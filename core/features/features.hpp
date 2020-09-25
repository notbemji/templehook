#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"

namespace visuals {
	namespace players {
		void render();
	};
}

namespace misc {
	namespace movement {
		void bunny_hop(c_usercmd* cmd);
	};

	namespace fun {
		void trashtalk();
	};
}