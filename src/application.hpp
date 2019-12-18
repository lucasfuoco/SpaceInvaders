#pragma once
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <window.hpp>

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