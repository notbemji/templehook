#include "menu.hpp"

void watermark::draw() {
	std::string watermark_text = utilities::get_timestamp_string() + " FPS:" + std::to_string(utilities::get_fps());
	if (csgo::local_player)
		watermark_text += " Speed:" + std::to_string((int)std::ceil(csgo::local_player->velocity().length_2d()));
	render::draw_filled_rect(5, 5, 8 * watermark_text.length(), 8, color::navy());
	render::text(5, 5, render::fonts::primary, watermark_text, false, color::white());
}