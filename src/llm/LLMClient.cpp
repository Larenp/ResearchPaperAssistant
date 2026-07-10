#include "LLMClient.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <string>

using json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);

  return size * nmemb;
}

std::string LLMClient::generate(const std::string &prompt) {
  CURL *curl = curl_easy_init();

  if (!curl) {
    return "Failed to initialize CURL.";
  }

  std::string response;

  json body;

  body["model"] = "qwen2.5:3b";
  body["prompt"] = prompt;
  body["stream"] = false;

  std::string requestBody = body.dump();

  struct curl_slist *headers = nullptr;
  headers = curl_slist_append(headers, "Content-Type: application/json");

  curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/generate");

  curl_easy_setopt(curl, CURLOPT_POST, 1L);

  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);

  CURLcode result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    std::string error = "CURL Error: ";

    error += curl_easy_strerror(result);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return error;
  }

  long statusCode = 0;

  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  if (statusCode != 200) {
    return "HTTP Error: " + std::to_string(statusCode);
  }

  try {
    json answer = json::parse(response);

    if (answer.contains("response")) {
      return answer["response"];
    }

    return "Ollama returned an unexpected response.";
  } catch (const std::exception &e) {
    return std::string("JSON Parse Error: ") + e.what();
  }
}