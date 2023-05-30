# src/app
add_executable(main main.cc)
add_executable(crypto_bench crypto_bench.cc)

target_link_libraries(crypto_bench CRYPTO_SRC_LIB ${THIRD_PARTY_LIB})