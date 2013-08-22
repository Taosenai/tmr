def target2px(range_m, width_cm):
	# number of pixels across scope view / number of angular mils subtended by view
	milsPerPx = 835/106.6666666667
	mils = (width_cm/100) / (range_m/1000)
	return mils * milsPerPx

w = float(input('Target width in cm (48.26 is 19"): '))

while 1:
	r = float(input('Range: '))
	print(target2px(r,w));
