project(ProcessCSVs)
find_package(Arrow REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Arrow::arrow_shared)