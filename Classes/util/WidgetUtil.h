//
//  WidgetUtil.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef NeglecClient_WidgetUtil_h
#define NeglecClient_WidgetUtil_h

#include "cocostudio/CocoStudio.h"

namespace WidgetUtil {
    cocos2d::ui::Widget* widgetHeaderFromJsonFile(const std::string &fileName) {
        const cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        
        auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(fileName.c_str());
        widget->setContentSize(cocos2d::Size(visibleSize.width, widget->getContentSize().height));
        widget->setPosition(cocos2d::Vec2(0, visibleSize.height - widget->getContentSize().height));
        return widget;
    }
    
    cocos2d::ui::Widget* widgetFotterFromJsonFile(const std::string &fileName) {
        const cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        
        auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile(fileName.c_str());
        widget->setContentSize(cocos2d::Size(visibleSize.width, widget->getContentSize().height));
        widget->setPosition(cocos2d::Vec2(0, 0));
        return widget;
    }
}

#endif
