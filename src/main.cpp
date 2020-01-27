#include <spaceinvaders/application.hpp>
#include <iostream>

int main(int argc, char** argv) {
	SpaceInvaders::Application application(argc, argv);
	return application.exec();
}