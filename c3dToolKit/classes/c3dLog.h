//
//  c3dLog.h
//  HelloCpp
//
//  Created by yang chao (wantnon) on 14-1-1.
//
//

#ifndef __HelloCpp__c3dLog__
#define __HelloCpp__c3dLog__

#include <iostream>
#include <stdarg.h>
//ref to CCCommon.h
static const int maxC3dLogLen = 16*1024;// The max length of c3dLog message.
void c3dLog(const char * pszFormat, ...);
//ref to CCPlatformMacros.h
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
#define C3DLOG(format, ...)      c3dLog(format, ##__VA_ARGS__)
#else
#define C3DLOG(format, ...)  void(0)
#endif
#endif /* defined(__HelloCpp__c3dLog__) */
