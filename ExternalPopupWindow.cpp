// ExternalPopupWindow.cpp
#include "ExternalPopupWindow.h"

ExternalPopupWindow::ExternalPopupWindow(QQuickWidget* parentWidget)
    : m_parentWidget(parentWidget) {
    setFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setColor(Qt::transparent);
    setResizeMode(QQuickView::SizeRootObjectToView);
}

void ExternalPopupWindow::showAtPosition(const QPoint& globalPos, const QSize& size) {
    setPosition(globalPos);
    resize(size);
    show();
    update();
    //requestActivate();
}

bool ExternalPopupWindow::event(QEvent* event) {
    if (event->type() == QEvent::Close) {
        emit closed();
        deleteLater();
    }
    return QQuickView::event(event);
}
