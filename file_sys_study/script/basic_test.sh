#! /bin/bash

MODULE_KO_FILE="./bin/my_module.ko"

set -x
echo "load the test module"
sudo insmod "${MODULE_KO_FILE}"
echo "unlad the test module"
sudo rmmod "${MODULE_KO_FILE}"