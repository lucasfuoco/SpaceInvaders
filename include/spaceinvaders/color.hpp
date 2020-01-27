#pragma once
#include <iostream>

namespace SpaceInvaders {
	struct Color {
		static uint32_t GetRGBToUInt32(uint8_t red, uint8_t green, uint8_t blue);
	};
}