import sys
sys.path.append("common_include")

from py import my_logger
from py import cmd_handle
from py import util

_G_SRC_FILE = util.get_format_cur_filename(__file__)

class TestClass:
    name = "global TestClass"
    def __init__(self):
        self.name = "TestClass"

if __name__ == "__main__":
    cur_logger = my_logger.get_log(console_fmt=my_logger._G_FMT_FULL)
    # cur_logger.ml_clear_log_propagate_func()
    cur_logger.ml_debug_func("Test")
    cur_logger.ml_info_func("Test")
    cur_logger.ml_warning_func("Test")
    cur_logger.ml_error_func("Test")
    cur_logger.ml_stdout_func("Test")

    cmd = "ls"
    cmd_handle.run(command=cmd)