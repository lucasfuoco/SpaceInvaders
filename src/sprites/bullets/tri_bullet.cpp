#include <sprites/bullets/tri_bullet.hpp>

using namespace SpaceInvaders::Sprites::Bullets;

TriBullet::TriBullet() : SpaceInvaders::Sprites::Bullet(),
	buffer1(new SpaceInvaders::SpriteBuffer()),
	buffer2(new SpaceInvaders::SpriteBuffer())
{
	buffer1->size.setWidth(3);
	buffer1->size.setHeight(11);
	buffer1->data = new uint8_t[33]
	{
		0,0,1, // ..@
		0,1,0, // .@.
		1,0,0, // @..
		0,1,0, // .@.
		0,0,1, // ..@
		0,1,0, // .@.
		1,0,0, // @..
		0,1,0, // .@.
		0,0,1, // ..@
		0,1,0, // .@.
		1,0,0  // @..
	};

	buffer2->size.setWidth(3);
	buffer2->size.setHeight(11);
	buffer2->data = new uint8_t[33]
	{
		1,0,0, // @..
		0,1,0, // .@.
		0,0,1, // ..@
		0,1,0, // .@.
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

	animation.loop = true;
	animation.frameCount = 2;
	animation.frameDuration = 4;
	animation.time = 0;
	animation.frames.push_back(buffer1);
	animation.frames.push_back(buffer2);

	setColor(Color::GetRGBToUInt32(230, 248, 255));
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

void TriBullet::UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) {
	if (animation.frameDuration <= 0) {
		setSpriteBuffer(animation.frames[0]);
	}
	else {
		setSpriteBuffer(animation.frames[animation.time / animation.frameDuration]);
	}

	drawSpriteBuffer(buffer, position.x(), position.y());

	if (animation.loop) {
		animation.time += 1;
	}

	if (animation.time >= (animation.frameCount * animation.frameDuration)) {
		animation.time = 0;
	}
}