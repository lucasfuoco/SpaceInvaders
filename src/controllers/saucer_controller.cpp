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
			game->GetSaucers()->at(i)->Fire();
		}

		if (game->GetSaucers()->at(i)->GetIsFiring() && (game->GetSaucerBulletsInFlightCount() < GAME_MAX_BULLETS_IN_FLIGHT)) {
			game->GetSaucerBullets()->at(game->GetSaucerBulletsInFlightCount())->SetX(game->GetSaucers()->at(i)->GetPosition().x() + (game->GetSaucers()->at(i)->GetSize().width() / 2));
			game->GetSaucerBullets()->at(game->GetSaucerBulletsInFlightCount())->SetY(game->GetSaucers()->at(i)->GetPosition().y() - game->GetSaucers()->at(i)->GetSize().height());
			game->GetSaucerBullets()->at(game->GetSaucerBulletsInFlightCount())->SetDirection(-1);
			game->AddSaucerBulletsInFlight(1);

			game->GetSaucers()->at(i)->Reload();
		}
	}

	SpaceInvaders::Controller::Think();
}