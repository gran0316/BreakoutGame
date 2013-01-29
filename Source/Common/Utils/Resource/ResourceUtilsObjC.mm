//
//  ResourceUtilsObjC.m
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#import "ResourceUtilsObjC.h"


namespace ResourceUtilsObjC 
{
  const char* getPathForResource(const char* aFileName, const char* aFileType, bool aCheckForIPadVersion)
  {
    //Convert the c strings into NSStrings
    NSString *fileName = [[NSString alloc] initWithCString:aFileName encoding:NSUTF8StringEncoding];
    NSString *fileType = [[NSString alloc] initWithCString:aFileType encoding:NSUTF8StringEncoding];

    //Get the resource path from the NSBundle
    NSString *path = path = [[NSBundle mainBundle] pathForResource:fileName ofType:fileType];
    
    //Release the NSString objects
    [fileName release];
    [fileType release];
    
    //Return the path
    return [path UTF8String];
  }
}

