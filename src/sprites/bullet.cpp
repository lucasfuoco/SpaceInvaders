#include <sprites/bullet.hpp>

using namespace SpaceInvaders::Sprites;

Bullet::Bullet() : SpaceInvaders::Sprite(),
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

Bullet::~Bullet() {
	delete buffer;
}

void Bullet::ClearData(void) {
	if (buffer) {
		delete[] buffer->data;
		buffer->data = nullptr;
	}
}

int Bullet::GetDirection(void) {
	return direction;
}

void Bullet::SetDirection(int dir) {
	if (direction != dir) {
		direction = dir;
	}
}

void Bullet::ResetPosition(void) {
	position.setX(1000);
	position.setY(1000);
}