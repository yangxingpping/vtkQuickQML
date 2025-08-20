#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->quickWidget->setSource(QUrl("qrc:/demo.qml"));
	auto vtkWidget = new QVTKOpenGLNativeWidget(ui->widget);

	auto layer = ui->widget->layout();
	if (!layer)
	{
		layer = new QVBoxLayout(ui->widget);
		ui->widget->setLayout(layer);
	}
	layer->addWidget(vtkWidget);

	m_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	vtkWidget->setRenderWindow(m_renderWindow);

	auto renderer = vtkSmartPointer<vtkRenderer>::New();
	m_renderWindow->AddRenderer(renderer);

	auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(1.5);

	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	renderer->SetBackground(0.5, 0.5, 0.5);
	renderer->AddActor(actor);
	renderer->ResetCamera();

}

MainWindow::~MainWindow()
{
	delete ui;
}
