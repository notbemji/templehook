#pragma once
#include <cstdint>
#include <ctime>
#include <string>
#include "../../source-sdk/math/vector3d.hpp"

namespace utilities {
	template< typename t >
	__forceinline static t call_virtual( void *name, int offset ) {
		int *table = *( int ** ) name;
		int address = table[ offset ];
		return ( t ) ( address );
	}

	std::uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept;

	int get_fps() noexcept;
	std::string get_timestamp_string() noexcept;
	bool cursor_in_box(int cursor[], int box[]);
}
