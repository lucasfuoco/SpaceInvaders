#include <spaceinvaders/sprites/bullet.hpp>

using namespace SpaceInvaders::Sprites;

Bullet::Bullet() : SpaceInvaders::Sprite(),
	direction()
{

}

Bullet::~Bullet() {

}

void Bullet::ClearData(void) {
	SpaceInvaders::Sprite::ClearData();
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