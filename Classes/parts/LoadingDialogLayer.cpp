//
//  LoadingDialogLayer.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/11/24.
//
//

#include "LoadingDialogLayer.h"

#include "ui/CocosGUI.h"
#include "CSLoaderUtil.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

LoadingDialogLayer::LoadingDialogLayer()
: _baseLayout(nullptr)
{
    
}

LoadingDialogLayer::~LoadingDialogLayer()
{
    
}

bool LoadingDialogLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // TouchEvent settings
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(LoadingDialogLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //    auto winSize = Director::getInstance()->getVisibleSize();
    this->_baseLayout = CSLoaderUtil::create("LoadingLayer");
    this->addChild(this->_baseLayout);
    
    return true;
}

bool LoadingDialogLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (this->isVisible()) {
        // モーダル以降のイベントを強制停止する
        return true;
    }
    return false;
}

void LoadingDialogLayer::setTitleText(const std::string& titleName)
{

}
