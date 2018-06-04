#! /usr/bin/env python

import time
import os
import sys


def check(folder):
    command = "ls -l %s | grep TRACKU | cut -c46-50" % folder
    t = int(os.popen(command).read().split(":")[0])
    tdiff = time.localtime().tm_hour - t
    if tdiff > 1:
        os.remove("%sTRACKU" % folder)
    else:
        pass


if __name__ == "__main__":
    check(sys.argv[1])
