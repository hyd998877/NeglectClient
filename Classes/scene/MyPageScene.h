//
//  MyPageScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/27.
//
//

#ifndef __NeglecClient__MyPageScene__
#define __NeglecClient__MyPageScene__

#include "cocos2d.h"

namespace cocos2d {
    namespace ui {
        class Text;
        class Button;
    }
}

class MyPageScene : public cocos2d::Layer
{
public:
    MyPageScene();
    virtual ~MyPageScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MyPageScene);
    
private:
    void initView();
    void requestMyPage();
private:
    cocos2d::ui::Text* _userNameLabel;
    cocos2d::ui::Text* _detailLabel;
    cocos2d::ui::Button* _playingButton;
    
    cocos2d::Node *_baseLayout;
};

#endif /* defined(__NeglecClient__MyPageScene__) */
