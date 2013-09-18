tt = 0

vi = 381
af = -0.0021;

accel = af * vi * vi

v = vi
dtrav = 0
lastaccelcalc = 0
drop = 0

interval = 0.01
i = 0

while tt < 0.5:
	i = i + 1;
	tt = tt + interval
	dtrav = dtrav + (v * interval)
	if dtrav - lastaccelcalc >= 1:
		lastaccelcalc = dtrav
		accel = af * v * v
		drop = 0.5 * 9.80665 * tt * tt * 100
		print(dtrav, v, drop)

	#print(tt, dtrav, v)

	v = v - accel * (tt - (tt + interval))


