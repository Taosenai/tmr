aiDispersionCoefY = 10.0;
aiDispersionCoefX = 18.0;

modes[] += {AI_MG_FIRING_MODES};

class Single : Mode_SemiAuto {
	#include "disable_firing_mode.h"
};

class manual : Mode_FullAuto {
	#include "disable_firing_mode.h"
};

#include "ai_mg_firing_modes_manual.h"

// Disable BI firing profiles
class close : manual {
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