f = open('crap2.txt')
list = f.readlines()
newlist = []

try:
	for x in range(0, len(list)):
		if 'class' in list[x] and ('aimPrecision' in list[x+1] or 'aimprecision' in list[x+1]):
			if len(list[x].split()) > 3:
				newlist.append("class " + list[x].split()[3] + ";\n")
			newlist.append(list[x])
			newlist.append(list[x+1])
			newlist.append("\n};\n")
except:
	print('whoops')

seenlist = []
newnewlist = []
for x in range(0, len(newlist)):
	if not newlist[x] in seenlist:
		seenlist.append(newlist[x])
		newnewlist.append(newlist[x])
	else:
		if not 'class' in newlist[x]:
			newnewlist.append(newlist[x])

fn = open('crap4.txt', 'w')
fn.writelines(newnewlist)
fn.close()
f.close()