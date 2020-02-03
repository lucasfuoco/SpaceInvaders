#include <spaceinvaders/application.hpp>

using namespace SpaceInvaders;

Application::Application(int& argc, char** argv) : QApplication(argc, argv) {
	QCoreApplication::setOrganizationName("Ossiaco");
	QCoreApplication::setApplicationName("SpaceInvaders");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);
#ifdef __arm__
	QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#else
	QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
#endif
	
	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::applicationName());
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("file", "The file to open.");
	parser.process(*this);

	window.setGeometry(
		QStyle::alignedRect(
			Qt::LayoutDirection::LayoutDirectionAuto,
			Qt::AlignCenter,
			QSize(1280, 800),
			qApp->desktop()->availableGeometry()
		)
	);
	window.setMinimumSize(QSize(1280, 800));
	window.show();
}

Application::~Application() {

}