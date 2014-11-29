//
//  CommonHeaderParts.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "CommonHeaderParts.h"

#include "ui/CocosGUI.h"
#include "CSLoaderUtil.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

CommonHeaderParts::CommonHeaderParts()
{
    
}

CommonHeaderParts::~CommonHeaderParts()
{
    
}

bool CommonHeaderParts::init()
{
    if (!Layer::init()) {
        return false;
    }
    this->setName("Header");
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    this->_baseLayout = CSLoaderUtil::create("HeaderParts");
    _baseLayout->setScale(winSize.width / _baseLayout->getContentSize().width);
    _baseLayout->setPosition(cocos2d::Vec2(winSize.width/2, winSize.height - _baseLayout->getContentSize().height/2));
    this->addChild(_baseLayout);

    return true;
}

void CommonHeaderParts::setTitleText(const std::string& titleName)
{
    auto labelText = utils::findChildByName<ui::Text*>(*_baseLayout, "Panel_main/Label_Title");
    labelText->setString(titleName);
}
