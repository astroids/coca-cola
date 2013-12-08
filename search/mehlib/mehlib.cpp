// mehlib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "mehlib.h"
#include <stdexcept>
#include <future>
#include <stdlib.h>


#define RTr 85
#define RTb 50
#define RTg 50
#define Wrbg 100




#include <iostream>	//kaldir bunu  butun io larla birlikte
#include <vector>
bool STATE0();
bool stateR();
bool stateRW();
bool stateRWR();
bool stateRWRW();
bool jumpC1();
bool jumpC1void();
bool jumpA1();
bool jumpA2void();
bool jumpA11();
bool jumpBigC();
bool jumpbigCvoid();
bool jumpBigL();
bool jumpEND();
bool fadeTOGREEN();


size_t limit;
size_t firstPhase;
size_t picsize = 0;
//std::vector<unsigned short> par;
unsigned char * par;
size_t banana = 0;
size_t white1 = 0;
size_t halfwhite = 0;
size_t STARTPOINT;
size_t vert;

bool lostAndFound = false;
size_t paras = 0;
size_t mainL = 2;

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

		std::async(std::launch::async, adjustASM, _norm, _ori, _bar, _size / 2);
		std::async(std::launch::async, adjustASM, n2, o2, _bar, _size / 2);

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



extern "C" { void _declspec(dllexport) searchrw(unsigned char*  sour, INT32 size,INT32 ver) {
	vert = ver*3;			//bu videoda birkere
	par = sour;
	limit = size - 1000;
	mainL = 2;
	STATE0();

}
}



//////////////////////////////////////					STATE 0000000000000000000000000000000000
bool STATE0()
{
	///bunlari azalttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
	banana = 0;
	white1 = 0;
	halfwhite = 0;
	paras = 0;

	/// kirmizimi testi       for (mainL = 2; mainL < par.size() ; mainL+=3) offfff 2den basla
	for (mainL; mainL < limit; mainL += 3)
	{
		if (par[mainL] > RTr)
		{
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg)
			{
				stateR();

			}

		}
	}
	return 0;
}












////////////////////////////////////					STATE 1111111111111111111111111111111111111  burada firstphase gereksiz olabilir
bool stateR() {
	STARTPOINT = mainL;
	banana = 1;
	paras = 0;
	firstPhase = mainL + 15;
	for (mainL; mainL < firstPhase; mainL += 3)
	{
		//ilk 10 pixel kirmizi değilse direk don				
		if (par[mainL] > RTr)
		{
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg)
			{
				banana++;

			}
			else
			{
				paras++;
			}
		}
	}
	if (banana < paras)
	{
		return false;
	}


	banana = 6;


	/// artik kirmizimi deilse beyazmı
	for (mainL; mainL < limit; mainL += 3)
	{
		if (par[mainL] > RTr) {
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				banana++;
			}
			else if (par[mainL] > Wrbg){
				if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg){
					return stateRW();
					
				}
			}
			else {
				paras++;							////////////      kirmizi paraziti bu değeri ince ayarla
				if (paras * 3 > banana){
					return false;
				}

			}

		}



	}
	return lostAndFound;


}


//////////////////////////////////  buradan sadece state 0 a donus var 
bool stateRW(){
	STARTPOINT = mainL;
	paras = 0;						////////// burada geleck parazit degeri hesaplanabilir ama algoritmayi cok yavaslatabilir
	white1 = 1;

	//ilk 10 pixel
	firstPhase = mainL + 15;
	for (mainL; mainL < firstPhase; mainL += 3) {
		if ((par[mainL] < Wrbg)){
			return STATE0();
			 
		}
		if ((par[mainL - 2]) < Wrbg && (par[mainL - 1] < Wrbg)) {
			return STATE0();
			
		}
	}
	white1 += 5;

	for (mainL; mainL < limit; mainL += 3){
		if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
			if (par[mainL]>RTr){
				return stateRWR();
			}
		}

		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				white1++;
			}
		}
		else
		{
			paras++;
			if (paras * 3 > white1){
				return STATE0();
			}
		}


	}return 0;
}


