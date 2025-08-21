
#include "YoungConfig.h"

YoungConfig::YoungConfig(QObject *parent) : QObject(parent) 
{
	_toolBar = { "File", "Display", "Tools", "Window", "Help" };
	_toolBarSubMenus.insert({ "0", {"New", "Open", "Recent files"} });
	_toolBarSubMenus.insert({ "1", {"Projection", "Mode"} });
	_toolBarSubMenus.insert({ "2", {"Save View to Image", "Options"} });
	_toolBarSubMenus.insert({ "3", {"Show Left Sidebar", "Fullscreen"} });
	_toolBarSubMenus.insert({ "4", {"About", "Help"} });

    _toolBarSubMenus.insert({ "0_1", {"s1", "s2", "s3", "s4"} });
	_toolBarSubMenus.insert({ "1_1", {"s3", "s4", "s5"} });
}

QStringList YoungConfig::getMenuItem(int sub, int sub2/* = -1*/)
{
	QString key;
	if (sub == -1 && sub2 == -1)
	{
		return QStringList();
	}
	if (sub2 == -1)
	{
		key = QString("%1").arg(sub);
	}
	else
	{
		key = QString("%1_%2").arg(sub).arg(sub2);
	}
	if (_toolBarSubMenus.find(key.toStdString()) != _toolBarSubMenus.end())
	{
		return _toolBarSubMenus.at(key.toStdString());
	}

	return QStringList();
}

YoungConfig::~YoungConfig() 
{
}

int YoungConfig::toolMenuHeight() const
{
	return _toolMenuHeight;
}

QStringList YoungConfig::toolBarMenu(int sub1, int sub2/* = -1*/) const
{
	QString key;
	assert(sub1 != -1);
	if (sub2==-1)
	{
		key = QString("%1").arg(sub1);
	}
	else
	{
		key = QString("%1_%2").arg(sub1).arg(sub2);
	}
	if (_toolBarSubMenus.find(key.toStdString()) != _toolBarSubMenus.end())
	{
		return _toolBarSubMenus.at(key.toStdString());
	}
	return QStringList();
}
