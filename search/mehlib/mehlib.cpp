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
void STATE0();
bool stateR();
void stateRW();
void stateRWR();
void stateRWRW();
void jumpC1();
void jumpC1void();
void jumpA1();
void jumpA2void();
void jumpA11();
void jumpBigC();
void jumpbigCvoid();
void jumpBigL();
void jumpEND();
void fadeTOGREEN();


size_t limit;
size_t firstPhase;
size_t picsize = 0;
//std::vector<unsigned short> par;
unsigned char * par;
int red1 = 0;
int red2 = 0;
int white1 = 0;
int halfwhite = 0;
int white2 = 0;
int Cwhite = 0;
int C2red = 0;
size_t STARTPOINT;
int A1white = 0;
int A2red = 0;
int bigC = 0;
int bigCvoid = 0;
int bigLwhite = 0;
int endRed = 0;
bool lostAndFound = false;
int paras = 0;
size_t mainL=2;

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



extern "C" { void _declspec(dllexport) searchrw(unsigned char*  sour, INT32 size) {
	par = sour;
	limit = size;
	STATE0();

}
}



//////////////////////////////////////					STATE 0000000000000000000000000000000000
void STATE0()
{
	///bunlari azalttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
	red1 = 0;
	red2 = 0;
	white1 = 0;
	halfwhite = 0;
	white2 = 0;
	Cwhite = 0;
	C2red = 0;
	A1white = 0;
	A2red = 0;
	bigC = 0;
	bigCvoid = 0;
	bigLwhite = 0;
	endRed = 0;
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

}












////////////////////////////////////					STATE 1111111111111111111111111111111111111  burada firstphase gereksiz olabilir
bool stateR() {
	STARTPOINT = mainL;
	red1 = 1;
	paras = 0;
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3)
	{
		//ilk 10 pixel kirmizi değilse direk don				
		if (par[mainL] > RTr)
		{
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg)
			{
				red1++;

			}
			else
			{
				paras++;
			}
		}
	}
	if (red1 < paras)
	{
		return false;
	}


	red1 = 11;


	/// artik kirmizimi deilse beyazmı
	for (mainL; mainL < limit; mainL += 3)
	{
		if (par[mainL] > RTr) {
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				red1++;
			}
			else if (par[mainL] > Wrbg){
				if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg){
					stateRW();
					break;
				}
			}
			else {
				paras++;							////////////      kirmizi paraziti bu değeri ince ayarla
				if (paras * 3 > red1){
					return false;
				}

			}

		}



	}
	return lostAndFound;


}


//////////////////////////////////  buradan sadece state 0 a donus var 
void stateRW(){

	paras = 0;						////////// burada geleck parazit degeri hesaplanabilir ama algoritmayi cok yavaslatabilir
	white1 = 1;

	//ilk 10 pixel
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3) {
		if ((par[mainL] < Wrbg)){
			STATE0();
			break;
		}
		if ((par[mainL - 2]) < Wrbg && (par[mainL - 1] < Wrbg)) {
			STATE0();
			break;
		}
	}
	white1 += 10;

	for (mainL; mainL < limit; mainL += 3){
		if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
			if (par[mainL]>RTr){
				stateRWR();
				break;
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
				STATE0();
				break;
			}
		}


	}
}


////////////////////////////////////////////					hic paraziti umursamiyor????????????
void stateRWR(){
	paras = 0;
	red2 = 1;
	halfwhite = white1 / 2;
	firstPhase = mainL + (white1 * 3) - 3;
	for (mainL; mainL < firstPhase; mainL += 3)									///bu *3 ten eksik olabilir
	{

		if (par[mainL] < RTr)
		{
			STATE0();
			break;
		}if ((par[mainL - 2]) > RTb && (par[mainL - 1] > RTg))
		{
			STATE0();
			break;
		}
		red2++;
	}
	red2 = white1 + 1;																		//yukariyi degistirirsen burayida degistir

	mainL += ((red2 / 4) * 3);							//burayi napcaz bilmiyom
	stateRWRW();






}


void stateRWRW(){
	white2 = 0;
	firstPhase = mainL + (white1 * 3);
	paras = (white1 / 3);
	for (mainL; mainL < firstPhase; mainL += 3)
	{

		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				white2++;
			}
			else
			{
				paras--;
				if (paras == 0){
					STATE0();
					break;
				}
			}
		}
	}
	jumpC1();

}







void jumpC1(){
	paras = 0;
	Cwhite = 0;
	mainL += (white1 * 6);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				Cwhite++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (Cwhite < paras * 3){
		STATE0();
	}

	jumpC1void();
}





void jumpC1void(){
	paras = 0;
	C2red = 0;
	mainL += ((white1 / 2) * 3);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				C2red++;
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
	if (C2red < (paras * 3)){
		STATE0();
	}
	else
	{
		jumpA1();
	}




}
void jumpA1(){
	paras = 0;
	mainL += (white1 * 3);
	firstPhase = mainL + ((white1 / 2) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				A1white++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (A1white < paras * 3){
		STATE0();
	}
	else
	{
		jumpA2void();

	}


}


void jumpA2void(){
	paras = 0;
	A2red = 0;
	mainL += ((white1) * 3);
	firstPhase = mainL + ((white1 / 2) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				A2red++;
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
	if (A2red < (paras * 3)){
		STATE0();
	}
	else
	{
		jumpA11();
	}



}

void jumpA11(){
	paras = 0;
	A1white = 0;
	mainL += ((white1 / 2) * 3);
	firstPhase = mainL + ((white1 / 2) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				A1white++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (A1white < paras * 3){
		STATE0();
	}
	else
	{
		jumpBigC();

	}


}

void jumpBigC(){
	paras = 0;
	mainL += ((white1) * 9);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				bigC++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (bigC < paras * 3){
		STATE0();
	}
	else
	{
		jumpbigCvoid();

	}


}


void jumpbigCvoid(){
	paras = 0;
	bigCvoid = 0;
	mainL += ((white1 * 5) * 3);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				bigCvoid++;
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
	if (bigCvoid < paras * 3){
		STATE0();
	}
	else
	{
		jumpBigL();

	}


}

void jumpBigL(){
	paras = 0;
	bigLwhite = 0;
	mainL += (((white1 * 4) + halfwhite) * 3);
	firstPhase = mainL + ((halfwhite) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > Wrbg){
			if (par[mainL - 2] > Wrbg && par[mainL - 1] > Wrbg) {
				bigLwhite++;
			}
		}
		else
		{
			paras++;
		}
	}
	if (bigLwhite < paras * 3){
		STATE0();
	}
	else
	{
		jumpEND();

	}

}

void jumpEND(){
	paras = 0;
	endRed = 0;
	mainL += ((white1 * 4) * 3);
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (par[mainL] > RTr){
			if (par[mainL - 2] < RTb && par[mainL - 1] < RTg){
				endRed++;
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
	if (endRed < (paras * 3)){
		STATE0();
	}
	else
	{
		fadeTOGREEN();
	}



}

void fadeTOGREEN(){
	for (STARTPOINT; STARTPOINT < mainL; STARTPOINT++ )
	{
		par[STARTPOINT] = 0;
	}
	//system("exit");
	//STARTPOINT = limit;
	lostAndFound = true;
}