#include "controls.hpp"

void controls::page_icon(uint16_t x, uint16_t y, int* page, int target_page, bool* is_selected, std::string text, page_icons icon, color foreground, color background) {
	int mouse_cursor_pos[2];
	interfaces::surface->surface_get_cursor_pos(mouse_cursor_pos[0], mouse_cursor_pos[1]);
	RECT bounds = RECT{ x, y, 60, 80 };
	int bounds_int[] = { x, y, 60, 80 };
	if (GetAsyncKeyState(VK_LBUTTON) & TRUE) {
		if (utilities::cursor_in_box(mouse_cursor_pos, bounds_int)) {
			if (*is_selected) {
				*page = target_page;
				*is_selected = false;
			}
			else
				*is_selected = true;
		}
		else
			*is_selected = false;
	}
	render::draw_filled_rect(bounds.left, bounds.top, bounds.right, bounds.bottom, *is_selected ? background : foreground);
	switch (icon) {
		case none: {
			render::text(bounds.left + (bounds.right / 2), bounds.top + (bounds.right / 2) - 4, render::fonts::primary, "(NO ICON)", true, *is_selected ? foreground : background);
		} break;
		default: break;
	}
	render::text(bounds.left + (bounds.right / 2), bounds.top + bounds.bottom - 8, render::fonts::primary, text, true, *is_selected ? foreground : background);
}