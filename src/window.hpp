#pragma once
#include <QtWidgets>
#include <game.hpp>
#include <shaders.hpp>
#include <vector>

namespace SpaceInvaders {
	using namespace SpaceInvaders;

	class Window : public QWindow, public QOpenGLExtraFunctions {
	public:
		Window();
		virtual ~Window();
	protected:
		virtual void resizeEvent(QResizeEvent* resizeEvent) override;
		virtual void exposeEvent(QExposeEvent* exposeEvent) override;
		virtual void wheelEvent(QWheelEvent* wheelEvent) override;
		virtual void keyPressEvent(QKeyEvent* keyEvent) override;
		void onGLInitialized(void);
		void drawFrame(void);
	private:
		void mainLoop(void);

		SpaceInvaders::Shaders* shaders;
		QOpenGLContext* openGLContext;
		bool isOpenGLFunctionsInitialized;
		bool isOpenGLContextCreated;
		Game game;
	};
}