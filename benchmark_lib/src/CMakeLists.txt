find_package(Boost)
find_package(OpenSSL)

if(BOOST_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${BOOST_LIBRARY_DIRS})
endif()

if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIRS})
    link_directories(${OPENSSL_LIBRARY_DIRS})
endif()

include_directories(${Boost_INCLUDE_DIRS} ../include)
link_directories(${Boost_LIBRARY_DIRS} ../lib)

set(COMMON_FLAG "-Wall")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb3 -fsanitize=address -fno-omit-frame-pointer ${COMMON_FLAG}")
# set(CMAKE_C_FLAGS_DEBUG "-O0 -g -ggdb3 ${COMMON_FLAG}")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb3 -fsanitize=address -fno-omit-frame-pointer ${COMMON_FLAG}")
# set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb3 ${COMMON_FLAG}") # for gdb, for valgrind
set(CMAKE_C_FLAGS_RELEASE "-O3 ${COMMON_FLAG}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${COMMON_FLAG}")

add_link_options(
    "-rdynamic"
)

# if use clang
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_AR "/usr/bin/llvm-ar")
set(CMAKE_LINKER "/usr/bin/llvm-ld")
set(CMAKE_NM "/usr/bin/llvm-nm")
set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
set(CMAKE_RANLIB "/usr/bin/llvm-ranlib")

set(OPENSSL_LIB ssl crypto)
set(SYS_LIB pthread)
list(APPEND THIRD_PARTY_LIB ${OPENSSL_LIB} ${SYS_LIB})

add_subdirectory(app)
add_subdirectory(crypto)
add_subdirectory(basic_io)