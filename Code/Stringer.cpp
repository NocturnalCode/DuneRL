//
//  Stringer.cpp
//  Roguelike
//
//  Created by Daniel Brooker on 10/03/12.
//  Copyright (c) 2012 Nocturnal Code Limited. All rights reserved.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef __APPLE__
    #include "CoreFoundation/CFBundle.h"
#else
	#include <Windows.h>
	#include <stdio.h>
	#include <stdarg.h>
#endif
//#elif defined __linux__
//    #warning "Untested on Linux"
//#elif defined _WIN32 || defined _WIN64
//    #warning "Untested on Linux"
//#else
//    #error "Unknown platform"
//#endif

void DoFormatting(std::string& sF, std::string sf, va_list marker)
{
    char *s, ch=0;
    int n, i=0, m;
    long l;
    double d;
//     = sformat;
    std::stringstream ss;

    m = sf.length();
    while (i<m)
    {
        ch = sf.at(i);
        if (ch == '%')
        {
            i++;
            if (i<m)
            {
                ch = sf.at(i);
                switch(ch)
                {
                    case 's': { s = va_arg(marker, char*);  ss << s;         } break;
                    case 'c': { n = va_arg(marker, int);    ss << (char)n;   } break;
                    case 'd': { n = va_arg(marker, int);    ss << (int)n;    } break;
                    case 'l': { l = va_arg(marker, long);   ss << (long)l;   } break;
                    case 'f': { d = va_arg(marker, double); ss << (float)d;  } break;
                    case 'e': { d = va_arg(marker, double); ss << (double)d; } break;
                    case 'X':
                    case 'x':
                        {
                            if (++i<m)
                            {
                                ss << std::hex << std::setiosflags (std::ios_base::showbase);
                                if (ch == 'X') ss << std::setiosflags (std::ios_base::uppercase);
                                char ch2 = sf.at(i);
                                if (ch2 == 'c') { n = va_arg(marker, int);  ss << std::hex << (char)n; }
                                else if (ch2 == 'd') { n = va_arg(marker, int); ss << std::hex << (int)n; }
                                else if (ch2 == 'l') { l = va_arg(marker, long);    ss << std::hex << (long)l; }
                                else ss << '%' << ch << ch2;
                                ss << std::resetiosflags (std::ios_base::showbase | std::ios_base::uppercase) << std::dec;
                            }
                        } break;
                    case '%': { ss << '%'; } break;
                    default:
                    {
                        ss << "%" << ch;
                        //i = m; //get out of loop
                    }
                }
            }
        }
        else ss << ch;
        i++;
    }
    va_end(marker);
    sF = ss.str();
}

std::string stringFormat(std::string format, ...)
{
#ifdef _WIN32
	//va_list args;
	//int len = f.size() + 100;
	//char *buffer;
	//char *format = (char*)malloc(f.size()+1 * sizeof(char) );
	//strcpy(format,f.c_str());
	//va_start(args,format);
	//len = _vscprintf(format,args) + 1;
	//buffer = (char*)malloc(len * sizeof(char) );
	//vsprintf(buffer,format,args);
	va_list args;
    va_start(args, format);
	std::string buffer;
    DoFormatting(buffer, format, args);
#else
    char *buffer;
    va_list args;
    va_start(args, format);
    vasprintf(&buffer,format.c_str(), args);
    va_end(args);
#endif
	return std::string(buffer);
}


std::string filenameWithFormat(std::string format, ...)
{
#ifdef _WIN32
	//va_list args;
	//int len = 0;
	//char *buffer;
	//char *format = (char*)malloc(f.size()+1 * sizeof(char) );
	//strcpy(format,f.c_str());
	//va_start(args,format);
	//len = _vscprintf(format,args) + 1;
	//buffer = (char*)malloc(len * sizeof(char) );
	//vsprintf(buffer,format,args);

	va_list args;
    va_start(args, format);
	std::string buffer;
    DoFormatting(buffer, format, args);

	std::string path = stringFormat("%s",buffer);
#else
    char *buffer;
    va_list args;
    va_start(args, format);
    vasprintf(&buffer,format.c_str(), args);
    va_end(args);
//    
    char *name = getenv("EXECUTABLE_NAME"); // this is a bad way to do this, it's OSX specific atm
//    
//    CFBundleRef bundle = CFBundleGetMainBundle();
//    CFURLRef fileURL = CFBundleCopyResourceURL( bundle,
//                                         CFSTR(buffer),
//                                         CFSTR(""),
//                                         NULL );

    std::string path = stringFormat("%s.app/Contents/Resources/%s",name,buffer);
#endif
    return path;
}

#if 0

A very late answer, but for those who, like me, do like the 'sprintf'-way: I've written and are using the following functions. If you like it, you can expand the %-options to more closely fit the sprintf ones; the ones in there currently are sufficient for my needs. You use stringf() and stringfappend() same as you would sprintf. Just remember that the parameters for ... must be POD types.

//=============================================================================


//=============================================================================
void stringf(string& stgt,const char *sformat, ... )
{
    va_list marker;
    va_start(marker, sformat);
    DoFormatting(stgt, sformat, marker);
}

//=============================================================================
void stringfappend(string& stgt,const char *sformat, ... )
{
    string sF = "";
    va_list marker;
    va_start(marker, sformat);
    DoFormatting(sF, sformat, marker);
    stgt += sF;
}

#endif