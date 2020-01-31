#include <spaceinvaders/window.hpp>

using namespace SpaceInvaders;

Window::Window() :
	QWindow(),
	openGLContext(nullptr),
	offscreenSurface(nullptr),
	debugLogger(nullptr),
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
	delete debugLogger;
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
	connect(
		debugLogger,
		&QOpenGLDebugLogger::messageLogged,
		this,
		&Window::onDebugMessageLogged
	);
	debugLogger->startLogging();

	shaders->LoadShaders(openGLContext);
	game.OnGLInitialized(this);
}

void Window::exposeEvent(QExposeEvent* exposeEvent) {
	if (!isOpenGLContextCreated) {
		openGLContext = new QOpenGLContext(this);

		QSurfaceFormat surfaceFormat;
		surfaceFormat.setOption(QSurfaceFormat::DebugContext);
		surfaceFormat.setVersion(3, 3);
		surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);

		debugLogger = new QOpenGLDebugLogger(this);
		debugLogger->initialize();

		openGLContext->setFormat(surfaceFormat);
		openGLContext->hasExtension(QByteArrayLiteral("GL_KHR_debug"));
		openGLContext->create();

		offscreenSurface = new QOffscreenSurface();
		offscreenSurface->setFormat(openGLContext->format());
		offscreenSurface->create();

		isOpenGLContextCreated = true;
	}

	openGLContext->makeCurrent(offscreenSurface);

	if (!isOpenGLFunctionsInitialized) {
		initializeOpenGLFunctions();
		onGLInitialized();

		isOpenGLFunctionsInitialized = true;
	}

	glViewport(0, 0, width(), height());

	openGLContext->swapBuffers(offscreenSurface);

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

void Window::onDebugMessageLogged(void) {
	const QList<QOpenGLDebugMessage> messages = debugLogger->loggedMessages();
	for (const QOpenGLDebugMessage& message : messages)
		qDebug() << message;
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