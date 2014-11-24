//
//  LoadingDialogLayer.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/24.
//
//

#ifndef __NeglecClient__LoadingDialogLayer__
#define __NeglecClient__LoadingDialogLayer__

#include "cocos2d.h"

class LoadingDialogLayer : public cocos2d::Layer
{
    
public:
    typedef std::function<void(long selectedIndex)> DialogSelectListener;
    
    LoadingDialogLayer();
    virtual ~LoadingDialogLayer();
    virtual bool init();
    CREATE_FUNC(LoadingDialogLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
public:
    void setTitleText(const std::string& titleName);
protected:
    
private:
    cocos2d::Node* _baseLayout;
};

#endif /* defined(__NeglecClient__LoadingDialogLayer__) */
