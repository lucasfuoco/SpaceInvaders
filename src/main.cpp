#include <application.hpp>
#include <iostream>

using namespace SpaceInvaders;

int main(int argc, char** argv) {
	Q_INIT_RESOURCE(resources);

	Application application(argc, argv);
	return application.exec();
}