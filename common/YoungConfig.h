#pragma once
#include <vector>
#include <map>
#include <string>
#include <QQmlEngine>
#include <QColor>
#include <QStringList>

#include "YoungMacro.h"

using std::vector;
using std::map;
using std::string;

class YoungConfig : public QObject {
	Q_OBJECT
	//QML_SINGLETON
	QML_ELEMENT;
	Q_PROPERTY_AUTO(int, toolbarIndex);
	Q_PROPERTY_AUTO(int, toolbarMenu1Index);
	Q_PROPERTY_AUTO(int, toolbarMenu2Index);
	Q_PROPERTY_AUTO(QStringList, toolBar);
	Q_PROPERTY_AUTO(QStringList, toolBarMenu1);
	Q_PROPERTY_AUTO(QStringList, toolBarMenu2);
	Q_PROPERTY_AUTO(bool, darkMode);
public:
	YoungConfig(QObject* parent=nullptr);
	virtual ~YoungConfig();

	int toolMenuHeight() const;

	QStringList getMenuItem(int sub, int sub2 = -1);
public slots:
	QStringList toolBarMenu(int sub1, int sub2=-1) const;
signals:
private:
	int _toolMenuHeight{ 50 };
	map<string, QStringList> _toolBarSubMenus;
};
