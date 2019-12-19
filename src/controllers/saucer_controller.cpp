#include <controllers/saucer_controller.hpp>

using namespace SpaceInvaders::Controllers;

SaucerController::SaucerController(SpaceInvaders::Game* game) : SpaceInvaders::Controller(game)
{

}

SaucerController::~SaucerController() {

}

void SaucerController::Think(void) {
	for (int i = 0; i < game->GetSaucers()->size(); i++) {
		if (game->GetSaucers()->at(i)->GetIsDead() && game->GetDeathCounters()->at(i)) {
			game->GetDeathCounters()->at(i) -= 1;
		}

		if (game->GetSaucers()->at(i)->GetSpriteInFieldOfView(game->GetPlayer())) {

		}
	}

	SpaceInvaders::Controller::Think();
}