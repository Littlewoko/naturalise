cmake_minimum_required(VERSION 3.15)
project(naturalise VERSION 0.0.1 LANGUAGES CXX)

# Enforce standard, modern C++ cross-platform behavior
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Protect against common MSVC compiler quirks on Windows
if(MSVC)
    add_compile_options(/W4 /WX /EHsc) # Strict warnings, treat warnings as errors, standard exceptions
else()
    add_compile_options(-Wall -Wextra -Werror) # Strict warnings for GCC/Clang (Linux/Mac)
endif()

set(UTILS
    src/utils/types.h
)

set(RULES
    src/rules/base_rule.h
    src/rules/comment_rule.h
    src/rules/comment_rule.cpp
    src/rules/line_rule.h
    src/rules/line_rule.cpp
)

set(PARSER
    src/parser/natural_parser.cpp
    src/parser/natural_parser.h
)

add_library(lint_core
    ${PARSER}
    ${UTILS}
    ${RULES}
)
target_include_directories(lint_core PUBLIC src)

# 2. The main command-line utility
add_executable(naturalise src/main.cpp)
target_link_libraries(naturalise PRIVATE lint_core)

# 3. Discover and build tests automatically
enable_testing()
add_subdirectory(tests)