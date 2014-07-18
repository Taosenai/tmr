///////////////////////////////////
// 0-120m

class AI_FullAuto_0to80_Burst25 : manual {
	showToPlayer = false;
	burst = 25;
	minRange = 0;
	minRangeProbab = 0.9;
	midRange = 40;
	midRangeProbab = 0.5;
	maxRange = 80;
	maxRangeProbab = 0.3;

	aiRateOfFire = 2.5;
	aiRateOfFireDistance = 80;
};

class AI_FullAuto_0to120_Burst20 : manual {
	showToPlayer = false;
	burst = 20;
	minRange = 0;
	minRangeProbab = 0.7;
	midRange = 50;
	midRangeProbab = 0.5;
	maxRange = 120;
	maxRangeProbab = 0.3;

	aiRateOfFire = 3;
	aiRateOfFireDistance = 120;
};

///////////////////////////////////
// 120-550m

class AI_FullAuto_120to550_Burst15 : manual {
	showToPlayer = false;
	burst = 15;
	minRange = 120;
	minRangeProbab = 0.3;
	midRange = 220;
	midRangeProbab = 0.3;
	maxRange = 550;
	maxRangeProbab = 0.15;

	aiRateOfFire = 3.2;
	aiRateOfFireDistance = 550;
};

///////////////////////////////////
// 550-950m

class AI_FullAuto_550to950_Burst10 : manual {
	showToPlayer = false;
	burst = 10;
	minRange = 550;
	minRangeProbab = 0.4;
	midRange = 750;
	midRangeProbab = 0.7;
	maxRange = 950;
	maxRangeProbab = 0.9;

	aiRateOfFire = 4.2;
	aiRateOfFireDistance = 950;
};


///////////////////////////////////
// 950-1300m (optics required)

class AI_FullAuto_950to1300_Burst10 : manual {
	requiredOpticType = 1;

	showToPlayer = false;
	burst = 10;
	minRange = 950;
	minRangeProbab = 1;
	midRange = 1125;
	midRangeProbab = 1;
	maxRange = 1300;
	maxRangeProbab = 1;

	aiRateOfFire = 8.2;
	aiRateOfFireDistance = 1300;
};