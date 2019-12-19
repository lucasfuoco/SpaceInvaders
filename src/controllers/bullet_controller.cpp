#include <controllers/bullet_controller.hpp>

using namespace SpaceInvaders::Controllers;

BulletController::BulletController(SpaceInvaders::Game* game) : SpaceInvaders::Controller(game) {

}

BulletController::~BulletController() {

}

void BulletController::Think(void) {

	SpaceInvaders::Controller::Think();
}