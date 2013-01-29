//
//  OpenGLTextureLoader.h
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#ifndef OPENGL_TEXTURE_LOADER_H
#define OPENGL_TEXTURE_LOADER_H

#include "OpenGLTexture.h"
#include "../libpng/png.h"


namespace OpenGLTextureLoader
{
  bool loadTextureFromPath(const char* path, OpenGLTextureInfo** textureInfo);
  void setTextureFromData(png_structp png_ptr, png_infop info_ptr, OpenGLTextureInfo** textureInfo);
}

#endif
