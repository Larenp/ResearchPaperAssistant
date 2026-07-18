# Research Paper Assistant

A C++-based Retrieval-Augmented Generation (RAG) application that lets
users ask questions about a research paper in PDF format. It extracts
and cleans PDF text, splits it into chunks, generates semantic
embeddings, retrieves relevant context, and uses a local Ollama model to
generate an answer.

## Features

-   PDF text extraction using Poppler
-   Text cleaning and chunking
-   Embeddings using Sentence Transformers (`all-MiniLM-L6-v2`)
-   Cosine similarity-based semantic retrieval
-   Top-K relevant chunk retrieval
-   Context-aware prompt generation
-   Local answer generation using Ollama and `qwen2.5:3b`
-   Offline embedding support after the model is cached
-   C++ application with Python-based embedding generation

## Pipeline

PDF → PDF Parser → Text Cleaner → Chunker → Embeddings → Vector Database
→ User Question → Query Embedding → Cosine Similarity → Top-K Retrieval
→ Prompt Builder → Ollama → Final Answer

## Technologies Used

-   C++20
-   CMake
-   Poppler C++
-   Python
-   Sentence Transformers
-   PyTorch
-   Hugging Face
-   Ollama
-   Qwen 2.5 3B
-   libcurl
-   nlohmann/json

## Prerequisites

On macOS, install the required dependencies:

    brew install cmake pkg-config poppler curl nlohmann-json

Install Ollama and pull the model:

    ollama pull qwen2.5:3b

Verify that Ollama is running:

    curl http://localhost:11434/api/tags

## Python Setup

Go to the Python directory:

    cd src/python

Create and activate a virtual environment:

    python3 -m venv .venv
    source .venv/bin/activate

Install the dependencies:

    pip install sentence-transformers torch

The embedding service uses `all-MiniLM-L6-v2`. Download and cache it
once while connected to the internet.

For offline use, set these before loading the model in
`embedding_service.py`:

    os.environ["HF_HUB_OFFLINE"] = "1"
    os.environ["TRANSFORMERS_OFFLINE"] = "1"

## Build

From the project root:

    mkdir build
    cd build
    cmake ..
    cmake --build .

## Run

Place `paper.pdf` in the project root and make sure Ollama is running.

From the `build` directory:

    ./ResearchPaperAssistant

Example:

    Embedding Chunk 1/4
    Embedding Chunk 2/4
    Embedding Chunk 3/4
    Embedding Chunk 4/4

    Ask a question: What are transformers?

## How It Works

1.  The PDF parser extracts text from `paper.pdf`.
2.  The text cleaner preprocesses the extracted text.
3.  The chunker divides the document into smaller chunks.
4.  MiniLM generates an embedding for each chunk.
5.  The user's question is converted into an embedding.
6.  Cosine similarity compares the question with document chunks.
7.  The retriever selects the top matching chunks.
8.  The prompt builder combines the retrieved context and question.
9.  The prompt is sent to Qwen through the local Ollama API.
10. The generated answer is displayed in the terminal.

## Current Limitations

-   Embeddings are regenerated every time the application starts.
-   The Python embedding process is started repeatedly, increasing
    processing time.
-   Large PDFs take longer to index.
-   Retrieval quality depends on chunk size and overlap.
-   A similarity threshold is needed to better reject unrelated
    questions.
-   The current version processes a single PDF.

## Planned Improvements

-   Persistent embedding service to load MiniLM only once
-   Save embeddings to disk to avoid repeated indexing
-   Improved chunking with overlap
-   Similarity threshold for irrelevant questions
-   Source and page references in answers
-   Multiple PDF support
-   Better performance for large documents

## Author

Laren Pinto
