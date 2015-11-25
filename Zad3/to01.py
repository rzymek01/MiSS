import sys
for s in sys.stdin:
	print s.strip() + "/" + str(int(sys.argv[1])-1)
