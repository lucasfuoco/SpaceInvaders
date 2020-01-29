#include <spaceinvaders/controllers/saucer_controller.hpp>

using namespace SpaceInvaders::Controllers;

SaucerController::SaucerController(SpaceInvaders::Game* game) : SpaceInvaders::Controller(game),
	saucerArea()
{
	saucerArea[0].setX(2);
	saucerArea[0].setY(20);
	saucerArea[1].setX(game->GetBuffer()->size.width() - 2);
	saucerArea[1].setY(game->GetBuffer()->size.height());
}

SaucerController::~SaucerController() {

}

void SaucerController::Think(void) {
	for (int i = 0; i < game->GetSaucers()->size(); i++) {
		if (game->GetSaucers()->at(i)->GetIsDead() && (game->GetSaucers()->at(i)->GetDeathFrameCount() > 0)) {
			game->GetSaucers()->at(i)->DecrementDeathFrameCount(1);
		}

		if (!game->GetPlayer()->GetIsDead() && game->GetSaucers()->at(i)->GetSpriteInFieldOfView(game->GetPlayer())) {
			if (game->GetSaucers()->at(i)->GetCanFire(game, i)) {
				game->GetSaucers()->at(i)->Fire();
			}
		}

		if (game->GetSaucers()->at(i)->GetIsFiring() && (game->GetSaucerBulletsInFlightCount() < GAME_MAX_BULLETS_IN_FLIGHT)) {
			game->GetSaucerBullets()->at(game->GetSaucerBulletsInFlightCount())->SetX(game->GetSaucers()->at(i)->GetPosition().x() + (game->GetSaucers()->at(i)->GetSize().width() / 2));
			game->GetSaucerBullets()->at(game->GetSaucerBulletsInFlightCount())->SetY(game->GetSaucers()->at(i)->GetPosition().y() - game->GetSaucers()->at(i)->GetSize().height());
			game->GetSaucerBullets()->at(game->GetSaucerBulletsInFlightCount())->SetDirection(-2);
			game->AddSaucerBulletsInFlight(1);

			game->GetSaucers()->at(i)->Reload();
		}

		if (!game->GetSaucers()->at(i)->IsInArea(saucerArea) && !game->GetSaucers()->at(i)->GetIsDead()) {
			if (game->GetSaucers()->at(i)->GetPosition().x() <= saucerArea[0].x()) {
				// Move right
			}

			if (game->GetSaucers()->at(i)->GetPosition().x() >= saucerArea[1].x()) {
				// Move left
			}

			if (game->GetSaucers()->at(i)->GetPosition().y() >= saucerArea[1].y()) {
				// Move down
			}
		}
	}

	SpaceInvaders::Controller::Think();
}