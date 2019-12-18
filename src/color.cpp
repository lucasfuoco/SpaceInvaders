#include <color.hpp>

using namespace SpaceInvaders;

uint32_t Color::GetRGBToUInt32(uint8_t red, uint8_t green, uint8_t blue) {
	return (red << 24) | (green << 16) | (blue << 8) | 255;
}