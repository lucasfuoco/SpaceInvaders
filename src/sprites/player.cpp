#include <sprites/player.hpp>

using namespace SpaceInvaders::Sprites;

Player::Player() : SpaceInvaders::Sprite(),
	buffer(new SpaceInvaders::SpriteBuffer()),
	deathBuffer(new SpaceInvaders::SpriteBuffer()),
	lifeCount(3),
	isFiring(false),
	isReloading(false),
	reloadDuration(10),
	reloadTime(0),
	isDead(false),
	deathFrameCount(10)
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

	deathBuffer->size.setWidth(11);
	deathBuffer->size.setHeight(7);
	deathBuffer->data = new uint8_t[77]
	{
		0,1,0,1,0,0,0,1,0,1,0, // .@.@...@.@.
		0,0,1,0,1,0,1,0,1,0,0, // ..@.@.@.@..
		0,0,0,0,0,0,0,0,0,0,0, // ...........
		1,1,0,0,0,0,0,0,0,1,1, // @@.......@@
		0,0,0,0,0,0,0,0,0,0,0, // ...........
		0,0,1,0,1,0,1,0,1,0,0, // ..@.@.@.@..
		0,1,0,1,0,0,0,1,0,1,0, // .@.@...@.@.
	};

	position.setX(107);
	position.setY(32);

	setColor(Color::GetRGBToUInt32(104, 157, 185));
	setSpriteBuffer(buffer);
}

Player::~Player() {
	delete deathBuffer;
	delete buffer;
}

void Player::UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) {
	if (isDead) {
		setColor(Color::GetRGBToUInt32(255, 229, 118));
		setSpriteBuffer(deathBuffer);
	}

	drawSpriteBuffer(buffer, position.x(), position.y());

	if (reloadTime != 0) {
		reloadTime -= 1;
	}
	else {
		isReloading = false;
	}
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

bool Player::GetIsDead(void) {
	return isDead;
}

void Player::Die(void) {
	isDead = true;
}

const int Player::GetDeathFrameCount(void) const {
	return this->deathFrameCount;
}

void Player::DecrementDeathFrameCount(int frame) {
	deathFrameCount -= frame;
}