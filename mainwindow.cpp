#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkCubeSource.h>
#include <vtkProperty.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->quickWidget->setSource(QUrl("qrc:/demo.qml"));
	m_vtkNativeWidget = new QVTKOpenGLNativeWidget(ui->widget);

	auto layer = ui->widget->layout();
	if (!layer)
	{
		layer = new QVBoxLayout(ui->widget);
		ui->widget->setLayout(layer);
	}
	layer->addWidget(m_vtkNativeWidget);

	auto cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetXLength(1.0);
	cubeSource->SetYLength(1.0);
	cubeSource->SetZLength(1.0);

	auto cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

	auto cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(0.9, 0.9, 0.9);

	

	m_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	m_vtkNativeWidget->setRenderWindow(m_renderWindow);

	auto renderer = vtkSmartPointer<vtkRenderer>::New();
	m_renderWindow->AddRenderer(renderer);

	renderer->AddActor(cubeActor);

	auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(1.5);

	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	renderer->AddActor(actor);

	renderer->SetBackground(0.9, 0.9, 0.9);
	
	renderer->ResetCamera();

}

MainWindow::~MainWindow()
{
	delete ui;
}
