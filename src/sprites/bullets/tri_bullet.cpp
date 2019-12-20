#include <sprites/bullets/tri_bullet.hpp>

using namespace SpaceInvaders::Sprites::Bullets;

TriBullet::TriBullet() : SpaceInvaders::Sprites::Bullet(),
	buffer1(new SpaceInvaders::SpriteBuffer()),
	buffer2(new SpaceInvaders::SpriteBuffer())
{
	buffer1->size.setWidth(3);
	buffer1->size.setHeight(7);
	buffer1->data = new uint8_t[21]
	{
		0,0,1, // ..@
		0,1,0, // .@.
		1,0,0, // @..
		0,1,0, // .@.
		0,0,1, // ..@
		0,1,0, // .@.
		1,0,0  // @..
	};

	buffer2->size.setWidth(3);
	buffer2->size.setHeight(7);
	buffer2->data = new uint8_t[21]
	{
		1,0,0, // @..
		0,1,0, // .@.
		0,0,1, // ..@
		0,1,0, // .@.
		1,0,0, // @..
		0,1,0, // .@.
		0,0,1  // ..@
	};

	position.setX(1000);
	position.setY(1000);

	setColor(Color::GetRGBToUInt32(255, 244, 182));
}

TriBullet::~TriBullet() {
	delete buffer1;
	delete buffer2;
}

void TriBullet::ClearData(void) {
	if (buffer1) {
		delete[] buffer1->data;
		buffer1->data = nullptr;
	}

	if (buffer2) {
		delete[] buffer2->data;
		buffer2->data = nullptr;
	}
}