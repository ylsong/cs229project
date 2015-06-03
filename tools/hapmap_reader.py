import sys

filename = sys.argv[1];

f = open(filename,"r")

#skip the first line
f.readline()
content = f.readlines()

print len(content)
for line in content:
	columns = line.split()
	major = columns[1][0]
	minor = columns[1][2]
	for x in range(11,59):
		snp = columns[x]
		if snp[0] != snp[1]:
			sys.stdout.write('2')
		elif snp[0] == major:
			sys.stdout.write('0')
		else:
			sys.stdout.write('1')
	print ""





