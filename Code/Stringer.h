//
//  Stringer.h
//  Roguelike
//
//  Created by Daniel Brooker on 23/07/11.
//  Copyright 2011 Nocturnal Code Limited. All rights reserved.
//

#ifndef STRINGER_H_INC
#define STRINGER_H_INC

#include <string>
#ifdef _WIN32
	#include <Windows.h>
#endif

std::string stringFormat(std::string format, ...);
std::string filenameWithFormat(std::string format, ...);
void DoFormatting(std::string& sF, std::string sf, va_list marker);

#endif /* STRINGER_H_INC */