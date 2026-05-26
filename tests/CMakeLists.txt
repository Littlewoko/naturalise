include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.15.0 # Or latest stable v3 version
)

FetchContent_MakeAvailable(Catch2)

# Create the test runner executable
set(RULES
  rules/comment_rule_test.cpp
  rules/line_rule_test.cpp
)

add_executable(tests 
    unit/natural_parser_test.cpp
    ${RULES}
)

# Link the test runner to Catch2 and YOUR core library
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lint_core)

# Register the executable with CMake's test runner (CTest)
include(Catch)
catch_discover_tests(tests)