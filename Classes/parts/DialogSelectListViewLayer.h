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
    typedef std::function<void(void)> DialogSelectListener;
    
    DialogSelectListViewLayer();
    virtual ~DialogSelectListViewLayer();
    virtual bool init();
    CREATE_FUNC(DialogSelectListViewLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
public:
    void setOkListener(const DialogSelectListener &listener) { _okListener = listener; }
    void setCloseListener(const DialogSelectListener &listener) { _closeListener = listener; }
    
    void setTitleText(const std::string& titleName);
    void pushListItem(cocos2d::ui::Widget *listItem);
protected:
    
private:
    cocos2d::Node* _baseLayout;
    
    DialogSelectListener _okListener;
    DialogSelectListener _closeListener;
};

#endif /* defined(__NeglecClient__DialogSelectListViewLayer__) */
