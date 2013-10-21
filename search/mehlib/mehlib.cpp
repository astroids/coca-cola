// mehlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "mehlib.h"
#include <stdexcept>
#include <future>

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


