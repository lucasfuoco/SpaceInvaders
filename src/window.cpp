#include <window.hpp>

using namespace SpaceInvaders;

Window::Window() :
	QWindow(),
	openGLContext(nullptr),
	shaders(new SpaceInvaders::Shaders()),
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
	delete openGLContext;
}

void Window::resizeEvent(QResizeEvent* resizeEvent) {
	if (isOpenGLFunctionsInitialized && isExposed()) {
		openGLContext->makeCurrent(this);

		glViewport(0, 0, width(), height());
	}
}

void Window::onGLInitialized(void) {
	shaders->LoadShaders(openGLContext);
	game.OnGLInitialized(this);
}

void Window::exposeEvent(QExposeEvent* exposeEvent) {
	if (!isOpenGLContextCreated) {
		openGLContext = new QOpenGLContext(this);
		QSurfaceFormat format;
		format.setVersion(3, 1);
		format.setProfile(QSurfaceFormat::CompatibilityProfile);
		format.setDepthBufferSize(24);
		format.setSamples(16);
		format.setStencilBufferSize(8);
		openGLContext->setFormat(format);
		openGLContext->create();

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

	glDisable(GL_DEPTH_TEST);

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