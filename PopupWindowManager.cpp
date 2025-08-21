
#include "PopupWindowManager.h"

#include <QQmlContext>
#include <QTimer>

PopupWindowManager::PopupWindowManager(QQuickWidget* p/* = nullptr*/)
	:_quickWidget(p)
{
	assert(_quickWidget);
}

PopupWindowManager::~PopupWindowManager()
{
}

bool PopupWindowManager::Init(initializer_list<PopWindowConfig> config, initializer_list<ViewContext> contexts)
{
	bool ret{ true };
	_popupWindows.clear();
	for (auto& conf: config)
	{
		auto pop = new ExternalPopupWindow(_quickWidget);
		for (auto& ctx: contexts)
		{
			assert(ctx.obj);
			pop->rootContext()->setContextProperty(QString::fromStdString(ctx.name), ctx.obj);
		}
		pop->rootContext()->setContextProperty(QString::fromStdString("youngRoot"), this);
		pop->setResizeMode(conf.mode);
		pop->setSource(QUrl(QString::fromStdString(conf.url)));
		_popupWindows.push_back(pop);
	}
	return ret;
}

bool PopupWindowManager::Init(vector<PopWindowConfig> config, vector<ViewContext> contexts)
{
	bool ret{ true };
	_popupWindows.clear();
	for (auto& conf : config)
	{
		auto pop = new ExternalPopupWindow(_quickWidget);
		for (auto& ctx : contexts)
		{
			assert(ctx.obj);
			pop->rootContext()->setContextProperty(QString::fromStdString(ctx.name), ctx.obj);
		}
		pop->rootContext()->setContextProperty(QString::fromStdString("youngRoot"), this);
		pop->setResizeMode(conf.mode);
		pop->setSource(QUrl(QString::fromStdString(conf.url)));
		_popupWindows.push_back(pop);
	}
	return ret;
}

bool PopupWindowManager::FindPopup(QWindow* handle)
{
	bool ret{ false };
	for (auto& pop: _popupWindows)
	{
		ret = (pop == handle);
		if (ret)
		{
			break;
		}
	}
	return ret;
}

bool PopupWindowManager::hidePopup(int index)
{
	bool ret{ false };
	if (index<0 || index>=_popupWindows.size())
	{
		return ret;
	}
	//qDebug() << "hide popup at index=" << index;
	auto pop = _popupWindows[index];
	pop->hide();
	ret = true;
	return ret;
}

bool PopupWindowManager::hidePopup()
{
	bool ret{ true };
	for (int i = 0; i < _popupWindows.size(); ++i)
	{
		ret = this->hidePopup(i);
	}
	return ret;
}

bool PopupWindowManager::clickPopup(int index)
{
	bool ret{ true };

	return ret;
}

void PopupWindowManager::clickToolbar1(int index)
{
}

bool PopupWindowManager::ShowPopup(std::string url, int index, int x, int y, int w, int h)
{
	bool ret{ false };
	if (index < 0 || index >= _popupWindows.size())
	{
		return ret;
	}
	auto pop = _popupWindows[index];
	pop->setResizeMode(QQuickView::SizeRootObjectToView);
	pop->setSource(QUrl(QString::fromStdString(url)));
	pop->showAtPosition(QPoint(x, y), QSize(w, h));
	ret = true;
	return ret;
}
