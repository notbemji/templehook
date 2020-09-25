#pragma once
#include "../../../dependencies/utilities/csgo.hpp"
#include "../../menu/variables.hpp"

namespace controls {
	void checkbox(uint16_t x, uint16_t* y, bool* option, std::string text, color foreground, color background);
}