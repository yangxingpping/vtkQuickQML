#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include "ktexteditor/Document"
#include "ktexteditor/View"

#include "YoungConfig.h"
#include "YoungNotify.h"
#include "ExternalPopupWindow.h"
#include "YoungToolBar.h"

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

signals:
    void topPopClosed();
    void maskClosed();
    void topPopOpened();
    void maskOpened();
public slots:
    void showPopup(const QPoint& pos, const QSize& size, int index);
    void hoveEnter(const QPoint& pos, const QSize& size, int index);
protected:
    void changeEvent(QEvent* event) override;
    void moveEvent(QMoveEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:

    void initQtWidgets();
    void initVtk();
    void initKde();

    void _initAxes(vtkSmartPointer<vtkRenderer> render);


    void _initTreeView();

    Ui::MainWindow *ui;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    QVTKOpenGLNativeWidget* m_vtkNativeWidget{ nullptr };

    KTextEditor::View* m_docView{ nullptr };
	KTextEditor::Document* m_doc{ nullptr };


    YoungConfig* m_config{ nullptr };
	YoungNotify* _notify{ nullptr };
    ExternalPopupWindow* m_popup = nullptr;
    vector<ViewContext> _gObjs;
    vector<PopWindowConfig> _toolBarConfigs;
    YoungToolBar* _tb{ nullptr };
};
#endif // MAINWINDOW_H
