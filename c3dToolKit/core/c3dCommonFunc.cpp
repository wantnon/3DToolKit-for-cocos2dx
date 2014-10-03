//
//  c3dCommonFunc.cpp
//  HelloCpp
//
//  Created by Yang Chao (wantnon) on 14-1-3.
//
//

#include "c3dCommonFunc.h"
string numberToStr(int n){//int to string
    char numbuf[128];
    sprintf(numbuf, "%i", n);//there is no itoa in xcode
    string numStr=numbuf;
    return numStr;
}