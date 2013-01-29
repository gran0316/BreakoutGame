//
//  ResourceUtilsObjC.h
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#ifndef RESOURCE_UTILS_OBJC_H
#define RESOURCE_UTILS_OBJC_H

namespace ResourceUtilsObjC
{
  const char* getPathForResource(const char* fileName, const char* fileType, bool checkForIPadVersion = true);
}

#endif