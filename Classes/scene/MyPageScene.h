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
    cocos2d::Node *_baseLayout;
};

#endif /* defined(__NeglecClient__MyPageScene__) */
