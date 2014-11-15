//
//  UserData.h
//  NeglecClient
//
//  Created by kyokomi on 2014/11/15.
//
//

#ifndef NeglecClient_UserData_h
#define NeglecClient_UserData_h

#include <vector>

struct UserData {
    struct TUserItem {
        float accountID;
        float itemID;
        float seqNo;
    };
    std::vector<TUserItem> tUserItem;
};

#endif
