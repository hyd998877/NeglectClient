//
//  NeglectHttpResponse.h
//  NeglecClient
//
//  Created by kyokomi on 2014/12/07.
//
//

#ifndef __NeglecClient__NeglectHttpResponse__
#define __NeglecClient__NeglectHttpResponse__

#include <stdio.h>

class NeglectHttpResponse
{
public:
    enum class PlayStatusType {
        PLAYING = 0,
        ENGIND,
        NOT_PLAY,
    };
};

#endif /* defined(__NeglecClient__NeglectHttpResponse__) */
