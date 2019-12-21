#include <sprites/saucers/saucer1.hpp>

using namespace SpaceInvaders;
using namespace SpaceInvaders::Sprites::Saucers;

Saucer1::Saucer1() : Sprites::Saucer(),
	buffer1(new SpaceInvaders::SpriteBuffer()),
	buffer2(new SpaceInvaders::SpriteBuffer())
{
	buffer1->size.setWidth(11);
	buffer1->size.setHeight(8);
	buffer1->data = new uint8_t[88]
	{
		0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
		0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
		0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
		0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
		1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
		1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
		1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
		0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
	};

	buffer2->size.setWidth(11);
	buffer2->size.setHeight(8);
	buffer2->data = new uint8_t[88]
	{
		0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
		1,0,0,1,0,0,0,1,0,0,1, // @..@...@..@
		1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
		1,1,1,0,1,1,1,0,1,1,1, // @@@.@@@.@@@
		1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
		0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
		0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
		0,1,0,0,0,0,0,0,0,1,0  // .@.......@.
	};


	position.setX(116);
	position.setY(120);

	animation.loop = true;
	animation.frameCount = 2;
	animation.frameDuration = 10;
	animation.time = 0;
	animation.frames.push_back(buffer1);
	animation.frames.push_back(buffer2);

	setColor(Color::GetRGBToUInt32(205, 171, 128));
	setDeathPoint(10);
	setReloadDuration(60);
}

Saucer1::~Saucer1() {
	delete buffer1;
	delete buffer2;
}

void Saucer1::ClearData(void) {
	if (buffer1->data) {
		delete[] buffer1->data;
		buffer1->data = nullptr;
	}

	if (buffer2->data) {
		delete[] buffer2->data;
		buffer2->data = nullptr;
	}

	Saucer::ClearData();
}