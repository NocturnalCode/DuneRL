/*
 *  Window.cpp
 *  Roguelike
 *
 *  Created by Daniel on 30/03/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#include "Window.h"
#include "Ascii.h"
#include "math.h"
#include "Point.h"
#include "Rect.h"

Window::Window(Rect rect)
{
	this->rect = rect;
	borderColour = Colour::white();
	borderStyle = Border_Single;
    background = true;
	this->delegate = NULL;
	this->texture = NULL;
	this->setup();
}

Window::~Window()
{
	this->delegate = NULL;
	this->texture = NULL;
	if(vertexCoordinates!=NULL)
		free(vertexCoordinates);
	if(texCoordinates!=NULL)
		free(texCoordinates);
	if(colCoordinates!=NULL)
		free(colCoordinates);
	if(bgColCoordinates!=NULL)
		free(bgColCoordinates);
}

Label* Window::getCentreLabel()
{
	return &centreLabel;
}

Label* Window::getLeftLabel()
{
	return &leftLabel;
}

Label* Window::getRightLabel()
{
	return &rightLabel;
}

Rect Window::getFrame()
{
	return rect;
}

void Window::add(Display *displayable)
{
	displayable->setParent(this);
	displays.push_back(displayable);
}

void Window::add(Window *window)
{
	window->setParent(this);
	if(window->wantsEvents())
		eventDelegate = window;
	windows.push_back(window);
}

void Window::remove(Display *displayable)
{
	displayable->setParent(NULL);
	displays.remove(displayable);
}

void Window::remove(Window *window)
{
	window->setParent(NULL);
	if(eventDelegate == window)
		eventDelegate = delegate;
	windows.remove(window);
}

void Window::setup()
{
	vertexCoordinates = NULL;
	texCoordinates = NULL;
	colCoordinates = NULL;
	bgColCoordinates = NULL;
	scale = 2;
	setupVertexCoordinates();
}

void Window::reset()
{
    unsigned tileW = (4*scale);
	unsigned tileH = (6*scale);
    //	printf("Scale %d\n",scale);
	unsigned width = rect.Width, height = rect.Height;
	unsigned nWide = width/tileW;
	unsigned nHigh = height/tileH;
    
    for(int j=0; j < nHigh; j++)
	{
		for(int i=0; i < nWide; i++)
		{
			// verts
			int k =  ARRAY2D(i,j,nWide)*12;
			vertexCoordinates[k+0] = i*tileW;			vertexCoordinates[k+1] = j*tileH;			vertexCoordinates[k+2] = 0;
			vertexCoordinates[k+3] = tileW+(i*tileW);	vertexCoordinates[k+4] = j*tileH;			vertexCoordinates[k+5] = 0;
			vertexCoordinates[k+6] = tileW+(i*tileW);	vertexCoordinates[k+7] = tileH+(j*tileH);	vertexCoordinates[k+8] = 0;
			vertexCoordinates[k+9] = i*tileW;			vertexCoordinates[k+10]= tileH+(j*tileH);	vertexCoordinates[k+11] = 0;
			
			// texture
			int l = ARRAY2D(i,j,nWide)*8;
            
            int row = 0;//(BLOCK+16) / 16;
            int column = 0;//(BLOCK+16) % 16;
            float ratio = 0.0625f;
            
            float alpha = background ? 1.0f : 0.0f;
            
            texCoordinates[l+0] = ratio*			column;		texCoordinates[l+1] = ratio*		row;	
            texCoordinates[l+2] = ratio+ratio*		column;		texCoordinates[l+3] = ratio*		row;
            texCoordinates[l+4] = ratio+ratio*		column;		texCoordinates[l+5] = ratio+ratio*	row;
            texCoordinates[l+6] = ratio*			column;		texCoordinates[l+7] = ratio+ratio*	row;
            
            // colour
            int m = ARRAY2D(i,j,nWide)*16;
            colCoordinates[m+0] = 0.0f;	colCoordinates[m+1] = 0.0f; colCoordinates[m+2] = 0.0f;  colCoordinates[m+3] = alpha;
            colCoordinates[m+4] = 0.0f;	colCoordinates[m+5] = 0.0f; colCoordinates[m+6] = 0.0f;  colCoordinates[m+7] = alpha;
            colCoordinates[m+8] = 0.0f;	colCoordinates[m+9] = 0.0f; colCoordinates[m+10]= 0.0f;  colCoordinates[m+11] = alpha;
            colCoordinates[m+12] =0.0f;	colCoordinates[m+13] =0.0f; colCoordinates[m+14]= 0.0f;  colCoordinates[m+15] = alpha;
            
            bgColCoordinates[m+0] = 0.0f;	bgColCoordinates[m+1] = 0.0f; bgColCoordinates[m+2] = 0.0f;  bgColCoordinates[m+3] = alpha;
            bgColCoordinates[m+4] = 0.0f;	bgColCoordinates[m+5] = 0.0f; bgColCoordinates[m+6] = 0.0f;  bgColCoordinates[m+7] = alpha;
            bgColCoordinates[m+8] = 0.0f;	bgColCoordinates[m+9] = 0.0f; bgColCoordinates[m+10]= 0.0f;  bgColCoordinates[m+11] = alpha;
            bgColCoordinates[m+12] =0.0f;	bgColCoordinates[m+13] =0.0f; bgColCoordinates[m+14]= 0.0f;  bgColCoordinates[m+15] = alpha;
 
		}
	}
}

void Window::setupVertexCoordinates()
{
	unsigned tileW = (4*scale);
	unsigned tileH = (6*scale);
//	printf("Scale %d\n",scale);
	unsigned width = rect.Width, height = rect.Height;
	unsigned nWide = width/tileW;
	unsigned nHigh = height/tileH;
//	unsigned xOff = rect.X/tileW;
//	unsigned yOff = rect.Y/tileH;
	
	vertices = nWide * nHigh * 4;
	if(vertexCoordinates!=NULL)
		free(vertexCoordinates);
	vertexCoordinates = (float*)malloc(sizeof(float) * nWide * nHigh * 12);
	if(texCoordinates!=NULL)
		free(texCoordinates);
	texCoordinates =(float*)malloc(sizeof(float) * nWide * nHigh * 8); 
	if(colCoordinates!=NULL)
		free(colCoordinates);
	colCoordinates =(float*)malloc(sizeof(float) * nWide * nHigh * 16);
	if(bgColCoordinates!=NULL)
		free(bgColCoordinates);
	bgColCoordinates =(float*)malloc(sizeof(float) * nWide * nHigh * 16);
	
	reset();
}

void Window::display()
{
    reset();
	// aquire texture and colour arrays
	if(texture)
		texture->bind();
	if(delegate)
		delegate->display(texCoordinates,colCoordinates,bgColCoordinates);

	// add window border
	border(texCoordinates,colCoordinates,bgColCoordinates);
	
	for(Displays::iterator d = displays.begin(); d != displays.end(); d++)
		(*d)->display(texCoordinates, colCoordinates, bgColCoordinates);
	
	glPushMatrix();
	// translate window to correct position
	glTranslatef(rect.X, rect.Y, 0);

	// setup texture pointers and colour pointers
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

    if(!background)
    {
        glAlphaFunc(GL_GREATER, 0.5);
        glEnable(GL_ALPHA_TEST);
    }
    
	// background
    glColorPointer(4, GL_FLOAT, 0, bgColCoordinates);
    glVertexPointer(3, GL_FLOAT, 0, vertexCoordinates);
    glDrawArrays(GL_QUADS, 0, vertices);
	
	// foreground
	glEnable(GL_TEXTURE_2D);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordinates);
	glColorPointer(4, GL_FLOAT, 0, colCoordinates);
	glVertexPointer(3, GL_FLOAT, 0, vertexCoordinates);
	glDrawArrays(GL_QUADS, 0, vertices);
	
	// disable
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	
	for(Windows::iterator d = windows.begin(); d != windows.end(); d++)
		(*d)->display();
		
	glPopMatrix();
}

void Window::border(float *tex, float *col, float *bgCol)
{
	unsigned tileW = (4*scale);
	unsigned tileH = (6*scale);
	unsigned width = rect.Width, height = rect.Height;
	unsigned nWide = width/tileW;
	unsigned nHigh = height/tileH;
	int tl,tr,br,bl,h,v,jl,jr;
	
	switch(borderStyle)
	{
		case Border_Single:
			tl=CORNER_TOP_LEFT_SINGLE,tr=CORNER_TOP_RIGHT_SINGLE;
			br=CORNER_BOTTOM_RIGHT_SINGLE,bl=CORNER_BOTTOM_LEFT_SINGLE;
			h=LINE_HORIZONTAL_SINGLE,v=LINE_VERTICAL_SINGLE;
			jl=JOINT_SINGLE_LEFT_SINGLE ,jr=JOINT_SINGLE_RIGHT_SINGLE;
			break;
		case Border_Double:
			tl=CORNER_TOP_LEFT_DOUBLE,tr=CORNER_TOP_RIGHT_DOUBLE;
			br=CORNER_BOTTOM_RIGHT_DOUBLE,bl=CORNER_BOTTOM_LEFT_DOUBLE;
			h=LINE_HORIZONTAL_DOUBLE,v=LINE_VERTICAL_DOUBLE;
			jl=JOINT_DOUBLE_LEFT_SINGLE ,jr= JOINT_DOUBLE_RIGHT_SINGLE;	
			break;
		case Border_Block:
			tl=BLOCK,tr=BLOCK,br=BLOCK,bl=BLOCK,h=BLOCK,v=BLOCK;
			jl=BLOCK,jr=BLOCK;
			break;
		default:
			return;
			break;
	}
	// top left
	{
	Ascii a(tl+16,borderColour,Colour(0,0,0));
	int texI = ARRAY2D(0,0,nWide)*8;
	int colI = ARRAY2D(0,0,nWide)*16;
	displayTile(&tex[texI],&col[colI],&bgCol[colI],a);
	}

	// top right
	{
	Ascii a(tr+16,borderColour,Colour(0,0,0));
	int texI = ARRAY2D((nWide-1),0,nWide)*8;
	int colI = ARRAY2D((nWide-1),0,nWide)*16;
	displayTile(&tex[texI],&col[colI],&bgCol[colI],a);
	}
		
	// bottom left
	{
	Ascii a(bl+16,borderColour,Colour(0,0,0));
	int texI = ARRAY2D(0,(nHigh-1),nWide)*8;
	int colI = ARRAY2D(0,(nHigh-1),nWide)*16;
	displayTile(&tex[texI],&col[colI],&bgCol[colI],a);
	}
	
	// bottom right
	{
	Ascii a(br+16,borderColour,Colour(0,0,0));
	int texI = ARRAY2D((nWide-1),(nHigh-1),nWide)*8;
	int colI = ARRAY2D((nWide-1),(nHigh-1),nWide)*16;
	displayTile(&tex[texI],&col[colI],&bgCol[colI],a);
	}
	
	// vertical
	for(int j=1;j<nHigh-1;j++)
	{
		Ascii b(v+16,borderColour,Colour(0,0,0));
		int texI = ARRAY2D(0,j,nWide)*8;
		int colI = ARRAY2D(0,j,nWide)*16;
		displayTile(&tex[texI],&col[colI],&bgCol[colI],b);
		texI = ARRAY2D((nWide-1),j,nWide)*8;
		colI = ARRAY2D((nWide-1),j,nWide)*16;
		displayTile(&tex[texI],&col[colI],&bgCol[colI],b);
	}
	
	// horizontal
	int centre = round(nWide/2.0)-round(centreLabel.getString().size()/2.0)-1;
	int left = 1;
	int right = nWide-rightLabel.getString().size()-3;
	for(int i=1;i<nWide-1;i++)
	{
		Ascii b, c = Ascii(h+16,borderColour,Colour(0,0,0));
		
		if(centreLabel.getString().size() != 0 && i >= centre-1 && i-centre <= centreLabel.getString().size()+1)
		{ // centre
//			printf("Centre label: %s\n",centreLabel.getString().c_str());
			if(i == centre)
				b = Ascii(jr+16,borderColour,Colour(0,0,0)); 
			else if(i-centre == centreLabel.getString().size()+1)
				b = Ascii(jl+16,borderColour,Colour(0,0,0)); 
			else
				b = Ascii(CHAR_TO_ASCII(centreLabel.getString()[i-centre-1])+16,centreLabel.getColour(),Colour(0,0,0)); 
		}
		else if(leftLabel.getString().size() != 0 && i >= 1 && i-left <= leftLabel.getString().size()+1)
		{ // left
			if(i == left)
				b = Ascii(jr+16,borderColour,Colour(0,0,0)); 
			else if(i-left == leftLabel.getString().size()+1)
				b = Ascii(jl+16,borderColour,Colour(0,0,0)); 
			else
				b = Ascii(CHAR_TO_ASCII(leftLabel.getString()[i-left-1])+16,leftLabel.getColour(),Colour(0,0,0)); 
		}
		else if(rightLabel.getString().size() != 0 && i >= right-1 && i-right <= rightLabel.getString().size()+1)
		{ // right
			if(i == right)
				b = Ascii(jr+16,borderColour,Colour(0,0,0)); 
			else if(i-right == rightLabel.getString().size()+1)
				b = Ascii(jl+16,borderColour,Colour(0,0,0)); 
			else
				b = Ascii(CHAR_TO_ASCII(rightLabel.getString()[i-right-1])+16,rightLabel.getColour(),Colour(0,0,0)); 
		}
		else
			b = c;
		int texI = ARRAY2D(i,0,nWide)*8;
		int colI = ARRAY2D(i,0,nWide)*16;
		displayTile(&tex[texI],&col[colI],&bgCol[colI],b);
		texI = ARRAY2D(i,(nHigh-1),nWide)*8;
		colI = ARRAY2D(i,(nHigh-1),nWide)*16;
		displayTile(&tex[texI],&col[colI],&bgCol[colI],c);
	}

}

void Window::setParent(Display* parent)
{
	this->parent = parent;
}

Display* Window::getParent()
{
	return parent;
}

void Window::display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates)
{
	
}