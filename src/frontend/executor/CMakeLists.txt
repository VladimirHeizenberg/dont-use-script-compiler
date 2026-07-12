add_library(executor ExecutionNodeVisitor.cpp)

target_include_directories(executor PUBLIC ${PROJECT_SOURCE_DIR}/src/frontend)