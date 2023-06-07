# src/app
add_executable(crypto_bench crypto_bench.cc)
add_executable(basic_io_bench basic_io_bench.cc)

target_link_libraries(crypto_bench CRYPTO_SRC_LIB ${THIRD_PARTY_LIB})
target_link_libraries(basic_io_bench BASIC_IO_SRC_LIB ${THIRD_PARTY_LIB})