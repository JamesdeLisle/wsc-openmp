#! /usr/bin/env python

import time
import os
import sys


def check(folder):
    fold = os.path.join(os.getcwd(), folder)
    command = "ls -l %s | grep TRACKU | cut -c46-50" % fold
    t = int(os.popen(command).read().split(":")[0])
    tdiff = time.localtime().tm_hour - t
    if tdiff > 1:
        os.remove("%sTRACKU" % fold)
    else:
        pass


if __name__ == "__main__":
    check(sys.argv[1])
