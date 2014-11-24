//
//  StartScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/23.
//
//

#ifndef __NeglecClient__StartScene__
#define __NeglecClient__StartScene__

#include "cocos2d.h"

namespace cocos2d {
    namespace ui {
        class Button;
    }
}

class StartScene : public cocos2d::Layer
{
public:
    StartScene();
    virtual ~StartScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
    
private:
    void initView();
    void requestLogin();
private:
    cocos2d::ui::Button *_startButton;
    cocos2d::Node *_baseLayout;
};

#endif /* defined(__NeglecClient__StartScene__) */
