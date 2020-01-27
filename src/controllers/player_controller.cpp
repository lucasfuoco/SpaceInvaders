#include <spaceinvaders/controllers/player_controller.hpp>

using namespace SpaceInvaders::Controllers;

PlayerController::PlayerController(SpaceInvaders::Game* game) : SpaceInvaders::Controller(game) {

}

PlayerController::~PlayerController() {

}

void PlayerController::Think(void) {
	if (game->GetPlayer()->GetIsDead() && (game->GetPlayer()->GetDeathFrameCount() > 0)) {
		game->GetPlayer()->DecrementDeathFrameCount(1);
	}

	if (game->GetPlayer()->GetIsFiring() && (game->GetPlayerBulletsInFlightCount() < GAME_MAX_BULLETS_IN_FLIGHT)) {
		game->GetPlayerBullets()->at(game->GetPlayerBulletsInFlightCount())->SetX(game->GetPlayer()->GetPosition().x() + (game->GetPlayer()->GetSize().width() / 2));
		game->GetPlayerBullets()->at(game->GetPlayerBulletsInFlightCount())->SetY(game->GetPlayer()->GetPosition().y() + game->GetPlayer()->GetSize().height());
		game->GetPlayerBullets()->at(game->GetPlayerBulletsInFlightCount())->SetDirection(4);
		game->AddPlayerBulletsInFlight(1);

		game->GetPlayer()->Reload();
	}

	SpaceInvaders::Controller::Think();
}