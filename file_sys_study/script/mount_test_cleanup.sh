#! /bin/bash

MODULE_KO_FILE="./bin/my_module.ko"
TEST_IMG_FILE_NAME="./test.img"
TEST_DIR_NAME="./test_dir"

set -x
cd ./bin
sudo umount -t simplefs -a -l

cd ..
echo "unload the test module"
sudo rmmod "${MODULE_KO_FILE}"