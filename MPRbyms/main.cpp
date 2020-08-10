#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
	// QT Stuff
	QApplication app(argc, argv);

	MainWindow myMainWindows;
	myMainWindows.show();

	return app.exec();
}
