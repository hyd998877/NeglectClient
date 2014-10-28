//
//  CommonHeaderParts.cpp
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#include "CommonHeaderParts.h"

#include "WidgetUtil.h"
#include "ui/CocosGUI.h"

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

    _baseLayout = WidgetUtil::widgetHeaderFromJsonFile("HeaderParts.json");
    this->addChild(_baseLayout);
    
    return true;
}

void CommonHeaderParts::setTitleText(const std::string& titleName)
{
    auto labelText = _baseLayout->getChildByName<ui::Text*>("Panel_main/Label_Title");
    labelText->setString(titleName);
}