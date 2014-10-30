//
//  ListViewPartsHelper.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/31.
//
//

#ifndef __NeglecClient__ListViewPartsHelper__
#define __NeglecClient__ListViewPartsHelper__

#include "cocos2d.h"

class ListViewPartsHelper
{
public:
    static cocos2d::ui::Widget* createListViewTextParts(const std::string &text);
    static cocos2d::ui::Widget* createListViewIconTextParts(const std::string &fileName, const std::string &text);
};

#endif /* defined(__NeglecClient__ListViewPartsHelper__) */
