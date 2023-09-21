# src/main
# add the lib
set(INNER_LIB BFS_Q_SRC_LIB APP_SYS_Q_SRC_LIB MATH_Q_SRC_LIB STACK_Q_SRC_LIB
    GREEDY_DP_Q_SRC_LIB FIND_SORT_Q_SRC_LIB HASH_Q_SRC_LIB SLIDE_TWO_Q_SRC_LIB
    BACK_TRACK_Q_SRC_LIB)
list(APPEND FINAL_LIB ${INNER_LIB})

add_executable(main main.c)
target_link_libraries(main ${FINAL_LIB})

add_executable(test_main main_template.c)