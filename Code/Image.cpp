/*
 *  Image.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/01/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Image.h"
#include "Stringer.h"

Image::Image(std::string filename)
{
	GLTextureId = 0;
	try
	{
		SDL_ClearError();
		SDL_Surface* surface = IMG_Load(filename.c_str());

		std::string error = std::string("SDL Error: ") + std::string(SDL_GetError());

		glPixelStorei(GL_UNPACK_ALIGNMENT,4);
		glGenTextures(1, &GLTextureId);
		glBindTexture(GL_TEXTURE_2D, GLTextureId);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
		
		

		SDL_PixelFormat *format = surface->format;
		if (format->Amask)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
				surface->w, surface->h, GL_RGBA,GL_UNSIGNED_BYTE, surface->pixels);
		}
		else
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
				surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		}
		Width = surface->w;
		Height = surface->h;
		SDL_FreeSurface(surface);
	}
	catch (...)
	{
		printf("Failed to load texture: %s",filename.c_str());
	}
}

//Image::~Image()
//{
//
//}
