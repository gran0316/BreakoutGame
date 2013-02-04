//
//  OpenGLTextureLoader.cpp
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#include "OpenGLTextureLoader.h"
#include <string>
#include <stdlib.h>


namespace OpenGLTextureLoader
{
  bool loadTextureFromPath(const char* aPath, OpenGLTextureInfo** aTextureInfo)
  {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    FILE *file;

    //Open the image file
    if ((file = fopen(aPath, "rb")) == NULL)
    {
      return false;
    }

    //Create and initialize the png_struct with the desired error handler
    //functions.  If you want to use the default stderr and longjump method,
    //you can supply NULL for the last three parameters.  We also supply the
    //the compiler header file version, so that we know if the application
    //was compiled with a compatible version of the library.  REQUIRED
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL)
    {
      fclose(file);
      return false;
    }

    //Allocate/initialize the memory for image information.  REQUIRED.
    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL)
    {
      fclose(file);
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      return false;
    }

    //Set error handling if you are using the setjmp/longjmp method (this is
    //the normal method of doing things with libpng).  REQUIRED unless you
    //set up your own error handlers in the png_create_read_struct() earlier.
    if(setjmp(png_jmpbuf(png_ptr)))
    {
      //Free all of the memory associated with the png_ptr and info_ptr
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(file);

      //If we get here, we had a problem reading the file
      return false;
    }

    //Set up the input control if you are using standard C streams
    png_init_io(png_ptr, file);

    //If we have already read some of the signature
    png_set_sig_bytes(png_ptr, sig_read);

    //If you have enough memory to read in the entire image at once,
    //and you need to specify only transforms that can be controlled
    //with one of the PNG_TRANSFORM_* bits (this presently excludes
    //quantizing, filling, setting background, and doing gamma
    //adjustment), then you can read the entire image (including
    //pixels) into the info structure with this call:
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    //
    OpenGLTextureLoader::setTextureFromData(png_ptr, info_ptr, aTextureInfo);

    //Clean up after the read, and free any memory allocated - REQUIRED
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    //Close the file
    fclose(file);

    //That's it
    return true;
  }

  void setTextureFromData(png_structp png_ptr, png_infop info_ptr, OpenGLTextureInfo** aTextureInfo)
  {
    //Texture info struct
    OpenGLTextureInfo* textureInfo = *aTextureInfo;
      
    //Get the data, width and height of the image.
    png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    unsigned int width = png_get_image_width(png_ptr, info_ptr);
    unsigned int height = png_get_image_height(png_ptr, info_ptr);
    unsigned char colorType = png_get_color_type(png_ptr, info_ptr);
    unsigned char bitDepth = png_get_bit_depth(png_ptr, info_ptr);
    int bitD = bitDepth;
    
    //
    GLint textureFormat = GL_RGBA;
    if(colorType == PNG_COLOR_TYPE_RGB)
    {
      textureFormat = GL_RGB;
    }

    //
    GLubyte* imageData = (unsigned char*) malloc(row_bytes * height);
      
    //
    for (int i = 0; i < height; i++)
    {
      // note that png is ordered top to
      // bottom, but OpenGL expect it bottom to top
      // so the order or swapped
      memcpy(imageData + (row_bytes * (height-1-i)), row_pointers[i], row_bytes);
    }

    //Load the texture data, and get the OpenGL texture id.
    GLuint textureId = textureInfo->textureId;
    if(textureId == 0)
    {
      //Use OpenGL ES to generate a name for the texture.
      glGenTextures(1, &textureId);
      
      //Bind the texture name. 
      glBindTexture(GL_TEXTURE_2D, textureId);
      
      //Does the texture options sepcify if the texture has mipmaps?
      GLint mipmapLevel = 0;

      //Set the texture parameters to use a minifying filter and a linear filer (weighted average)
      if(mipmapLevel > 0)
      {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      }
      else
      {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      }
      
      //Specify a 2D texture image, provideing the a pointer to the image data in memory
      glTexImage2D(GL_TEXTURE_2D, mipmapLevel, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, imageData);			
    }

    //If the texture name isn't zero, set the image info struct.
    if(textureId != 0)
    {
      //Is there only a subsection of the image to use? If not use 0,0 as the image origin.
      GLuint sourceX = textureInfo->sourceX;
      GLuint sourceY = textureInfo->sourceY;
    
      //Is there only a subsection of the image to use? If not use the image's native width.
      GLuint sourceWidth = textureInfo->sourceWidth;
      if(sourceWidth == 0)
      {
        sourceWidth = width;
      }
      
      //Is there only a subsection of the image to use? If not use the image's native height.
      GLuint sourceHeight = textureInfo->sourceHeight;
      if(sourceHeight == 0)
      {
        sourceHeight = height;
      }
    
      //Set the texture info struct data
      textureInfo->textureId = textureId;
      textureInfo->sourceX = sourceX;
      textureInfo->sourceY = sourceY;
      textureInfo->sourceWidth = sourceWidth;
      textureInfo->sourceHeight = sourceHeight;
      textureInfo->textureWidth = width;
      textureInfo->textureHeight = height;
      textureInfo->textureFormat = GL_RGBA;
    }
  }
}

