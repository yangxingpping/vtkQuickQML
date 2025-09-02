#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QQmlContext>
#include <QStandardItem>
#include <QStandardItemModel>

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

#include "config.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	auto conf = new Config("first", "second", this);
	conf->load();
	conf->setLastSeenVersion("hello,world");
	auto l1 = conf->lastSeenVersion();

	conf->save();

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

	//for ui
	m_config = new YoungConfig(this);
	_notify = new YoungNotify(this);
	ui->quickWidget_ToolBar->setFixedHeight(45);
	ui->quickWidget_ToolBar->rootContext()->setContextProperty("popupHelper", this);
	ui->quickWidget_ToolBar->rootContext()->setContextProperty("youngConf", m_config);
	ui->quickWidget_ToolBar->rootContext()->setContextProperty("youngNotify", _notify);

	ui->quickWidget->rootContext()->setContextProperty("popupHelper", this);
	ui->quickWidget->rootContext()->setContextProperty("youngConf", m_config);
	ui->quickWidget->rootContext()->setContextProperty("youngNotify", _notify);
	ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

	ui->quickWidget->setSource(QUrl("qrc:/qml/demo.qml"));
	ui->quickWidget_ToolBar->setSource(QUrl("qrc:/qml/toolBarBase.qml"));
	auto errs = ui->quickWidget_ToolBar->errors();
	assert(errs.empty());
	_toolBarConfigs.push_back(PopWindowConfig{ QQuickView::SizeRootObjectToView, "qrc:/qml/ToolBarLevel1.qml" });
	_toolBarConfigs.push_back(PopWindowConfig{ QQuickView::SizeRootObjectToView, "qrc:/qml/ToolBarLevel2.qml" });

	_gObjs.push_back(ViewContext{ "youngConf", m_config });
	_gObjs.push_back(ViewContext{ "youngNotify", _notify });

	_tb = new YoungToolBar(ui->quickWidget_ToolBar, _gObjs);

	QObject::connect(_tb, &YoungToolBar::clickToolbarMenu, [this](int index, int s1, int s2)
		{
			/*if (index == 3 && s1 == 0)
			{
				auto cmd = m_cmdContainer.findCommand(CommandLeftSidebarWidgetToggle::Name);
				cmd->execute();
				int j = 1;
			}*/
		});

	_tb->Init(m_config);
	QObject::connect(_notify, &YoungNotify::clickToolbar, _tb, &YoungToolBar::onClickToolbar);
	QObject::connect(_notify, &YoungNotify::hoveEnterToolbar, _tb, &YoungToolBar::onMoveEnterToolbar);
	

	m_vtkNativeWidget = new QVTKOpenGLNativeWidget(ui->widget);

	auto layer = ui->widget->layout();
	if (!layer)
	{
		layer = new QVBoxLayout(ui->widget);
		ui->widget->setLayout(layer);
	}
	layer->setContentsMargins(0, 0, 0, 0);
	layer->addWidget(m_vtkNativeWidget);

	_initTreeView();

	statusBar()->hide();
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
	m_docView->setConfigValue("line-numbers", true);
	m_docView->setConfigValue("scrollbar-minimap", true);
	m_docView->setStatusBarEnabled(false);
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

void MainWindow::_initTreeView()
{
	QStandardItemModel* model = new QStandardItemModel(ui->treeView);
	auto root = model->invisibleRootItem();
	root->appendRow(new QStandardItem("hello"));

	root->appendRow(new QStandardItem("world"));
	auto child1 = new QStandardItem("child1");
	root->appendRow(child1);
	//child1->setCheckable(true);
	child1->appendRow(new QStandardItem("child2"));
	child1->appendRow(new QStandardItem("child3"));

	ui->treeView->setHeaderHidden(true);
	ui->treeView->setModel(model);
}

void MainWindow::showPopup(const QPoint& pos, const QSize& size, int index)
{
	qWarning() << "show pop at index=" << index;
	m_popup->setSource(QUrl("qrc:/images/next.qml"));
	assert(m_popup->status() == QQuickView::Ready);
	m_popup->showAtPosition(pos, size);
	emit topPopOpened();
}

void MainWindow::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::ActivationChange)
	{
		qDebug() << "active window changed";
		auto w2 = QGuiApplication::focusWindow();
		if (this->isActiveWindow())
		{
			qDebug() << "Application gained focus";
		}
		else if (_tb->IsActiveWindow(w2))
		{
			qDebug() << "Popup gained focus";
		}
		else
		{
			qDebug() << "Application lost focus";
			_tb->onCloseToolbar();
		}
	}
	QMainWindow::changeEvent(event);

}

void MainWindow::moveEvent(QMoveEvent* event)
{
	QMainWindow::moveEvent(event);

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	QMainWindow::resizeEvent(event);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		qDebug() << "main window mouse clicked";
		_tb->onCloseToolbar();
	}
	else if (event->type() == QEvent::NonClientAreaMouseButtonPress)
	{
		qDebug() << "main window non-client area mouse clicked";
		_tb->onCloseToolbar();
	}
	return QMainWindow::eventFilter(obj, event);
}

void MainWindow::hoveEnter(const QPoint& pos, const QSize& size, int index)
{
	qDebug() << "hover to pop index=" << index;
	if (m_popup->isVisible())
	{
		qDebug() << "start show pop up";

		m_popup->setSource(QUrl("qrc:/images/next.qml"));
		m_popup->setResizeMode(QQuickView::SizeViewToRootObject);
		m_popup->showAtPosition(pos, size);
		emit topPopOpened();
	}
}
