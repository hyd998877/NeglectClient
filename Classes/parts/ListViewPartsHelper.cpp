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

constexpr static auto LIST_PARTS_LABEL_TEXT = "Label_text";
constexpr static auto LIST_PARTS_IMAGE_ICON = "Image_icon";

cocos2d::ui::Widget* ListViewPartsHelper::createListViewShortTextParts(const std::string &text)
{
    auto parts = GUIReader::getInstance()->widgetFromJsonFile("ListPartsShortText.json");
    utils::findChildByName<ui::Text*>(*parts, LIST_PARTS_LABEL_TEXT)->setString(text);
    return parts;
}

cocos2d::ui::Widget* ListViewPartsHelper::createListViewTextParts(const std::string &text)
{
    auto parts = GUIReader::getInstance()->widgetFromJsonFile("ListPartsText.json");
    utils::findChildByName<ui::Text*>(*parts, LIST_PARTS_LABEL_TEXT)->setString(text);
    return parts;
}

cocos2d::ui::Widget* ListViewPartsHelper::createListViewIconTextParts(const std::string &fileName, const std::string &text)
{
    auto parts = GUIReader::getInstance()->widgetFromJsonFile("ListPartsIconText.json");
    utils::findChildByName<ui::Text*>(*parts, LIST_PARTS_LABEL_TEXT)->setString(text);
    utils::findChildByName<ui::ImageView*>(*parts, LIST_PARTS_IMAGE_ICON)->loadTexture(fileName);
    return parts;
}

cocos2d::ui::Widget* ListViewPartsHelper::createListViewTextParts(const std::string &text1, const std::string &text2)
{
    auto parts = GUIReader::getInstance()->widgetFromJsonFile("QuestListParts.json");
    utils::findChildByName<ui::Text*>(*parts, "Label_dName_1")->setString(text1);
    utils::findChildByName<ui::Text*>(*parts, "Label_dName_2")->setString(text2);
    return parts;
}
