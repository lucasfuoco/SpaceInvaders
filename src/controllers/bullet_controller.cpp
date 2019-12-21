#include <controllers/bullet_controller.hpp>

using namespace SpaceInvaders::Controllers;

BulletController::BulletController(SpaceInvaders::Game* game) : SpaceInvaders::Controller(game) {

}

BulletController::~BulletController() {

}

void BulletController::Think(void) {
	for (int i = 0; i < game->GetPlayerBulletsInFlightCount();) {
		game->GetPlayerBullets()->at(i)->SetY(game->GetPlayerBullets()->at(i)->GetPosition().y() + game->GetPlayerBullets()->at(i)->GetDirection());
		if (game->GetPlayerBullets()->at(i)->GetPosition().y() >= game->GetBuffer()->size.height())
		{
			game->GetPlayerBullets()->at(i)->ResetPosition();
			std::rotate(game->GetPlayerBullets()->begin() + i, game->GetPlayerBullets()->begin() + i + 1, game->GetPlayerBullets()->end());
			game->RemovePlayerBulletsInFlight(1);
			continue;
		}

		// Check if saucers are hit
		for (int saucerIndex = 0; saucerIndex < game->GetSaucers()->size(); saucerIndex++) {
			if (game->GetSaucers()->at(saucerIndex)->GetIsDead()) {
				continue;
			}

			if (getSpritesAreOverlaping(game->GetPlayerBullets()->at(i), game->GetSaucers()->at(saucerIndex))) {
				game->AddScore(game->GetSaucers()->at(saucerIndex)->GetDeathPoint());

				game->GetSaucers()->at(saucerIndex)->Die();

				game->GetPlayerBullets()->at(i)->ResetPosition();
				std::rotate(game->GetPlayerBullets()->begin() + i, game->GetPlayerBullets()->begin() + i + 1, game->GetPlayerBullets()->end());
				game->RemovePlayerBulletsInFlight(1);
				continue;
			}
		}

		i += 1;
	}

	SpaceInvaders::Controller::Think();
}

bool BulletController::getSpritesAreOverlaping(
	SpaceInvaders::Sprite* spriteA,
	SpaceInvaders::Sprite* spriteB
)
{
	if (
		(spriteA->GetPosition().x() < (spriteB->GetPosition().x() + spriteB->GetSize().width())) && ((spriteA->GetPosition().x() + spriteA->GetSize().width()) > spriteB->GetPosition().x()) &&
		(spriteA->GetPosition().y() < (spriteB->GetPosition().y() + spriteB->GetSize().height())) && ((spriteA->GetPosition().y() + spriteA->GetSize().height()) > spriteB->GetPosition().y())
		) {
		return true;
	}

	return false;
}