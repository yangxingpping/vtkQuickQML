#pragma once
#include "PopupWindowManager.h"
#include "YoungConfig.h"

class YoungToolBar : public QObject
{
	Q_OBJECT
public:
	YoungToolBar(QQuickWidget* parent, vector<ViewContext>& ctxs);
	virtual ~YoungToolBar();
	bool Init(YoungConfig* conf);
	bool IsActiveWindow(QWindow* active);
public slots:
	//interface for operate on toolbar
	void onClickToolbar(const QPoint& pos, const QSize& size, int index);
	void onMoveEnterToolbar(const QPoint& pos, const QSize& size, int index);

	//interface for operate on sub menu
	void onMoveEnterToolsubMenu1(const QPoint& pos, int sub);
	bool onClickSubMenu1(int sub);

	void onMoveEnterToolsubMenu2(const QPoint& pos, int sub);
	bool onClickSubMenu2(int sub);

	void onCloseToolbar();
	int calcHeight(int toolIndex, int subIndex=-1);

	signals:
		void clickToolbarMenu(int index, int sub1, int sub2);
	
private:
	PopupWindowManager* _impl{};
	vector<PopWindowConfig> _toolBarConfigs;
	vector<ViewContext> _ctxs;
	YoungConfig* _confs{ nullptr };
};
