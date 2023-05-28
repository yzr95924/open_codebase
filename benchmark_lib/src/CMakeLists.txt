find_package(Boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

include_directories(${Boost_INCLUDE_DIRS} ../include)
link_directories(${Boost_LIBRARY_DIRS} ../lib)

set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g -ggdb3 -fsanitize=address -fno-omit-frame-pointer")
# set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -g -ggdb3")
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

add_subdirectory(app)
add_subdirectory(crypto)