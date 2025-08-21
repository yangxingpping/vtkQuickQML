#pragma once
#include <QObject>

class YoungNotify : public QObject
{
	Q_OBJECT
public:
	YoungNotify(QObject* parent=nullptr);
	virtual ~YoungNotify();

	signals:
		void clickToolbar(const QPoint& pos, const QSize& size, int index);
		void hoveEnterToolbar(const QPoint& pos, const QSize& size, int index);
		void hoveLeaveToolbar(const QPoint& pos, const QSize& size, int index);

		void clickToolbar1(int index);
		void clickToolbar2(int index);

};
