#include "controls.hpp"

void controls::side_button(uint16_t x, uint16_t* y, int* page, int target_page, std::string text, color foreground, color background) {
	int mouse_cursor_pos[2];
	interfaces::surface->surface_get_cursor_pos(mouse_cursor_pos[0], mouse_cursor_pos[1]);
	int bounds[] = { x, *y, 8, text.length() * 8 };
	if (utilities::cursor_in_box(mouse_cursor_pos, bounds) && GetAsyncKeyState(VK_LBUTTON) & TRUE)
		*page = target_page;
	render::draw_filled_rect(x, *y, 8, text.length() * 8, *page == target_page ? (variables::blink_switch ? foreground : background) : background);
	for (uint16_t i = 0; i < text.length(); i++) {
		std::string letter(1, text.at(i));
		render::text(x, *y + (i * 8), render::fonts::primary, letter, false, *page == target_page ? (variables::blink_switch ? background : foreground) : foreground);
	}
	*y += (text.length() * 8) + 8;
}