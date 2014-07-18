///////////////////////////////////
// 0-120m

class AI_Single_0to120_11ROF : Single {
	showToPlayer = false;
	minRange = 0;
	minRangeProbab = 0.15;
	midRange = 50;
	midRangeProbab = 0.2;
	maxRange = 120;
	maxRangeProbab = 0.4;

	aiRateOfFire = 1.1;
	aiRateOfFireDistance = 120;
};

class AI_Single_0to120_07ROF : Single {
	showToPlayer = false;
	minRange = 0;
	minRangeProbab = 0.15;
	midRange = 50;
	midRangeProbab = 0.3;
	maxRange = 120;
	maxRangeProbab = 0.3;

	aiRateOfFire = 0.7;
	aiRateOfFireDistance = 120;
};

class AI_FullAuto_0to120_Burst5 : FullAuto {
	showToPlayer = false;
	burst = 5;
	minRange = 0;
	minRangeProbab = 0.7;
	midRange = 50;
	midRangeProbab = 0.5;
	maxRange = 120;
	maxRangeProbab = 0.3;

	aiRateOfFire = 3.5;
	aiRateOfFireDistance = 120;
};

///////////////////////////////////
// 120-550m

class AI_Single_120to550_25ROF : Single {
	showToPlayer = false;
	minRange = 120;
	minRangeProbab = 0.4;
	midRange = 220;
	midRangeProbab = 0.3;
	maxRange = 550;
	maxRangeProbab = 0.2;

	aiRateOfFire = 2.5;
	aiRateOfFireDistance = 550;
};

class AI_Single_120to550_35ROF : Single {
	showToPlayer = false;
	minRange = 120;
	minRangeProbab = 0.3;
	midRange = 220;
	midRangeProbab = 0.4;
	maxRange = 550;
	maxRangeProbab = 0.65;

	aiRateOfFire = 3.5;
	aiRateOfFireDistance = 550;
};

class AI_FullAuto_120to550_Burst4 : FullAuto {
	showToPlayer = false;
	burst = 4;
	minRange = 120;
	minRangeProbab = 0.3;
	midRange = 220;
	midRangeProbab = 0.3;
	maxRange = 550;
	maxRangeProbab = 0.15;

	aiRateOfFire = 3.5;
	aiRateOfFireDistance = 550;
};

///////////////////////////////////
// 550-950m

class AI_Single_550to950_55ROF : Single {
	showToPlayer = false;
	minRange = 550;
	minRangeProbab = 0.6;
	midRange = 750;
	midRangeProbab = 0.3;
	maxRange = 950;
	maxRangeProbab = 0.1;

	aiRateOfFire = 5.5;
	aiRateOfFireDistance = 950;
};

class AI_Single_550to950_120ROF : Single {
	showToPlayer = false;
	minRange = 550;
	minRangeProbab = 0.4;
	midRange = 750;
	midRangeProbab = 0.7;
	maxRange = 950;
	maxRangeProbab = 0.9;

	aiRateOfFire = 12.0;
	aiRateOfFireDistance = 950;
};

///////////////////////////////////
// 950-1300m (sniper optics required)

class AI_Single_950to1300_300ROF : Single {
	requiredOpticType = 2;

	showToPlayer = false;
	minRange = 950;
	minRangeProbab = 1;
	midRange = 1125;
	midRangeProbab = 1;
	maxRange = 1300;
	maxRangeProbab = 1;
	aiRateOfFire = 30.0;
	aiRateOfFireDistance = 1300;
};