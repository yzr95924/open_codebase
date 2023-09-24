# src/app
add_executable(main main.c)
target_link_libraries(main BASIC_API_SRC_LIB)

add_executable(mkfs_simple mkfs_simple.c)