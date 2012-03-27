/*
 *  LabelValue.h
 *  Roguelike
 *
 *  Created by Daniel on 29/04/10.
 *  Copyright 2010 quantoaduro.com. All rights reserved.
 *
 */

#ifndef LABELVALUE_H_INC
#define LABELVALUE_H_INC 

#include "Label.h"
#include <iostream>

#ifdef _WIN32
#define snprintf _snprintf
#endif

template < class T, class S >
class LabelValue : public Label
{
	protected:
		T *value;
        CallBack<S, T> *getter;
        
    
	public:
		LabelValue() {};
        LabelValue(std::string text,T *value) : Label(text) { this->value=value; this->getter = NULL; }
        LabelValue(std::string text,CallBack<S, T> *getCallback) : Label(text) { this->getter = getCallback; }
		
		T getValue() 
        {
            if(getter != NULL)
                return (T)getter->execute();
            return value; 
        }
		
		virtual void display(float *texCoordinates, float *colCoordinates, float *bgColCoordinates);
		std::string description();
		void up() {};
		void down() {};
};

template < class S >
class LabelValue<bool,S> : public Label {
	protected:
		bool *value;
        CallBack<S, bool> *getter;
    
	public:
		LabelValue(std::string text,bool *value) : Label(text) { this->value=value; this->getter = NULL; }
        bool* getValue() 
        {
            if(getter != NULL)
                return (bool *)getter->execute();
            return value; 
        }	
        std::string suffix() { char str[10]; snprintf(str,10," %s",(*getValue())?"[YES]":"[NO ]"); return str; }
		void up() { (*value) = true; }
		void down() { (*value) = false; }
};

template <class S>
class LabelValue<int,S> : public Label {
	protected:
		int *value;
        CallBack<S, int> *getter;
    
	public:
		LabelValue(std::string text,int *value) : Label(text) { this->value=value; this->getter = NULL; }
        int* getValue() 
        {
            if(getter != NULL)
                return (int *)getter->execute();
            return value; 
        }
		std::string suffix() { char str[100]; snprintf(str,100," [%d]",(*getValue())); return str; }
		void up() { (*value)++; }
		void down() { (*value)--; }
};

template <class S>
class LabelValue<std::string,S> : public Label {
    protected:
        std::string *value;
        CallBack<S, std::string> *getter;
    
    public:
        LabelValue(std::string text,std::string *value) : Label(text) { this->value=value; }
        LabelValue(std::string text,CallBack<S, std::string> *getCallback) : Label(text) { this->getter = getCallback; }
    
        std::string getValue() 
        {
            if(getter != NULL)
                return getter->execute();
            return *value; 
        }
        std::string suffix() { char str[100]; snprintf(str,100,"%s",getValue().c_str()); return str; }
};

#endif /* LABELVALUE_H_INC */