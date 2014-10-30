//
//  ListViewPartsHelper.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/31.
//
//

#include "ListViewPartsHelper.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio;
using namespace ui;

cocos2d::ui::Widget* ListViewPartsHelper::createListViewTextParts(const std::string &text)
{
    auto parts = GUIReader::getInstance()->widgetFromJsonFile("ListPartsText.json");
    utils::findChildByName<ui::Text*>(*parts, "Label_text")->setString(text);
    return parts;
}

cocos2d::ui::Widget* ListViewPartsHelper::createListViewIconTextParts(const std::string &fileName, const std::string &text)
{
    auto parts = GUIReader::getInstance()->widgetFromJsonFile("ListPartsIconText.json");
    utils::findChildByName<ui::Text*>(*parts, "Label_text")->setString(text);
    utils::findChildByName<ui::ImageView*>(*parts, "Image_icon")->loadTexture(fileName);
    return parts;
}
