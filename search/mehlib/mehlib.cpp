// mehlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "mehlib.h"
#include <stdexcept>
/*
extern "C" int __declspec(dllexport)  addasm(int a, int b);

extern "C" {int __declspec(dllexport)  add(int a, int b){
	return addasm(a,b);
}}
*/

extern "C" __declspec(dllexport) void adjustASM(unsigned char* norm, unsigned char * ori, short bar, INT32 size);

extern "C"{
	__declspec(dllexport) void adjustASMadap(unsigned char* _norm, unsigned char * _ori, short _bar, INT32 _size)
	{
		adjustASM(_norm, _ori, _bar, _size);
	}
}
