#include "renderer.hpp"
#include "../../lodepng/lodepng.hpp"

unsigned long render::fonts::primary;

/*
std::vector <int> get_resolution(std::string file_name) {
	std::ifstream in(file_name);

	unsigned int width, height;

	in.seekg(16);

	in.read((char*)&width, 4);

	in.read((char*)&height, 4);

	width = ntohl(width);

	height = ntohl(height);

	std::vector <int> kek;

	kek.push_back(width);

	kek.push_back(height);

	return kek;

}

unsigned char* ldImg(const char* filename, int w, int h) {
	std::vector<unsigned char> image;

	unsigned int width, height;

	width = w;

	height = h;

	unsigned int error = lodepng::decode(image, width, height, filename);

	// Just incase we get errors display them and say something is wrong
	if (error)
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	unsigned char* a = new unsigned char[image.size()];

	std::copy(image.begin(), image.end(), a);

	image.clear();

	return a;
}

texture::texture(std::string name) {
	std::vector <int> res = get_resolution(name);
	wi = res[0];
	he = res[1];
	char name2[MAX_PATH];
	str_to_char(name, name2, MAX_PATH);
	chr = ldImg(name2, wi, he);
	last_t = 0;
}

void texture::draw(int x, int y, int x1, int y1) {
	bool is_valid = false;
	unsigned int drawing_texture;

	if (last_t = 0 || !interfaces::surface->is_texture_id_valid(last_t)) {
		drawing_texture = interfaces::surface->create_new_texture_id(true);

		if (drawing_texture)
			return;

		interfaces::surface->set_texture_rgba(drawing_texture, chr, (unsigned int)wi, (unsigned int)he);

		if (interfaces::surface->is_texture_id_valid(drawing_texture))
			is_valid = true;
		last_t = drawing_texture;

	}
	else
		drawing_texture = last_t;

	interfaces::surface->set_drawing_color(255, 255, 255, 255);
	interfaces::surface->set_texture(drawing_texture);
	interfaces::surface->draw_textured_rect(x, y, x1, y1);
}

*/

void render::initialize() {
	render::fonts::primary = interfaces::surface->font_create();

	interfaces::surface->set_font_glyph(render::fonts::primary, "Modern Dos 8x8", 8, 400, 0, 0, font_flags::fontflag_none);

	console::log("[setup] render initialized!\n");
}

void render::draw_line(std::int32_t x1, std::int32_t y1, std::int32_t x2, std::int32_t y2, color colour) {
	interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
	interfaces::surface->draw_line(x1, y1, x2, y2);
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t *text, bool centered, color color) {
	interfaces::surface->draw_text_font(font);
	int text_width, text_height;

	if (centered) {
		interfaces::surface->get_text_size(font, text, text_width, text_height);
		interfaces::surface->draw_text_pos(x - text_width / 2, y);
	}
	else
		interfaces::surface->draw_text_pos(x, y );

	interfaces::surface->set_text_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_render_text(text, wcslen(text));
}

void render::text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color) {
	wchar_t temp[128];
	int text_width, text_height;
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
		interfaces::surface->draw_text_font(font);
		if (centered) {
			interfaces::surface->get_text_size(font, temp, text_width, text_height);
			interfaces::surface->draw_text_pos(x - text_width / 2, y);
		}
		else
			interfaces::surface->draw_text_pos(x, y);
		interfaces::surface->set_text_color(color.r, color.g, color.b, color.a);
		interfaces::surface->draw_render_text(temp, wcslen(temp));
	}
}

void render::draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outlined_rect(x, y, width, height);
}

void render::draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_filled_rectangle(x, y, width, height);
}

void render::draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) {
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outlined_rect(x, y, width, height);
}

void render::draw_textured_polygon(std::int32_t vertices_count, vertex_t* vertices, color color) {
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	unsigned int texture_id{};
	if (!texture_id) {
		texture_id = interfaces::surface->create_new_texture_id(true);
		interfaces::surface->set_texture_rgba(texture_id, buf, 1, 1);
	}
	interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
	interfaces::surface->set_texture(texture_id);
	interfaces::surface->draw_polygon(vertices_count, vertices);
}

void render::draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color) {
	float step = M_PI * 2.0 / segments;
	for (float a = 0; a < (M_PI * 2.0); a += step) {
		float x1 = radius * cos(a) + x;
		float y1 = radius * sin(a) + y;
		float x2 = radius * cos(a + step) + x;
		float y2 = radius * sin(a + step) + y;
		interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
		interfaces::surface->draw_line(x1, y1, x2, y2);
	}
}

vec2_t render::get_text_size(unsigned long font, std::string text) {
	std::wstring a(text.begin(), text.end());
	const wchar_t* wstr = a.c_str();
	static int w, h;

	interfaces::surface->get_text_size(font, wstr, w, h);
	return { static_cast<float>(w), static_cast<float>(h) };
}
