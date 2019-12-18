#include <sprites/player_bullet.hpp>

using namespace SpaceInvaders::Sprites;

PlayerBullet::PlayerBullet() : SpaceInvaders::Sprite(),
	buffer(new SpaceInvaders::SpriteBuffer()),
	direction()
{
	buffer->size.setWidth(1);
	buffer->size.setHeight(3);
	buffer->data = new uint8_t[3]
	{
		1, // @
		1, // @
		1  // @
	};

	position.setX(1000);
	position.setY(1000);

	setColor(Color::GetRGBToUInt32(255, 244, 182));
	setSpriteBuffer(buffer);
}

PlayerBullet::~PlayerBullet() {
	delete buffer;
}

void PlayerBullet::ClearData(void) {
	if (buffer) {
		delete[] buffer->data;
		buffer->data = nullptr;
	}
}

int PlayerBullet::GetDirection(void) {
	return direction;
}

void PlayerBullet::SetDirection(int dir) {
	if (direction != dir) {
		direction = dir;
	}
}

void PlayerBullet::ResetPosition(void) {
	position.setX(1000);
	position.setY(1000);
}