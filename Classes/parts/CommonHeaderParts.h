//
//  CommonHeaderParts.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__CommonHeaderParts__
#define __NeglecClient__CommonHeaderParts__

#include "cocos2d.h"

class CommonHeaderParts : public cocos2d::Layer
{
    
public:
    CommonHeaderParts();
    virtual ~CommonHeaderParts();
    virtual bool init();
    CREATE_FUNC(CommonHeaderParts);
    
    void setTitleText(const std::string& titleName);
    
protected:
    
private:
    cocos2d::ui::Widget* _baseLayout;
    
};

#endif /* defined(__NeglecClient__CommonHeaderParts__) */
