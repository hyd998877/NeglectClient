//
//  DialogShowListViewLayer.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/31.
//
//

#include "DialogShowListViewLayer.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

DialogShowListViewLayer::DialogShowListViewLayer()
: _baseLayout(nullptr)
, _closeListener(nullptr)
{
    
}

DialogShowListViewLayer::~DialogShowListViewLayer()
{
    
}

bool DialogShowListViewLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    // TouchEvent settings
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(DialogShowListViewLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
//    auto winSize = Director::getInstance()->getVisibleSize();
    this->_baseLayout = GUIReader::getInstance()->widgetFromJsonFile("ListViewLayerShow.json");
    this->addChild(this->_baseLayout);
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_close")->addClickEventListener([this](Ref *ref) {
        if (_closeListener) _closeListener();
        this->setVisible(false);
        this->removeAllChildren();
    });
    
    return true;
}

bool DialogShowListViewLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (this->isVisible()) {
        // モーダル以降のイベントを強制停止する
        return true;
    }
    return false;
}

void DialogShowListViewLayer::pushListItem(Widget *listItem)
{
    auto winSize = Director::getInstance()->getVisibleSize();
    auto baseWidth = utils::findChildByName(*_baseLayout, "Panel_back")->getContentSize().width;
    listItem->setContentSize(Size(listItem->getContentSize().width * (winSize.width / baseWidth),
                                  listItem->getContentSize().height));
    
    auto listView = utils::findChildByName<ui::ListView*>(*_baseLayout, "Panel_main/ListView_list");
    listView->pushBackCustomItem(listItem);
}

void DialogShowListViewLayer::setTitleText(const std::string& titleName)
{
    auto labelText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_title/Label_title");
    labelText->setString(titleName);
}
