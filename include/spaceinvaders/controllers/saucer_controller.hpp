#pragma once
#include <iostream>
#include <spaceinvaders/controller.hpp>
#include <vector>
#include <spaceinvaders/game.hpp>
#include <QtWidgets>
#include <array>

namespace SpaceInvaders {
	namespace Controllers {
		enum MoveDirection {
			Left,
			Right,
			Down
		};

		class SaucerController : public SpaceInvaders::Controller {
		public:
			SaucerController(SpaceInvaders::Game* game);
			virtual ~SaucerController();
			virtual void Think(void) override;
		private:
			std::array<QPoint, 2> saucerArea;
		};
	}
}