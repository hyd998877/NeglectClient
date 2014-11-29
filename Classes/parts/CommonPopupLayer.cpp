//
//  CommonPopupLayer.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/11/29.
//
//

#include "CommonPopupLayer.h"

#include "ui/CocosGUI.h"
#include "CSLoaderUtil.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

CommonPopupLayer::CommonPopupLayer()
: _baseLayout(nullptr)
, _mainPanel(nullptr)
, _buttonOK(nullptr)
, _buttonNG(nullptr)
, _textTitle(nullptr)
, _textMessage(nullptr)
, _textCaution(nullptr)
{
    
}

CommonPopupLayer::~CommonPopupLayer()
{
    
}

void CommonPopupLayer::show(cocos2d::Node* target,
                 const std::string& titleText,
                 const std::string& messageText,
                 const ButtonClickCallback &callbackOK,
                 const std::string &buttonNameOK,
                 const std::string& cautionText)
{
    auto popup = CommonPopupLayer::create();
    popup->setTitleText(titleText);
    popup->setMessageText(messageText);
    
    popup->setOKButtonListener([callbackOK, popup](Ref *ref) {
        callbackOK(ref);
        popup->close();
    }, buttonNameOK);
    popup->centerButtonOK();
    
    popup->setCautionText(cautionText);
    
    popup->runShowAnimation();
    target->addChild(popup);
}

void CommonPopupLayer::show(cocos2d::Node* target,
                 const std::string& titleText,
                 const std::string& messageText,
                 const ButtonClickCallback &callbackOK,
                 const std::string &buttonNameOK,
                 const ButtonClickCallback &callbackNG,
                 const std::string &buttonNameNG,
                 const std::string& cautionText)
{
    auto popup = CommonPopupLayer::create();
    popup->setTitleText(titleText);
    popup->setMessageText(messageText);
    
    popup->setOKButtonListener(callbackOK, buttonNameOK);
    popup->setNGButtonListener([callbackNG, popup](Ref *ref) {
        callbackNG(ref);
        popup->close();
    }, buttonNameNG);
    
    popup->setCautionText(cautionText);
    
    popup->runShowAnimation();
    target->addChild(popup);
}

bool CommonPopupLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    // TouchEvent settings
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CommonPopupLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->initView();
    
    return true;
}

void CommonPopupLayer::initView()
{
    this->_baseLayout = CSLoaderUtil::create("CommonPopupLayer");
    this->addChild(this->_baseLayout);
    
    _mainPanel = utils::findChildByName<Node*>(*_baseLayout, "Panel_main");
    
    _buttonOK = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_ok");
    _buttonNG = utils::findChildByName<ui::Button*>(*_baseLayout, "Panel_main/Button_ng");

    _textTitle = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Text_title");
    _textMessage = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Text_message");
    _textCaution = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Text_caution");
}

bool CommonPopupLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (this->isVisible()) {
        // モーダル以降のイベントを強制停止する
        return true;
    }
    return false;
}

void CommonPopupLayer::setTitleText(const std::string& titleText)
{
    _textTitle->setString(titleText);
}

void CommonPopupLayer::setMessageText(const std::string& messageText)
{
    _textMessage->setString(messageText);
}

void CommonPopupLayer::setCautionText(const std::string& cautionText, Color3B textColor)
{
    _textCaution->setColor(textColor);
    _textCaution->setString(cautionText);
}

void CommonPopupLayer::setOKButtonListener(const ButtonClickCallback &callback, const std::string &buttonName)
{
    _buttonOK->setTitleText(buttonName);
    _buttonOK->addClickEventListener(callback);
}

void CommonPopupLayer::setNGButtonListener(const ButtonClickCallback &callback, const std::string &buttonName)
{
    _buttonNG->setTitleText(buttonName);
    _buttonNG->addClickEventListener(callback);
}

void CommonPopupLayer::centerButtonOK()
{
    _buttonNG->setVisible(false);
    _buttonOK->setPositionX(_mainPanel->getContentSize().width / 2);
}

void CommonPopupLayer::runShowAnimation()
{
    _mainPanel->setScale(0.0f);
    _mainPanel->runAction(ScaleTo::create(0.1f, 1.0f));
}

void CommonPopupLayer::close()
{
    this->setVisible(false);
    this->removeAllChildren();
}
