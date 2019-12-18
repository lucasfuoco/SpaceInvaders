#pragma once
#include <iostream>

namespace SpaceInvaders {
	class Controller {
	public:
		Controller();
		virtual ~Controller();
		virtual void Think(void);
	};
}