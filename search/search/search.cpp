// search.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"



#include "search.h"
#include <stdexcept>
		
void  adjustASM(unsigned char* norm, unsigned char * ori, short bar, INT32 size);


/*
extern "C" {void _declspec(dllexport) adjustb(unsigned char*  norm,short bar, INT32 size ,unsigned char * ori){
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
*/