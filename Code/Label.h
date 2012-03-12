/*
 *  Label.h
 *  Roguelike
 *
 *  Created by Daniel on 2/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef LABEL_H_INC
#define LABEL_H_INC 

#include "Types.h"
#include "Display.h"
#include <string>

#include "Colour.h"
#include "Rect.h"

typedef enum {
    LabelAlignTop,
    LabelAlignBottom
} LabelAlign;

/**
 Wrap debug text in <> brackets
 */
class Label : public Display
{
	private:
		std::string text;
		Colour colour,bgColour;
		Rect frame;
		Display *parent;
		bool selected;
        LabelAlign alignment;
        bool button;
	public:
		Label();
		Label(std::string text);
		
		void setString(std::string text);
		std::string getString();
		
		void setColour(Colour colour);
		Colour getColour();
		
		void setBackgroundColour(Colour colour);
		Colour getBackgroundColour();
		
		void setFrame(Rect frame);
		Rect getFrame();
		
		void setParent(Display *parent);
		Display* getParent();
		
		void setSelected(bool selected);
		bool getSelected();
    
        void setMultiline(bool enable,int left, int right);
        void setAlignment(LabelAlign align);
		
		virtual void display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates);
//		void displayTile(float *texture, float *colour, float *background ,Ascii ascii);
		
		virtual std::string prefix() { return ""; };
		virtual std::string suffix() { return ""; };
};

#endif /* LABEL_H_INC */