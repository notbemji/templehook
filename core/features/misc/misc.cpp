#include "../features.hpp"

void misc::movement::bunny_hop(c_usercmd* cmd) {
	const int move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
		return;

	if (!(csgo::local_player->flags() & fl_onground))
		cmd->buttons &= ~in_jump;
};

void misc::fun::trashtalk() {
	std::vector<std::string> quotes = {
		"Jesus said \"I will rebuild this temple in three days.\" I could make a compiler in 3 days.",
		"India nigger retard doctor.",
		"Yeah, I killed a CIA nigger with my car in 1999. Score one for the good guys.",
		"If you guys have ideas for things to do, let me know.I probably will ignore them.",
		"I have God's official endorsement. I win and the CIA/FBI niggers lose. Just wait. Dumb fuck FBI niggers.",
		"I report to God. You report to me.",
		"Computers went to shit when they started making them for niggers.",
		"God's world is perfectly just. Only a nigger cannot see. That's why niggers have no morals.",
		"The first time you meet an angel you get a horrible beating",
		"FUCK CIA NIGGERS",
		"If you don't wanna go for realism, you can go for better than realism!",
		"FUCK 7 bit ASCII",
		"I am literally the smartest programmer that has ever lived."
	};

	bool should_trashtalk = (int)std::floor((interfaces::globals->cur_time * 0.005f) / interfaces::globals->interval_per_tick) % 2;

	srand(time(NULL));
	std::string text = "say " + quotes[rand() % quotes.size()];

	static bool once = false;
	if (should_trashtalk) {
		if (!once) {
			interfaces::engine->execute_cmd(text.c_str());
			once = true;
		}
	}
	else {
		once = false;
	}
}