def target2px(range_m, width_cm):
	# number of pixels across scope view / number of mils subtended by view
	milsPerPx = 835.0/14.0
	mils = (width_cm/100.0) / (range_m/1000.0)
	return mils * milsPerPx

w = float(eval(input('Target width in cm (48.26 is 19"): ')))

while 1:
	r = float(eval(input('Range: ')))
	print((target2px(r,w)));
