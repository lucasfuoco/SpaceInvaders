#include <sprites/bullets/di_bullet.hpp>

using namespace SpaceInvaders::Sprites::Bullets;

DiBullet::DiBullet() : SpaceInvaders::Sprites::Bullet(),
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

	animation.loop = true;
	animation.frameCount = 2;
	animation.frameDuration = 2;
	animation.time = 0;
	animation.frames.push_back(buffer1);
	animation.frames.push_back(buffer2);

	setColor(Color::GetRGBToUInt32(255, 220, 255));
}

DiBullet::~DiBullet() {
	delete buffer1;
	delete buffer2;
}

void DiBullet::ClearData(void) {
	if (buffer1) {
		delete[] buffer1->data;
		buffer1->data = nullptr;
	}

	if (buffer2) {
		delete[] buffer2->data;
		buffer2->data = nullptr;
	}
}

void DiBullet::UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) {
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