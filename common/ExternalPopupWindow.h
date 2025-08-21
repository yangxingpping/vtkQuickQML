#pragma once

#include <QQuickView>

class ExternalPopupWindow : public QQuickView
{
    Q_OBJECT
public:
    explicit ExternalPopupWindow(QQuickWidget* parentWidget);

    void showAtPosition(const QPoint& globalPos, const QSize& size);

signals:
    void closed();

protected:
    bool event(QEvent* event) override;

private:
    QQuickWidget* m_parentWidget;
};
