aiDispersionCoefY = 7.0;
aiDispersionCoefX = 14.0;

modes[] += {AI_RIFLE_FIRING_MODES};

class Single : Mode_SemiAuto {
	#include "disable_firing_mode.h"
};

class FullAuto : Mode_FullAuto {
	#include "disable_firing_mode.h"
};

#include "ai_rifle_firing_modes.h"

// Disable BI firing profiles
class fullauto_medium: FullAuto {
	#include "disable_firing_mode.h"
};

class single_medium_optics1 : Single {
	#include "disable_firing_mode.h"
};

class single_far_optics2 : single_medium_optics1 {
	#include "disable_firing_mode.h"
};