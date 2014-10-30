//
//  DialogShowListViewLayer.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/31.
//
//

#ifndef __NeglecClient__DialogShowListViewLayer__
#define __NeglecClient__DialogShowListViewLayer__

#include "cocos2d.h"

class DialogShowListViewLayer : public cocos2d::Layer
{
    
public:
    DialogShowListViewLayer();
    virtual ~DialogShowListViewLayer();
    virtual bool init();
    CREATE_FUNC(DialogShowListViewLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
public:
    void setTitleText(const std::string& titleName);
    
protected:
    
private:
    cocos2d::Node* _baseLayout;
    
};

#endif /* defined(__NeglecClient__DialogShowListViewLayer__) */
