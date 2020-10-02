#include "../features.hpp"

RECT get_player_box_dimensions(player_t* player)
{
	RECT box;
	vec3_t bottom, top;
	math::world_to_screen(player->abs_origin() - vec3_t(0, 0, 7), bottom);
	math::world_to_screen(player->get_hitbox_position(hitboxes::hitbox_neck) + vec3_t(0, 0, 12), top);
	int mid = bottom.y - top.y;
	int width = mid / 4.f;

	box.bottom = top.y;
	box.top = top.y + mid;
	box.left = bottom.x - width;
	box.right = bottom.x - width + width * 2;
	return box;
}

void visuals::players::render() {
	if (!csgo::local_player)
		return;

	if (variables::visuals::player_esp_dead_only && csgo::local_player->is_alive())
		return;

	for (uint16_t i = 1; i < interfaces::globals->max_clients; i++) {
		auto player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!player || !player->is_player() || !player->is_alive() || player->dormant() || player->team() == csgo::local_player->team())
			continue;

		RECT box = get_player_box_dimensions(player);

		player_info_t player_info;
		interfaces::engine->get_player_info(i, &player_info);

		render::draw_outline(box.left, box.bottom, box.right - box.left, box.top - box.bottom, color::white());
		render::draw_outline(box.left - 1, box.bottom - 1, box.right - box.left + 2, box.top - box.bottom + 2, color::black(175));
		render::draw_outline(box.left + 1, box.bottom + 1, box.right - box.left - 2, box.top - box.bottom - 2, color::black(175));

		std::string player_name_text = player_info.name;
		player_name_text += " \u1665" + std::to_string(player->health()); // TODO: fix the heart icon
		vec2_t text_size = render::get_text_size(render::fonts::primary, player_name_text);
		render::text(box.left + ((box.right - box.left) * 0.5f), box.bottom - text_size.y - 2, render::fonts::primary, player_name_text, true, color::white());
	}
}
