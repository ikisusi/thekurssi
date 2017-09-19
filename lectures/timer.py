from timeit import timeit
import string
import sys

repeat = 100

for i in string.ascii_lowercase:
    if len(sys.argv) > 1:
        args = sys.argv[1] + i
    else:
        args = i
    timed = timeit(stmt = "subprocess.call(['./timeme', '%s'])" % args,
            setup = "import subprocess;",  number = repeat) / repeat

    print "For '%s' it took: %f seconds" % (args, timed)
