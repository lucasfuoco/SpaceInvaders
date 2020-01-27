#include <spaceinvaders/application.hpp>
#include <iostream>

int main(int argc, char** argv) {
	Q_INIT_RESOURCE(spaceinvaders_resources);

	SpaceInvaders::Application application(argc, argv);
	return application.exec();
}