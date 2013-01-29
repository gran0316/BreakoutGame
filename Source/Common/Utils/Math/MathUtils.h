//
//  MathUtils.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-01-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

class MathUtils
{
public:
  //
  static unsigned int nextPowerOf2(unsigned int value);
  
  //
  static float radiansToDegrees(float radians);
  static float degressToRadians(float degrees);
    
  //
  static int randomRange(int min, int max);
  
  //
  static bool withinRange(float valueA, float valueB, float range);
};

#endif
