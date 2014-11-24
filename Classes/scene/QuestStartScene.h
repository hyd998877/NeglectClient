//
//  QuestStartScene.h
//  NeglecClient
//
//  Created by kyokomi on 2014/10/28.
//
//

#ifndef __NeglecClient__QuestStartScene__
#define __NeglecClient__QuestStartScene__

#include "cocos2d.h"

namespace MasterData {
    class MItem;
}

class QuestStartSceneView
{
public:
    typedef std::function<void(cocos2d::Ref *ref)> OnClickCallback;
    typedef std::function<void(cocos2d::Node *itemNode, cocos2d::Ref *ref)> ItemButtonOnClickCallback;
    typedef std::function<void(MasterData::MItem mItem)> ItemSelectListener;
    
    QuestStartSceneView(cocos2d::Node *sceneNode)
    : _scene(sceneNode)
    , _baseLayout(nullptr)
    , _equipLayer(nullptr)
    {
        
    }
    
    virtual ~QuestStartSceneView()
    {
        
    }
    
    void init(const std::string &sceneFileName);
    void setHeaderTitle(const std::string &titleText);
    
    void setupEquipItem(const std::vector<MasterData::MItem> equipItemArray);
    void setupItem(const std::vector<MasterData::MItem> itemArray);
    void setOnClickStartButtonListener(const OnClickCallback &callback);
private:
    
    void setOnClickItemButtonListener(int index, const ItemButtonOnClickCallback &callback);
    void setOnClickEquipButtonListener(int index, const ItemButtonOnClickCallback &callback);
    
    static cocos2d::Layer* createItemListDialog(const std::vector<MasterData::MItem> equipItemArray, const ItemSelectListener &listener);
    
    void addChild(cocos2d::Node *node);
private:
    cocos2d::Node *_scene;
    cocos2d::Node *_baseLayout;
    
    cocos2d::Node *_equipLayer;
};

class QuestStartScene : public cocos2d::Layer
{
public:
    QuestStartScene();
    virtual ~QuestStartScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    
    // implement the "static create()" method manually
    CREATE_FUNC(QuestStartScene);
    
    struct Param {
        int questID;
    };
    
    void setup(Param param);
    
private:
    void requestStartQuest(int questID);
    void requestDataMasterLoad();
private:
    Param _param;
    QuestStartSceneView _view;
};

#endif /* defined(__NeglecClient__QuestStartScene__) */
