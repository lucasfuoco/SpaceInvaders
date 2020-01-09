#include <sprites/saucer.hpp>
#include <game.hpp>

using namespace SpaceInvaders;
using namespace SpaceInvaders::Sprites;

Saucer::Saucer() : Sprite(),
	deathBuffer(new SpaceInvaders::SpriteBuffer()),
	isDead(false),
	deathPoint(10),
	isFiring(false),
	isReloading(false),
	reloadDuration(30),
	reloadTime(0)
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

	if (reloadTime != 0) {
		reloadTime -= 1;
	}
	else {
		isReloading = false;
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

bool Saucer::GetSpriteInFieldOfView(const SpaceInvaders::Sprite* sprite) {
	if (
		sprite->GetPosition().x() <= (position.x() + (sprite->GetSize().width() / 2)) &&
		sprite->GetPosition().x() >= (position.x() - (sprite->GetSize().width() / 2))
	) {
		return true;
	}

	return false;
}

void Saucer::Fire(void) {
	if (!isReloading) {
		isFiring = true;
	}
}

void Saucer::Reload(void) {
	isFiring = false;
	isReloading = true;
	reloadTime = reloadDuration;
}

bool Saucer::GetIsFiring(void) {
	return isFiring;
}

bool Saucer::GetIsReloading(void) {
	return isReloading;
}

bool Saucer::CanFire(SpaceInvaders::Game* game, int index) {
	for (int s = (index - game->GetSaucerMatrix()->width()); s > 0;) {
		if (!game->GetSaucers()->at(s)->GetIsDead()) {
			return false;
		}

		s -= game->GetSaucerMatrix()->width();
	}

	if (isDead) {
		return false;
	}

	return true;
}

void Saucer::setDeathPoint(int point) {
	if (deathPoint != point) {
		deathPoint = point;
	}
}

void Saucer::setReloadDuration(int duration) {
	if (reloadDuration != duration) {
		reloadDuration = duration;
	}
}