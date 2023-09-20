# Find the kernel release
execute_process(
        COMMAND uname -r
        OUTPUT_VARIABLE KERNEL_RELEASE_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Find the headers
find_path(KERNEL_SOURCE_DIR
    include/linux/user.h
    PATHS /usr/src/linux-headers-${KERNEL_RELEASE_VERSION}
    PATHS /usr/src/kernels/${KERNEL_RELEASE_VERSION}
)

message(STATUS "Kernel release: ${KERNEL_RELEASE_VERSION}")
message(STATUS "Kernel headers: ${KERNEL_SOURCE_DIR}")

if (KERNEL_SOURCE_DIR)
    set(KERNEL_HEADER_INCLUDE
        ${KERNEL_SOURCE_DIR}/include
        ${KERNEL_SOURCE_DIR}/arch/x86/include/generated
        ${KERNEL_SOURCE_DIR}/arch/x86/include
        CACHE PATH "Kernel headers include dirs"
    )
    set(KERNEL_HEADER_FOUND 1 CACHE STRING "Set to 1 if kernel headers were found")
else (KERNEL_SOURCE_DIR)
    set(KERNEL_HEADER_FOUND 0 CACHE STRING "Set to 1 if kernel headers were found")
endif (KERNEL_SOURCE_DIR)

mark_as_advanced(KERNEL_HEADER_FOUND)