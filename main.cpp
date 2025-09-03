#include "mainwindow.h"

#include <QApplication>
#include <qquickwindow.h>
#include <QStyleFactory>
#include <ktexteditor/Document>
#include <ktexteditor/Editor>
#include <KCrash>

#include <QFile>

void fakecall()
{
	auto instance = KTextEditor::Editor::instance();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KCrash::initialize();
    auto emergencySave = [](int tag) {
        QFile f("crash_recovery.log");
        if (f.open(QIODevice::WriteOnly))
            f.write("App crashed, unsaved data dumped...\n");
        };
    KCrash::setEmergencySaveFunction(emergencySave);
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
