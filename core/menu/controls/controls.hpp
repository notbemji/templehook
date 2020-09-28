#pragma once
#include "../../../dependencies/utilities/csgo.hpp"
#include "../../menu/variables.hpp"

enum page_icons : int {
	none = 0
};

namespace controls {
	void checkbox(uint16_t x, uint16_t* y, bool* option, std::string text, color foreground, color background);
	void side_button(uint16_t x, uint16_t* y, int* page, int target_page, std::string text, color foreground, color background);
	void page_icon(uint16_t x, uint16_t y, int* page, int target_page, bool* is_selected, std::string text, page_icons icon, color foreground, color background);
}