////////////////////////////////////////////					hic paraziti umursamiyor????????????
bool stateRWR(){
		if (limit < (36 * white1) + mainL){
			return STATE0(); 
		}
		else if (white1 > (vert / 16)){
			return STATE0;
		}else
		{


			paras = 0;
			banana = 1;
			halfwhite = (white1 / 2);
			firstPhase = mainL + (white1 * 3) - 3;
			for (mainL; mainL < firstPhase; mainL += 3)									///bu *3 ten eksik olabilir
			{

				if (par[mainL] < RTr)
				{
					return STATE0();
					
				}if ((par[mainL - 2]) > RTb && (par[mainL - 1] > RTg))
				{
					return STATE0();
					
				}
				banana++;
			}
			//banana = white1 + 1;																		//yukariyi degistirirsen burayida degistir

			mainL += ((white1 / 4) * 3);							//burayi napcaz bilmiyom
			return stateRWRW(); 

		}




}


bool stateRWRW(){
	banana = 0;
	paras = 0;
	firstPhase = mainL + (white1 * 3);
	paras = (white1 / 3);
	for (mainL; mainL < firstPhase; mainL += 3)
	{

		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				banana++;
			}
		}
		else
		{
			paras--;
			if (paras == 0){
				return STATE0();
				
			}
		}
	}
	return jumpC1();
}









//coc
bool jumpC1(){
	paras = 0;
	banana = 0;
	mainL += (white1 * 6);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				banana++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (banana < paras * 3){
		return STATE0(); 
	}

	return jumpC1void(); 
}




/// coc boslugu
bool jumpC1void(){
	paras = 0;
	banana = 0;
	mainL += ((( white1 / 2)) * 3);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				banana++;
			}
			else
			{
				paras++;
			}

		}
		else
		{
			paras++;
		}

	}
	if (banana < (paras * 3)){
		return STATE0();
	}
	else
	{
		return jumpA1();
	}




}

//coc a baslangic
bool jumpA1(){
	paras = 0;
	mainL += (white1 * 3);
	firstPhase = mainL + (( white1 / 2) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				banana++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (banana < paras * 3){
		return STATE0();
	}
	else
	{
		return jumpA2void();

	}


}

//coca a orta
bool jumpA2void(){
	paras = 0;
	banana = 0;
	mainL += ((white1) * 3);
	firstPhase = mainL + ((white1 / 2) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				banana++;
			}
			else
			{
				paras++;
			}

		}
		else
		{
			paras++;
		}

	}
	if (banana < (paras * 3)){
		return STATE0();
	}
	else
	{
		return jumpA11();
	}



}


//coca a son
bool jumpA11(){
	paras = 0;
	banana = 0;
	mainL += (( white1 / 2) * 3);
	firstPhase = mainL + (white1 / 2) * 3;
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				banana++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (banana < paras * 3){
		return STATE0();
	}
	else
	{
		return jumpBigC();

	}


}

//coca C beyaz
bool jumpBigC(){
	paras = 0;
	banana = 0;
	mainL += ((white1) * 9);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				banana++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (banana < paras * 3){
		return STATE0();
	}
	else
	{
		return jumpbigCvoid();

	}


}

// coca C-o arasi  kirmizi
bool jumpbigCvoid(){
	paras = 0;
	banana = 0;
	mainL += ((white1 * 5) * 3);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				banana++;
			}
			else
			{
				paras++;
			}

		}
		else
		{
			paras++;
		}

	}
	if (banana < paras * 3){
		return STATE0();
	}
	else
	{
		return jumpBigL();

	}


}

//coca Col  i 
bool jumpBigL(){
	paras = 0;
	banana = 0;
	mainL += (((white1 * 4) + halfwhite) * 3);
	firstPhase = mainL + ((halfwhite) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				banana++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (banana < paras * 3){
		return STATE0();
	}
	else
	{
		return jumpEND();

	}

}
// son kirmizi
bool jumpEND(){
	paras = 0;
	banana = 0;
	mainL += ((white1 * 4) * 3);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				banana++;
			}
			else
			{
				paras++;
			}

		}
		else
		{
			paras++;
		}

	}
	if (banana < (paras * 3)){
		return STATE0(); 
	}
	else
	{
		return fadeTOGREEN();
	}



}

bool fadeTOGREEN(){

	
	///																							burası array overflova davet
	for (size_t i = 0; i < 5; i++)
	{
		
		for (STARTPOINT; STARTPOINT < mainL; STARTPOINT++)
		{
			par[STARTPOINT] = 0;
		}
		STARTPOINT += vert*3;
		mainL += vert*3;
	}

	//system("exit");
	//STARTPOINT = limit;
	lostAndFound = true;
	return 1;
}