#! /bin/bash

MODULE_KO_FILE="./bin/my_module.ko"
TEST_IMG_FILE_NAME="./test.img"
TEST_DIR_NAME="./test_dir"

set -x
cd ./bin
dd if=/dev/zero of=${TEST_IMG_FILE_NAME} bs=1M count=50
./mkfs_simplefs ${TEST_IMG_FILE_NAME}

cd ..
echo "load the test module"
sudo insmod "${MODULE_KO_FILE}"

cd ./bin
mkdir -p ${TEST_DIR_NAME}
sudo mount -o loop -t simplefs ${TEST_IMG_FILE_NAME} ${TEST_DIR_NAME}
