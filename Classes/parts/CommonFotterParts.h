//
//  CommonFotterParts.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__CommonFotterParts__
#define __NeglecClient__CommonFotterParts__

#include "cocos2d.h"

class CommonFotterParts : public cocos2d::Layer
{
    
public:
    CommonFotterParts();
    virtual ~CommonFotterParts();
    virtual bool init();
    CREATE_FUNC(CommonFotterParts);
    
    void setLockMenu(int menuId);
    
protected:
    
private:
    cocos2d::ui::Widget* _baseLayout;
    
};

#endif /* defined(__NeglecClient__CommonFotterParts__) */
