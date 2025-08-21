#include "mainwindow.h"

#include <QApplication>
#include <qquickwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickWindow::setSceneGraphBackend("opengl");
    qputenv("QSG_RHI_BACKEND", "opengl");
    /*QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);*/
    MainWindow w;
    
    w.show();
    return a.exec();
}
