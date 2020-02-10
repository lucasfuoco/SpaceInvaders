#include <spaceinvaders/sprites/saucers/saucer3.hpp>

using namespace SpaceInvaders;
using namespace SpaceInvaders::Sprites::Saucers;

Saucer3::Saucer3() : Sprites::Saucer(),
buffer1(new SpaceInvaders::SpriteBuffer()),
buffer2(new SpaceInvaders::SpriteBuffer())
{
	buffer1->size.setWidth(12);
	buffer1->size.setHeight(8);
	buffer1->data = new uint8_t[96]
	{
		0,0,0,0,1,1,1,1,0,0,0,0, // ....@@@@....
		0,1,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@@.
		1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
		1,1,1,0,0,1,1,0,0,1,1,1, // @@@..@@..@@@
		1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
		0,0,0,1,1,0,0,1,1,0,0,0, // ...@@..@@...
		0,0,1,1,0,1,1,0,1,1,0,0, // ..@@.@@.@@..
		1,1,0,0,0,0,0,0,0,0,1,1  // @@........@@
	};

	buffer2->size.setWidth(12);
	buffer2->size.setHeight(8);
	buffer2->data = new uint8_t[96]
	{
		0,0,0,0,1,1,1,1,0,0,0,0, // ....@@@@....
		0,1,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@@.
		1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
		1,1,1,0,0,1,1,0,0,1,1,1, // @@@..@@..@@@
		1,1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@@
		0,0,1,1,1,0,0,1,1,1,0,0, // ..@@@..@@@..
		0,1,1,0,0,1,1,0,0,1,1,0, // .@@..@@..@@.
		0,0,1,1,0,0,0,0,1,1,0,0  // ..@@....@@..
	};


	position.setX(116);
	position.setY(120);

	animation.loop = true;
	animation.frameCount = 2;
	animation.frameDuration = 10;
	animation.time = 0;
	animation.frames.push_back(buffer1);
	animation.frames.push_back(buffer2);

	setColor(Color::GetRGBToUInt32(154, 128, 205));
	setDeathPoint(25);
	setReloadDuration(150);
}

Saucer3::~Saucer3() {
	if (buffer1->data) {
		delete[] buffer1->data;
		buffer1->data = nullptr;
	}

	if (buffer2->data) {
		delete[] buffer2->data;
		buffer2->data = nullptr;
	}

	delete buffer1;
	delete buffer2;
}

void Saucer3::ClearData(void) {
	Saucer::ClearData();
}