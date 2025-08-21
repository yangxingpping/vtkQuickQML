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
#include <vtkAxesActor.h>
#include <vtkCaptionActor2D.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	initQtWidgets();
	initVtk();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initQtWidgets()
{
	ui->quickWidget->setSource(QUrl("qrc:/demo.qml"));
	m_vtkNativeWidget = new QVTKOpenGLNativeWidget(ui->widget);

	auto layer = ui->widget->layout();
	if (!layer)
	{
		layer = new QVBoxLayout(ui->widget);
		ui->widget->setLayout(layer);
	}
	layer->addWidget(m_vtkNativeWidget);
}

void MainWindow::initVtk()
{
	m_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	m_vtkNativeWidget->setRenderWindow(m_renderWindow);

	auto renderer = vtkSmartPointer<vtkRenderer>::New();
	m_renderWindow->AddRenderer(renderer);


	auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(1.5);

	auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	auto actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	renderer->AddActor(actor);

	_initCube(renderer);

	renderer->SetBackground(0.9, 0.9, 0.9);

	renderer->ResetCamera();

	
}

void MainWindow::_initCube(vtkSmartPointer<vtkRenderer> renderer)
{
	auto cubeSource = vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->SetCenter(5.0, 0.0, 0.0);
	cubeSource->SetXLength(1.0);
	cubeSource->SetYLength(1.0);
	cubeSource->SetZLength(1.0);

	auto cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cubeSource->GetOutputPort());

	auto cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(0.9, 0.9, 0.9);

	renderer->AddActor(cubeActor);

	auto axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetTotalLength(2.0, 2.0, 2.0);
	axes->SetShaftTypeToCylinder();     
	axes->SetCylinderRadius(0.02);
	axes->GetXAxisCaptionActor2D()->GetTextActor()->GetTextProperty()->SetColor(1, 0, 0);
	axes->GetYAxisCaptionActor2D()->GetTextActor()->GetTextProperty()->SetColor(0, 1, 0);
	axes->GetZAxisCaptionActor2D()->GetTextActor()->GetTextProperty()->SetColor(0, 0, 1);
	renderer->AddActor(axes);
}
