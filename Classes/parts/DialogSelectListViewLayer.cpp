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
        this->setVisible(false);
        this->removeAllChildren();
    });
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_ok")->addClickEventListener([this](Ref *ref) {
        CCLOG("OK! callback");
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

void DialogSelectListViewLayer::setTitleText(const std::string& titleName)
{
    
}
