#pragma once
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <window.hpp>
#include <iostream>

namespace SpaceInvaders {
	using namespace SpaceInvaders;

	class Application : public QApplication {
	public:
		Application(int& argc, char** argv);
		virtual ~Application();
	private:
		Window window;
	};
}