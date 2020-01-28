#include <spaceinvaders/window.hpp>

using namespace SpaceInvaders;

Window::Window() :
	QWindow(),
	openGLContext(nullptr),
	offscreenSurface(nullptr),
	shaders(new SpaceInvaders::Shaders(this)),
	game(shaders),
	isOpenGLFunctionsInitialized(false),
	isOpenGLContextCreated(false)
{
	setSurfaceType(QOpenGLWindow::OpenGLSurface);
}

Window::~Window() {
	openGLContext->makeCurrent(this);
	game.Cleanup(this);
	openGLContext->doneCurrent();

	delete shaders;
	delete offscreenSurface;
	delete openGLContext;
}

void Window::resizeEvent(QResizeEvent* resizeEvent) {
	if (isOpenGLFunctionsInitialized && isExposed()) {
		openGLContext->makeCurrent(this);
		glViewport(0, 0, width(), height());
		openGLContext->swapBuffers(this);
	}
}

void Window::onGLInitialized(void) {
	shaders->LoadShaders(openGLContext);
	game.OnGLInitialized(this);
}

void Window::exposeEvent(QExposeEvent* exposeEvent) {
	if (!isOpenGLContextCreated) {
		openGLContext = new QOpenGLContext(this);
		openGLContext->setFormat(QSurfaceFormat::defaultFormat());
		openGLContext->create();

		offscreenSurface = new QOffscreenSurface();
		offscreenSurface->setFormat(openGLContext->format());
		offscreenSurface->create();

		isOpenGLContextCreated = true;
	}

	openGLContext->makeCurrent(this);

	if (!isOpenGLFunctionsInitialized) {
		initializeOpenGLFunctions();
		onGLInitialized();
		isOpenGLFunctionsInitialized = true;
	}

	glViewport(0, 0, width(), height());

	openGLContext->swapBuffers(this);

	mainLoop();
}

void Window::wheelEvent(QWheelEvent* wheelEvent) {
	game.OnWheelEvent(wheelEvent);
}

void Window::drawFrame(void) {
	openGLContext->makeCurrent(this);

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	game.UpdateCommandBuffers(this);

	openGLContext->swapBuffers(this);
}

void Window::keyPressEvent(QKeyEvent* keyEvent) {
	game.OnKeyEvent(keyEvent);
}

void Window::mainLoop(void) {
	if (!isExposed()) {
		return;
	}

	QTimer::singleShot(0, this, [&]() {
		drawFrame();
		mainLoop();
	});	
}