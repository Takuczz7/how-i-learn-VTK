#ifndef MainWindow_H
#define MainWindow_H

#include "vtkSmartPointer.h"
#include "vtkResliceImageViewer.h"
#include "vtkImagePlaneWidget.h"
#include "vtkDistanceWidget.h"
#include "vtkResliceImageViewerMeasurements.h"
#include <QMainWindow>


class Ui_MainWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:

	// Constructor/Destructor
	MainWindow(int argc, char *argv[]);
	~MainWindow() {}

	public slots:


	virtual void resliceMode(int);
	virtual void ResetViews();
	virtual void Render();
protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[3];
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[3];

protected slots:

private:

	// Designer form
	Ui_MainWindow *ui;
};

#endif // MainWindow_H
