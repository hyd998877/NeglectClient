//
//  DialogSelectListViewLayer.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/31.
//
//

#ifndef __NeglecClient__DialogSelectListViewLayer__
#define __NeglecClient__DialogSelectListViewLayer__

#include "cocos2d.h"

class DialogSelectListViewLayer : public cocos2d::Layer
{
    
public:
    DialogSelectListViewLayer();
    virtual ~DialogSelectListViewLayer();
    virtual bool init();
    CREATE_FUNC(DialogSelectListViewLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

public:
    void setTitleText(const std::string& titleName);
    
protected:
    
private:
    cocos2d::Node* _baseLayout;
    
};

#endif /* defined(__NeglecClient__DialogSelectListViewLayer__) */
