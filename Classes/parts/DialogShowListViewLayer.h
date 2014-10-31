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
    typedef std::function<void(void)> DialogShowListener;
    
    DialogShowListViewLayer();
    virtual ~DialogShowListViewLayer();
    virtual bool init();
    CREATE_FUNC(DialogShowListViewLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
public:
    void setCloseListener(const DialogShowListener &listener) { _closeListener = listener; }
    
    void setTitleText(const std::string& titleName);
    void pushListItem(cocos2d::ui::Widget *listItem);
protected:
    
private:
    cocos2d::Node* _baseLayout;
    
    DialogShowListener _closeListener;
};

#endif /* defined(__NeglecClient__DialogShowListViewLayer__) */
