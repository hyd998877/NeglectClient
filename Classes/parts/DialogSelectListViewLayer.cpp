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
, _selectedIndex(-1)
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
    
    auto listView = utils::findChildByName<ui::ListView*>(*_baseLayout, "Panel_main/ListView_list");
    listView->addEventListener([this](Ref *ref, ListView::EventType eventType) {
        if (eventType != ListView::EventType::ON_SELECTED_ITEM_END) {
            return;
        }
        auto listView = static_cast<ui::ListView*>(ref);
        long selectedIndex = listView->getCurSelectedIndex();
        if (this->_selectedIndex == selectedIndex) {
            return;
        }
        
        // 行選択されたらOKボタンを有効にする
        if (this->_selectedIndex == -1) {
            auto okButton = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_ok");
            okButton->setColor(Color3B::WHITE);
            okButton->setEnabled(true);
        }
        this->_selectedIndex = selectedIndex;
        
        // 選択状態を戻す
        for (auto widget : listView->getItems()) {
            widget->setColor(Color3B::WHITE);
        }
        // TODO: 本当は背景の色を変えたい・・・Panelを被せないと？
        listView->getItem(selectedIndex)->setCascadeColorEnabled(true);
        listView->getItem(selectedIndex)->setColor(Color3B::GREEN);
    });
    
    utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_close")->addClickEventListener([this](Ref *ref) {
        if (_closeListener) _closeListener(_selectedIndex);
        this->setVisible(false);
        this->removeAllChildren();
    });

    auto okButton = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_ok");
    okButton->setColor(Color3B::BLACK);
    okButton->setEnabled(false);
    okButton->addClickEventListener([this](Ref *ref) {
        if (_okListener) _okListener(_selectedIndex);
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
    auto winSize = Director::getInstance()->getVisibleSize();
    auto baseWidth = utils::findChildByName(*_baseLayout, "Panel_back")->getContentSize().width;
    listItem->setContentSize(Size(listItem->getContentSize().width * (winSize.width / baseWidth),
                                  listItem->getContentSize().height));
    
    auto listView = utils::findChildByName<ui::ListView*>(*_baseLayout, "Panel_main/ListView_list");
    listView->pushBackCustomItem(listItem);
}

void DialogSelectListViewLayer::setTitleText(const std::string& titleName)
{
    auto labelText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Panel_title/Label_title");
    labelText->setString(titleName);
}
