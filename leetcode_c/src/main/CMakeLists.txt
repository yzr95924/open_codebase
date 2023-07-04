# src/main
add_executable(main main.c)
target_link_libraries(main ${FINAL_LIB})

add_executable(uthash_test_int_key uthash_test_int_key.c)