#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include "ktexteditor/Document"
#include "ktexteditor/View"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void initQtWidgets();
    void initVtk();
    void initKde();

    void _initAxes(vtkSmartPointer<vtkRenderer> render);


    Ui::MainWindow *ui;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    QVTKOpenGLNativeWidget* m_vtkNativeWidget{ nullptr };

    KTextEditor::View* m_docView{ nullptr };
	KTextEditor::Document* m_doc{ nullptr };
};
#endif // MAINWINDOW_H
