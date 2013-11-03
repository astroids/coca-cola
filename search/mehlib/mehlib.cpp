// mehlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "mehlib.h"
#include <stdexcept>
#include <future>


//#define DEFRW
//#define DEFRW_P
//#define DEFR
//#define DEFR_P
#define FADE


#include <iostream>	//kaldir bunu  butun io larla birlikte
#include <vector>
std::vector<unsigned short> pic;
int redFlag = 0;
int whiteFlag = 0;
int paras = 0;
size_t mainL;


/*
extern "C" int __declspec(dllexport)  addasm(int a, int b);

extern "C" {int __declspec(dllexport)  add(int a, int b){
	return addasm(a,b);
}}
*/

extern "C" __declspec(dllexport) void adjustASM(unsigned char* norm, unsigned char * ori, short bar, INT32 size);

extern "C"{
	__declspec(dllexport) void adjustASMadap(unsigned char* _norm, short _bar, INT32 _size, unsigned char * _ori)
	{
		unsigned char * n2 = _norm + (_size / 2);
		unsigned char * o2 = _ori + (_size / 2);

		std::async(std::launch::async, adjustASM,_norm, _ori, _bar, _size/2);
		std::async(std::launch::async, adjustASM, n2, o2, _bar, _size/2);

		//adjustASM(_norm, _ori, _bar, _size);



	}
}


extern "C" {void _declspec(dllexport) adjustb(unsigned char*  norm, short bar, INT32 size, unsigned char * ori){
	for (size_t i = 0; i < size; i++)
	{
		if ((short) ori[i] + bar < 0) {
			norm[i] = 0;
		}
		else if ((short) ori[i] + bar > 255){
			norm[i] = 255;
		}
		else
		{
			norm[i] = ori[i] + bar;
		}

	}
}}

//extern void incPara();
//extern void fadeToBlack();
//extern void RWAnalize();
//extern void incWhite();
//extern void incRed();
//extern bool isItRed();
//extern void resetRWFlags();
//extern bool isItWhite();
//extern void RWAnalize();
//



extern "C" { MEHLIB_API void searchrw(unsigned char*  a, short bar, INT32 size, unsigned char* orig) {

	//RWAnalize();

}
}
