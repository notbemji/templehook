#include "controls.hpp"

void controls::checkbox(uint16_t x, uint16_t* y, bool* option, std::string text, color foreground, color background) {
	int mouse_cursor_pos[2];
	interfaces::surface->surface_get_cursor_pos(mouse_cursor_pos[0], mouse_cursor_pos[1]);
	std::string checkbox_text = "[";
	checkbox_text += *option ? "x" : " ";
	checkbox_text += "] " + text;
	vec2_t checkbox_text_size = render::get_text_size(render::fonts::primary, checkbox_text);
	int bounds[] = { x, *y, checkbox_text_size.x, checkbox_text_size.y };
	if (utilities::cursor_in_box(mouse_cursor_pos, bounds) && GetAsyncKeyState(VK_LBUTTON) & TRUE)
		*option = !(*option);
	render::draw_filled_rect(x, *y, checkbox_text_size.x, checkbox_text_size.y, utilities::cursor_in_box(mouse_cursor_pos, bounds) ? (variables::blink_switch ? foreground : background) : background);
	render::text(x, *y, render::fonts::primary, checkbox_text, false, utilities::cursor_in_box(mouse_cursor_pos, bounds) ? (variables::blink_switch ? background : foreground) : foreground);
	*y += checkbox_text_size.y + 5;
}