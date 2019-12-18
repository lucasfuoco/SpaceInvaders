#include <sprites/saucer.hpp>

using namespace SpaceInvaders;
using namespace SpaceInvaders::Sprites;

Saucer::Saucer() : Sprite(),
	deathBuffer(new SpaceInvaders::SpriteBuffer()),
	isDead(false),
	deathPoint(10)
{
	deathBuffer->size.setWidth(13);
	deathBuffer->size.setHeight(7);
	deathBuffer->data = new uint8_t[91]
	{
		0,1,0,0,1,0,0,0,1,0,0,1,0, // .@..@...@..@.
		0,0,1,0,0,1,0,1,0,0,1,0,0, // ..@..@.@..@..
		0,0,0,1,0,0,0,0,0,1,0,0,0, // ...@.....@...
		1,1,0,0,0,0,0,0,0,0,0,1,1, // @@.........@@
		0,0,0,1,0,0,0,0,0,1,0,0,0, // ...@.....@...
		0,0,1,0,0,1,0,1,0,0,1,0,0, // ..@..@.@..@..
		0,1,0,0,1,0,0,0,1,0,0,1,0  // .@..@...@..@.
	};
}

Saucer::~Saucer() {
	delete deathBuffer;
}

void Saucer::ClearData(void) {
	if (deathBuffer->data) {
		delete[] deathBuffer->data;
		deathBuffer->data = nullptr;
	}

	Sprite::ClearData();
}

void Saucer::UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) {
	if (isDead) {
		setColor(Color::GetRGBToUInt32(174, 0, 0));
		setSpriteBuffer(deathBuffer);
	}
	else {
		if (animation.frameDuration <= 0) {
			setSpriteBuffer(animation.frames[0]);
		}
		else {
			setSpriteBuffer(animation.frames[animation.time / animation.frameDuration]);
		}
	}

	drawSpriteBuffer(buffer, position.x(), position.y());

	if (animation.loop) {
		animation.time += 1;
	}

	if (animation.time >= (animation.frameCount * animation.frameDuration)) {
		animation.time = 0;
	}
}

void Saucer::Die(void) {
	if (!isDead) {
		isDead = true;
	}
}

bool Saucer::GetIsDead(void) {
	return isDead;
}

int Saucer::GetDeathPoint(void) {
	return deathPoint;
}

void Saucer::setDeathPoint(int point) {
	if (deathPoint != point) {
		deathPoint = point;
	}
}