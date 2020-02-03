#include <spaceinvaders/color.hpp>

using namespace SpaceInvaders;

uint32_t Color::GetRGBToUInt32(uint8_t red, uint8_t green, uint8_t blue) {
	uint32_t rgba = (red << 24) | (green << 16) | (blue << 8) | 255;
	return // Source is in format: 0xAARRGGBB
        ((rgba & 0xFF000000) >> 24) | //______AA
        ((rgba & 0x00FF0000) >> 8) | //____RR__
        ((rgba & 0x0000FF00) << 8) | //__GG____
        ((rgba & 0x000000FF) << 24);  //BB______
    // Return value is in format:  0xBBGGRRAA;
}