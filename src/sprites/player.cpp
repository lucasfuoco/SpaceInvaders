#include <sprites/player.hpp>

using namespace SpaceInvaders::Sprites;

Player::Player() : SpaceInvaders::Sprite(),
	buffer(new SpaceInvaders::SpriteBuffer()),
	lifeCount(3),
	isFiring(false),
	isReloading(false),
	reloadDuration(10),
	reloadTime(0)
{
	buffer->size.setWidth(11);
	buffer->size.setHeight(7);
	buffer->data = new uint8_t[77]
	{
		0,0,0,0,0,1,0,0,0,0,0, // .....@.....
		0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
		0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
		0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
		1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
		1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
		1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
	};

	position.setX(107);
	position.setY(32);

	setColor(Color::GetRGBToUInt32(104, 157, 185));
	setSpriteBuffer(buffer);
}

Player::~Player() {
	delete buffer;
}

void Player::UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) {
	if (reloadTime != 0) {
		reloadTime -= 1;
	}
	else {
		isReloading = false;
	}

	SpaceInvaders::Sprite::UpdateSpriteBuffer(buffer);
}

void Player::Fire(void) {
	if (!isReloading) {
		isFiring = true;
	}
}

void Player::Reload(void) {
	isFiring = false;
	isReloading = true;
	reloadTime = reloadDuration;
}

bool Player::GetIsFiring(void) {
	return isFiring;
}

bool Player::GetIsReloading(void) {
	return isReloading;
}