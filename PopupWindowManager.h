#pragma once
#include <vector>
#include <string>
#include <QObject>
#include <QQuickView>
#include "ExternalPopupWindow.h"
using std::string;
using std::vector;
using std::initializer_list;
class PopWindowConfig
{
public:
	QQuickView::ResizeMode mode{ QQuickView::SizeViewToRootObject };
	string url;
};

class ViewContext
{
public:
	string name;
	QObject* obj{ nullptr };
};

class PopupWindowManager : public QObject
{
	Q_OBJECT
public:
	PopupWindowManager(QQuickWidget* p=nullptr);
	virtual ~PopupWindowManager();
	bool Init(initializer_list<PopWindowConfig> config, initializer_list<ViewContext> contexts);
	bool Init(vector<PopWindowConfig> configs, vector<ViewContext> contexts);
	bool FindPopup(QWindow* handle);
signals:
	void moveEnter0(int index);
	void moveLeave0(int index);
	void click0(int index);
	void moveEnter1(int index);
	void moveLeave1(int index);
	void click1(int index);
public slots:
	bool ShowPopup(std::string url, int index, int x, int y, int w=100, int h=200);
	bool hidePopup(int index);
	bool hidePopup();
	bool clickPopup(int index);
	void clickToolbar1(int index);
private:
	QQuickWidget* _quickWidget{nullptr}; // Main widget for displaying popups
	vector<ExternalPopupWindow*> _popupWindows; // List of popup windows
};
