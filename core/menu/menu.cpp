#include "menu.hpp"

RECT dimensions = RECT{ 50, 50, 600, 500 };

int mouse_cursor_pos[2];

void menu::draw() {
	if (!variables::menu::is_open)
		return;

	interfaces::surface->surface_get_cursor_pos(mouse_cursor_pos[0], mouse_cursor_pos[1]);

	static int cp_drag[] = { 0, 0 };
	static bool cp_dragging = false;
	int bounds[4] = { dimensions.left, dimensions.top, dimensions.right, dimensions.bottom };
	static int cur_page = 0;

	if (cp_dragging && !GetAsyncKeyState(VK_LBUTTON))
		cp_dragging = false;

	if (cp_dragging && GetAsyncKeyState(VK_LBUTTON)) {
		dimensions.left = mouse_cursor_pos[0] - cp_drag[0];
		dimensions.top = mouse_cursor_pos[1] - cp_drag[1];
	}

	int cp_draggable_bounds[] = { dimensions.left, dimensions.top, dimensions.right, 8 };
	if (utilities::cursor_in_box(mouse_cursor_pos, cp_draggable_bounds)) {
		cp_dragging = true;
		cp_drag[0] = mouse_cursor_pos[0] - dimensions.left;
		cp_drag[1] = mouse_cursor_pos[1] - dimensions.top;
	}

	int screen_size[2];
	interfaces::surface->get_screen_size(screen_size[0], screen_size[1]);

	if (dimensions.left < 0)
		dimensions.left = 0;
	if (dimensions.top < 0)
		dimensions.top = 0;
	if (dimensions.left + dimensions.right > screen_size[0])
		dimensions.left = screen_size[0] - dimensions.right;
	if (dimensions.top + dimensions.bottom > screen_size[1])
		dimensions.top = screen_size[1] - dimensions.bottom;

	render::draw_filled_rect(dimensions.left, dimensions.top, dimensions.right, dimensions.bottom, color::white());
	render::draw_filled_rect(dimensions.left, dimensions.top, dimensions.right, 8, color::navy());
	std::stringstream address_string;
	address_string << interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());
	std::string title_string = utilities::get_timestamp_string() + " FPS:" + std::to_string(utilities::get_fps()) + " Lcl:" + address_string.str();
	render::text(dimensions.left, dimensions.top, render::fonts::primary, title_string, false, color::white());

	render::draw_outline(dimensions.left + 3, dimensions.top + 10, dimensions.right - 6, dimensions.bottom - 12, color::navy());
	render::draw_line(dimensions.left + 2, dimensions.top + 10, dimensions.left + 2, dimensions.top + dimensions.bottom - 2, color::navy());
	render::draw_outline(dimensions.left + 6, dimensions.top + 12, dimensions.right - 12, dimensions.bottom - 16, color::navy());
	render::draw_line(dimensions.left + 5, dimensions.top + 12, dimensions.left + 5, dimensions.top + dimensions.bottom - 4, color::navy());
	render::draw_line(dimensions.left + dimensions.right - 3, dimensions.top + 10, dimensions.left + dimensions.right - 3, dimensions.top + dimensions.bottom - 2, color::navy());
	render::draw_line(dimensions.left + dimensions.right - 6, dimensions.top + 12, dimensions.left + dimensions.right - 6, dimensions.top + dimensions.bottom - 4, color::navy());

	render::draw_filled_rect(dimensions.left + 8, dimensions.top + 8, 32, 8, variables::blink_switch ? color::white() : color::navy());
	render::text(dimensions.left + 8, dimensions.top + 8, render::fonts::primary, "MENU", false, variables::blink_switch ? color::navy() : color::white());

	render::draw_filled_rect(dimensions.left + ((dimensions.right * 0.5f) - 64), dimensions.top + 8, 128, 8, color::navy());
	static float last_scrolling_change_time = 0.f;
	static std::string temple_hook_scrolling_title = "TempleHook......";
	if (interfaces::globals->realtime - last_scrolling_change_time >= 0.15f) {
		std::rotate(std::begin(temple_hook_scrolling_title), std::next(std::begin(temple_hook_scrolling_title)), std::end(temple_hook_scrolling_title));
		last_scrolling_change_time = interfaces::globals->realtime;
	}
	render::text(dimensions.left + ((dimensions.right * 0.5f) - 64), dimensions.top + 8, render::fonts::primary, temple_hook_scrolling_title, false, color::white());

	uint16_t side_y = dimensions.top + 16;

	controls::side_button(dimensions.left, &side_y, &cur_page, 0, "HOME", color::navy(), color::white());
	controls::side_button(dimensions.left, &side_y, &cur_page, 1, "AIMBOT", color::navy(), color::white());
	controls::side_button(dimensions.left, &side_y, &cur_page, 2, "VISUALS", color::navy(), color::white());
	controls::side_button(dimensions.left, &side_y, &cur_page, 3, "MISC", color::navy(), color::white());
	controls::side_button(dimensions.left, &side_y, &cur_page, 4, "INFO", color::navy(), color::white());

	switch (cur_page) {
		case 0: {
			static bool aimbot_is_selected = false;
			controls::page_icon(dimensions.left + 32, dimensions.top + 32, &cur_page, 1, &aimbot_is_selected, "Aimbot", page_icons::none, color::white(), color::navy());
			static bool visuals_is_selected = false;
			controls::page_icon(dimensions.left + 132, dimensions.top + 32, &cur_page, 2, &visuals_is_selected, "Visuals", page_icons::none, color::white(), color::navy());
		} break;
		case 1: {
			// aimbot
		} break;
		case 2: {
			uint16_t y = dimensions.top + 24;

			controls::checkbox(dimensions.left + 16, &y, &variables::visuals::player_esp, "Player wallhack", color::navy(), color::white());
			controls::checkbox(dimensions.left + 16, &y, &variables::visuals::player_esp_dead_only, "Player wallhack only while dead", color::navy(), color::white());
		} break;
		case 3: {
			uint16_t y = dimensions.top + 24;

			controls::checkbox(dimensions.left + 16, &y, &variables::movement::bunnyhop, "Automatic jump", color::navy(), color::white());
			controls::checkbox(dimensions.left + 16, &y, &variables::fun::trashtalk, "Divine Intellect Simulator 2018", color::navy(), color::white());
		} break;
		case 4: {
			// info
		} break;
		default: break;
	}
}

void menu::handle() {
	if (GetAsyncKeyState(VK_INSERT) & TRUE)
		variables::menu::is_open = !variables::menu::is_open;
}