//
//  MasterData.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/15.
//
//

#ifndef NeglecClient_MasterData_h
#define NeglecClient_MasterData_h

#include <vector>
#include "json11.hpp"

namespace MasterData {

    struct MItem {
        int itemID;
        int itemType;
        int param;
        std::string imageID;
        std::string name;
        std::string detail;
    };

    struct MQuest {
        int questID;
        int floorCount;
        std::string questName;
        std::string questDetail;
    };

    struct MasterData {
        std::vector<MItem> mItem;
        std::vector<MQuest> mQuest;
    };

    template <typename T>
    static T create(json11::Json item) {
        assert(false);
    }

    template <typename T>
    static std::vector<T> createList(json11::Json items) {
        std::vector<T> dataList;
        
        for (auto item : items.array_items()) {
            dataList.push_back(create<T>(item));
        }
        return dataList;
    }
    
    template<>
    MItem create(json11::Json item) {
        MItem data;
        
        data.itemID     = item["ItemID"].int_value();
        data.itemType   = item["Type"].int_value();
        data.param      = item["Param"].int_value();
        data.imageID    = item["ImageID"].string_value();
        data.name       = item["Name"].string_value();
        data.imageID    = item["Detail"].string_value();
        return data;
    }
    
    template<>
    MQuest create(json11::Json item) {
        MQuest data;
        
        data.questID     = item["QuestID"].int_value();
        data.floorCount  = item["FloorCount"].int_value();
        data.questName   = item["QuestName"].string_value();
        data.questDetail = item["QuestDetail"].string_value();
        return data;
    }
}

#endif
