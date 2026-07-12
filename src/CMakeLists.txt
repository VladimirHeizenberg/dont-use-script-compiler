add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(frontend)

target_link_libraries(${PROJECT_NAME} PRIVATE lexer parser executor)