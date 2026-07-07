cmake_minimum_required(VERSION 3.16)

project(ResearchPaperAssistant)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER REQUIRED poppler-cpp)

add_executable(
    ResearchPaperAssistant
    src/main.cpp
    src/pdf/PDFParser.cpp
)

target_include_directories(
    ResearchPaperAssistant
    PRIVATE
    ${POPPLER_INCLUDE_DIRS}
)

target_link_directories(
    ResearchPaperAssistant
    PRIVATE
    ${POPPLER_LIBRARY_DIRS}
)

target_link_libraries(
    ResearchPaperAssistant
    PRIVATE
    ${POPPLER_LIBRARIES}
)