cmake_minimum_required(VERSION 3.16)

project(ResearchPaperAssistant)

# Generate compile_commands.json (helps VS Code IntelliSense)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Poppler using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER REQUIRED poppler-cpp)

# Create executable
add_executable(
    ResearchPaperAssistant

    src/main.cpp

    src/pdf/PDFParser.cpp

    src/text/TextCleaner.cpp

    src/chunk/Chunker.cpp

    src/embedding/EmbeddingGenerator.cpp
)

# Include project headers
target_include_directories(
    ResearchPaperAssistant
    PRIVATE

    ${POPPLER_INCLUDE_DIRS}

    src
)

# Link library directories
target_link_directories(
    ResearchPaperAssistant
    PRIVATE

    ${POPPLER_LIBRARY_DIRS}
)

# Link Poppler library
target_link_libraries(
    ResearchPaperAssistant
    PRIVATE

    ${POPPLER_LIBRARIES}
)
