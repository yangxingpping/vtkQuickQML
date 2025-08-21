#include "YoungToolBar.h"


YoungToolBar::YoungToolBar(QQuickWidget* parent, vector<ViewContext>& ctxs)
{
	assert(parent);
    _ctxs = ctxs;
	_impl = new PopupWindowManager(parent);
    _toolBarConfigs.push_back(PopWindowConfig{ QQuickView::SizeViewToRootObject, "qrc:/qml/toolBar1.qml" });
    _toolBarConfigs.push_back(PopWindowConfig{ QQuickView::SizeViewToRootObject, "qrc:/qml/toolBar2.qml" });
}

YoungToolBar::~YoungToolBar()
{
}

bool YoungToolBar::Init(YoungConfig* conf)
{
    bool ret{ true };
    assert(_impl);
    assert(conf);
    _confs = conf;
   /* _confs->toolbarIndex(-1);
	_confs->toolbarMenu1Index(-1);
    _confs->toolbarMenu2Index(-1);*/
    _ctxs.push_back(ViewContext{ "youngToolbar", this });
    ret = _impl->Init(_toolBarConfigs, _ctxs);
    return ret;
}

bool YoungToolBar::IsActiveWindow(QWindow* active)
{
    bool ret{ false };
    if (!active)
    {
        return ret;
    }
	ret = _impl->FindPopup(active);
    return ret;
}

void YoungToolBar::onMoveEnterToolbar(const QPoint& pos, const QSize& size, int index)
{
    if (index >= _confs->toolBar().size() || _confs->toolbarIndex()==-1)
    {
        return;
    }
	auto h = calcHeight(index);
    if (_confs->toolbarIndex() !=index)
    {
        _impl->hidePopup();
    }
    auto curMenu1 = _confs->toolBarMenu(index);
    string url = "qrc:/qml/toolBar1.qml";
    //_confs->toolBarMenu1(curMenu1);
    _impl->ShowPopup(url, 0, pos.x(), pos.y(), 100, h);
    /*_confs->toolbarIndex(index);
    _confs->toolbarMenu1Index(-1);
    _confs->toolbarMenu2Index(-1);*/
}

void YoungToolBar::onMoveEnterToolsubMenu1(const QPoint& pos, int sub)
{
    auto h = calcHeight(_confs->toolbarIndex(), sub);
    if (h>0)
    {
        auto subs = _confs->getMenuItem(_confs->toolbarIndex(), sub);
        //_confs->toolBarMenu2(subs);
        auto curMenu2 = _confs->toolBarMenu(_confs->toolbarIndex(), sub);
       // _confs->toolbarMenu1Index(sub);
        _impl->ShowPopup("qrc:/qml/toolBar2.qml", 1, pos.x(), pos.y(), 100, h);
    }
    else
    {
		_impl->hidePopup(1);
    }
}

void YoungToolBar::onMoveEnterToolsubMenu2(const QPoint& pos, int sub)
{
    auto h = calcHeight(_confs->toolbarIndex(), sub);
    if (h > 0)
    {
        auto subs = _confs->toolBarMenu(_confs->toolbarIndex(), sub);
        //_confs->toolBarMenu2(subs);
        //_confs->toolbarMenu2Index(sub);
        _impl->ShowPopup("qrc:/qml/toolBar2.qml", 1, pos.x(), pos.y(), 100, h);
    }
    else
    {
        _impl->hidePopup(1);
    }
}

void YoungToolBar::onCloseToolbar()
{
    if (!_impl)
    {
        return;
    }
	_impl->hidePopup();
    /*_confs->toolbarIndex(-1);
    _confs->toolbarMenu1Index(-1);
	_confs->toolbarMenu2Index(-1);*/
	
}

int YoungToolBar::calcHeight(int toolIndex, int subIndex)
{
    assert(_confs);
    if (subIndex==-1)
    {
		auto items = _confs->toolBarMenu(toolIndex);
		return items.size() * _confs->toolMenuHeight();
    }
    else
    {
		auto items = _confs->toolBarMenu(toolIndex, subIndex);
		return items.size() * _confs->toolMenuHeight();
    }
}

bool YoungToolBar::onClickSubMenu1(int sub1)
{
    bool ret{false};if (!_impl)
    {
        return false;
    }
    auto h = calcHeight(_confs->toolbarIndex(), sub1);
    if (h>0)
    {
        qDebug() << "current click item index=" << sub1 << " has sub item";
        return false;
    }
    //_confs->toolbarMenu1Index(sub1);
    clickToolbarMenu(_confs->toolbarIndex(), _confs->toolbarMenu1Index(), _confs->toolbarMenu2Index());
    onCloseToolbar();
    ret = true; 
    return ret;
}

bool YoungToolBar::onClickSubMenu2(int sub1)
{
    bool ret{ false }; if (!_impl)
    {
        return false;
    }
    //_confs->toolbarMenu2Index(sub1);
    clickToolbarMenu(_confs->toolbarIndex(), _confs->toolbarMenu1Index(), _confs->toolbarMenu2Index());
    onCloseToolbar();
    ret = true;
    return ret;
}

void YoungToolBar::onClickToolbar(const QPoint& pos, const QSize& size, int index)
{
    if (index >= _confs->toolBar().size())
    {
        assert(0);
        return;
    }
    string url = "qrc:/images/toolBar1.qml";
    if (_confs->toolbarIndex() !=index)
    {
        _impl->hidePopup(0);
    }
    auto curMenu1 = _confs->toolBarMenu(index);
    if (curMenu1.empty())
    {
        return;
	}
    //_confs->toolBarMenu1(curMenu1);
    _impl->ShowPopup(url, 0, pos.x(), pos.y(), 100, calcHeight(index));
    /*_confs->toolbarIndex(index);
    _confs->toolbarMenu1Index(-1);
    _confs->toolbarMenu2Index(-1);*/
}
