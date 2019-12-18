#pragma once
#include <iostream>
#include <controller.hpp>

namespace SpaceInvaders {
	namespace Controllers {
		class SaucerController : public Controller {
		public:
			SaucerController();
			virtual ~SaucerController();
			virtual void Think(void) override;
		};
	}
}