# src/main
add_executable(main main.c)
target_link_libraries(main ${FINAL_LIB})

add_executable(test_main test_main.cc)
target_link_libraries(test_main ${FINAL_LIB})

# add_executable(uthash_test_int_key uthash_test_int_key.c)