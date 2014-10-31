//
//  DialogSelectListViewLayer.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/31.
//
//

#include "DialogSelectListViewLayer.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

DialogSelectListViewLayer::DialogSelectListViewLayer()
: _baseLayout(nullptr)
, _okListener(nullptr)
, _closeListener(nullptr)
{
    
}

DialogSelectListViewLayer::~DialogSelectListViewLayer()
{
    
}

bool DialogSelectListViewLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // TouchEvent settings
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(DialogSelectListViewLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
//    auto winSize = Director::getInstance()->getVisibleSize();
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("ListViewLayerSelect.json");
    this->addChild(this->_baseLayout);
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_close")->addClickEventListener([this](Ref *ref) {
        if (_closeListener) _closeListener();
        this->setVisible(false);
        this->removeAllChildren();
    });
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_ok")->addClickEventListener([this](Ref *ref) {
        if (_okListener) _okListener();
    });
    
    return true;
}

bool DialogSelectListViewLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (this->isVisible()) {
        // モーダル以降のイベントを強制停止する
        return true;
    }
    return false;
}

void DialogSelectListViewLayer::pushListItem(Widget *listItem)
{
    auto listView = utils::findChildByName<ui::ListView*>(*_baseLayout, "Panel_main/ListView_list");
    listView->pushBackCustomItem(listItem);
}

void DialogSelectListViewLayer::setTitleText(const std::string& titleName)
{
    auto labelText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_title/Label_title");
    labelText->setString(titleName);
}
