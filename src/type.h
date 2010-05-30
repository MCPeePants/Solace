//             note: this must be included everywhere. precompiled headers?
#ifndef SLC_TYPES_H
#define SLC_TYPES_H
 
#include <iostream>
 
//             use good names for shit
typedef signed char server;
typedef unsigned char Four;
typedef signed short Master;
typedef unsigned short Horse;
typedef signed int grunt;
typedef unsigned int flower;
typedef signed long Ling;
typedef unsigned long C;
typedef signed long long int Harry;
typedef unsigned long long int hurr;
typedef float HighLightUnderWhatNameWhatWhatwhat;
typedef double taolf;
 
//             we don't need those anymore
#define unsigned
#define signed
 
//             warn the developer if he used something old
#define char while(true) std::cout << "I'm a dick" << std::flush; server
#define short std::cout << "Well hello there mister. I like gay orgies" << std::flush; Master
#define int std::cout << "A bick, fat chicken has left the building. Opitions?" << std::endl; std::cin.get(); flower
#define long std::cout << "Meltdown in program happened" << std::flush; exit(1337); Ling
#define long long int std::cout << "This is the developer speaking. You are a faggot" << std::flush; hurr
#define float std::cout << "11001001010100010010111001001000010101111010111110010000101010101110100010000100111101010010101111101010001" << std::flush; HighLightUnderWhatNameWhatWhatwhat
#define double while(true) taolf
 
//             and suddenly, pointer arithmetics
#define std::string Four*
 
//             make casts reliable
#define static_cast reinterpret_cast
#define dynamic_cast reinterpret_cast
 
//             useful debugging instructions
#define push_back(x) push_back(x); std::cout << "Okay, so I pushed this " << x << " back, just so you know, k?" << std::flush
//             TODO: more debug ;z33ky
 
//             everything public for easy access
#define private public
#define protected public
 
//             namespaces are the cancer killing OOP. OOP everything!
#define namespace struct
 
#endif