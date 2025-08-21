#include "mainwindow.h"

#include <QApplication>
#include <qquickwindow.h>
#include <QStyleFactory>
#include <ktexteditor/Document>
#include <ktexteditor/Editor>

void fakecall()
{
	auto instance = KTextEditor::Editor::instance();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fakecall();
	QQuickWindow::setSceneGraphBackend("opengl");
    qputenv("QSG_RHI_BACKEND", "opengl");
    /*QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);*/
    auto styles = QStyleFactory::keys();
	auto style = QStyleFactory::create("Breeze");
    qApp->setStyle(style);
    MainWindow w;
    
    w.show();
    return a.exec();
}
