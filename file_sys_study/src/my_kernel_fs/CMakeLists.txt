# ./src/kernel
find_package(KernelHeader REQUIRED)
aux_source_directory(. MY_KERNEL_SRC)
set(MY_KERNEL_OBJ_STR "${MY_KERNEL_SRC}")
string(REPLACE ".c" ".o " MY_KERNEL_OBJ_STR ${MY_KERNEL_OBJ_STR})
set(KERNEL_MODULE_NAME "my_module")
set(KERNEL_MODULE_FILE_NAME "${KERNEL_MODULE_NAME}.ko")

# add header to include path
add_definitions(-D__KERNEL__ -DMODULE -D__GNUC__)
include_directories(${KERNEL_HEADER_INCLUDE})

# configure the compile command
set(KBUILD_CMD $(MAKE) modules -C ${KERNEL_SOURCE_DIR}
    M=${CMAKE_CURRENT_BINARY_DIR}
    src=${CMAKE_CURRENT_SOURCE_DIR}
)
set(KBUILD_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Kbuild)

# Remove the old KBUILD file before start
FILE(REMOVE ${KBUILD_FILE})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    set(CCFLAG_Y "ccflags-y := -g -DDEBUG -std=gnu11 -I${PROJECT_SOURCE_DIR}/include ")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CCFLAG_Y "ccflags-y := -O3 -std=gnu11 -I${PROJECT_SOURCE_DIR}/include ")
    message(STATUS "Release build")
endif()

# Generate the Kbuild file through cmake.
add_custom_command(
    OUTPUT ${KBUILD_FILE}
    COMMAND echo "obj-m := ${KERNEL_MODULE_NAME}.o" > ${KBUILD_FILE}
    COMMAND echo "${KERNEL_MODULE_NAME}-objs := ${MY_KERNEL_OBJ_STR}" >> ${KBUILD_FILE}
    COMMAND echo ${CCFLAG_Y} >> ${KBUILD_FILE}
    # ccflags-y := -std=gnu11 -I${PROJECT_SOURCE_DIR}/include " >> ${KBUILD_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

# Build
add_custom_command(
    OUTPUT ${KERNEL_MODULE_FILE_NAME}
    COMMAND ${KBUILD_CMD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${KBUILD_FILE} ${MY_KERNEL_SRC}
    VERBATIM
)

# move the mod file to the bin folder
add_custom_target(MoveMod ALL DEPENDS ${KBUILD_FILE} ${KERNEL_MODULE_FILE_NAME})
add_custom_command(TARGET MoveMod POST_BUILD
    COMMAND ${CMAKE_COMMADN} mv
    ${CMAKE_CURRENT_BINARY_DIR}/${KERNEL_MODULE_FILE_NAME}
    ${EXECUTABLE_OUTPUT_PATH}
    VERBATIM
)