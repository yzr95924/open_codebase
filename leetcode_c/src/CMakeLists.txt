include_directories(../include)
link_directories(../lib)

set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g -ggdb3 -fsanitize=address -fno-omit-frame-pointer")
#set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g -ggdb3") # for gdb, for valgrind
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb3 -fsanitize=address -fno-omit-frame-pointer")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb3") # for gdb, for valgrind
set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

# if use clang
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_AR "/usr/bin/llvm-ar")
set(CMAKE_LINKER "/usr/bin/llvm-ld")
set(CMAKE_NM "/usr/bin/llvm-nm")
set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
set(CMAKE_RANLIB "/usr/bin/llvm-ranlib")

# add the lib
set(INNER_LIB BFS_Q_SRC_LIB APP_SYS_Q_SRC_LIB MATH_Q_SRC_LIB STACK_Q_SRC_LIB
    GREEDY_DP_Q_SRC_LIB FIND_SORT_Q_SRC_LIB HASH_Q_SRC_LIB SLIDE_TWO_Q_SRC_LIB)
list(APPEND FINAL_LIB ${INNER_LIB})

add_subdirectory(main)
add_subdirectory(app_sys_q)
add_subdirectory(bfs_q)
add_subdirectory(math_q)
add_subdirectory(stack_q)
add_subdirectory(greedy_dp_q)
add_subdirectory(find_sort_q)
add_subdirectory(hash_q)
add_subdirectory(slide_two_q)
