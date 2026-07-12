include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  dont_use_script_tests
  lexer/arithmetic_lexer_tests.cpp
  parser/parser_tests.cpp
)

target_link_libraries(
  dont_use_script_tests
  lexer
  parser
  executor
  GTest::gtest_main
)

target_include_directories(dont_use_script_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(dont_use_script_tests)