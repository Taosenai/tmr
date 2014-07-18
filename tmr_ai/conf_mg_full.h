aiDispersionCoefY = 10.0;
aiDispersionCoefX = 18.0;

modes[] += {AI_MG_FIRING_MODES};

class Single : Mode_SemiAuto {
	#include "disable_firing_mode.h"
};

class FullAuto : Mode_FullAuto {
	#include "disable_firing_mode.h"
};

#include "ai_mg_firing_modes_full.h"

// Disable BI firing profiles
class close : FullAuto {
	#include "disable_firing_mode.h"
};
class short : close {
	#include "disable_firing_mode.h"
};
class medium : close {
	#include "disable_firing_mode.h"
};
class far_optic1 : medium {
	#include "disable_firing_mode.h"
};
class far_optic2 : far_optic1 {
	#include "disable_firing_mode.h"
};