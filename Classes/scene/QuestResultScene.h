//
//  QuestResultScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/12/07.
//
//

#ifndef __NeglecClient__QuestResultScene__
#define __NeglecClient__QuestResultScene__

#include "cocos2d.h"

class QuestResultScene : public cocos2d::Layer
{
public:
    QuestResultScene();
    virtual ~QuestResultScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(QuestResultScene);
    
private:
    void initView();
    void requestResultQuest();
    
    // view
//    void setTextQuestDetail(int floorCount, int hour, int minute);
//    void setTextStatus(int lv, int hp, int maxHp, int mp, int maxMp);
//    void setTextLogMessage(const std::string &message);
private:
    cocos2d::Node *_baseLayout;
};

#endif /* defined(__NeglecClient__QuestResultScene__) */
