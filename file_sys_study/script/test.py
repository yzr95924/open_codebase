import sys
import time
sys.path.append("common_include")

from my_py_lib import util
from my_py_lib import my_logger
from my_py_lib import cmd_handle

_G_SRC_FILE = util.get_format_cur_filename(__file__)

class TestClass:
    name = "global TestClass"
    def __init__(self):
        self.name = "TestClass"


if __name__ == "__main__":
    print(util.get_current_utc_time())

    filename, lineno, func = my_logger.find_caller(_G_SRC_FILE)
    print(filename)
    print(lineno)
    print(func)

    test_class = TestClass()
    print(test_class.name)