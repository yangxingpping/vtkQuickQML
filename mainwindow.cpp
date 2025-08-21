#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>

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
#include <vtkNamedColors.h>
#include <ktexteditor/Editor>


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	initQtWidgets();
	initVtk();
	initKde();
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

	_initAxes(renderer);

	renderer->SetBackground(0.9, 0.9, 0.9);

	renderer->ResetCamera();

	
}

void MainWindow::initKde()
{
	auto layer = ui->widget_2->layout();
	if (!layer)
	{
		layer = new QVBoxLayout(ui->widget_2);
		ui->widget_2->setLayout(layer);
	}
	auto editor = KTextEditor::Editor::instance();
	assert(editor);
	m_doc = editor->createDocument(this);
	m_docView = m_doc->createView(ui->widget_2);
	m_docView->setConfigValue("line-numbers", false);
	m_docView->setConfigValue("scrollbar-minimap", true);
	
	layer->addWidget(m_docView);
}

void MainWindow::_initAxes(vtkSmartPointer<vtkRenderer> renderer)
{
	auto axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetTotalLength(5.0, 5.0, 5.0);
	axes->SetShaftTypeToCylinder();     
	axes->SetCylinderRadius(0.006);
	axes->SetConeRadius(0.1);
	axes->GetXAxisCaptionActor2D()->GetTextActor()->GetTextProperty()->SetColor(1, 0, 0);
	axes->GetYAxisCaptionActor2D()->GetTextActor()->GetTextProperty()->SetColor(0, 1, 0);
	axes->GetZAxisCaptionActor2D()->GetTextActor()->GetTextProperty()->SetColor(0, 0, 1);
	renderer->AddActor(axes);
}
