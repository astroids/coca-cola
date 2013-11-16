#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <future>

//#define DEFRW
//#define DEFRW_P
//#define DEFR
//#define DEFR_P
#define FADE
#define LIMI 1500
#define RTr 85
#define RTb 50
#define RTg 50

#define Wrbg 100


/*
	white 1 disinda gereksiz variable

*/



void STATE0();
void readFile();
bool stateR();
void stateRW();
void stateRWR();
void stateRWRW();
void jumpC1();
void jumpC1void();
void jumpA();

void incPara();
void fadeToBlack();
void resetRWFlags();
void print();


size_t firstPhase;
size_t picsize = 0;
std::vector<unsigned short> pic;
std::ifstream f("lolcpp.txt");
int red1 = 0;
int red2 = 0;
int white1 = 0;
int white2 = 0;
int Cwhite = 0;
int C2red = 0;
int STARTPOINT;

int paras = 0;
size_t mainL;									/* bu sayi parametre  olarak gelmesi lzmmmm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* dll yazarken async calismazsa buraya baaakkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk*/




//////////////////////////////////   MAIN
void main(){

	readFile();
	//print();
	std::cout << pic.size() << std::endl;
	picsize = pic.size();
	//system("pause");
	if (picsize == 0) {
		std::cout << "file not found" << std::endl;
		system("pause");

	}
	mainL = 2;
	STATE0();
	std::cout << "Fin" << mainL / 3 << std::endl;
	system("pause");
}

void readFile(){
	unsigned short temp;

	if (f){
		while (f.good())
		{
			f >> temp;
			pic.push_back(temp);
		}
	}

}
void print(){
	for (size_t i = 0; i < pic.size(); i++)
	{
		std::cout << pic[i] << " ";
		if ((i % 3) == 0){
			std::cout << "-- ";
		}if (i % 12 == 0){
			std::cout << std::endl;
		}
	}

}




//////////////////////////		DEBUGGER
void fadeToBlack()
{
#ifdef FADE
	size_t from = mainL - ((white1 + red1) * 3);
	//	std::cout << "fading-----------" << std::endl;
	//if ((mainL - from)>200){
	std::cout << mainL - from << std::endl;

	//system("pause");

	for (size_t i = from; i < mainL; i++)
	{
		pic[i] = 0;
		std::cout << pic[i] << " ";
		if ((i % 3) == 0)std::cout << "\n";

	}
	//	std::cout << "-----------------------------------------" << std::endl;


#endif
}
//////////////////////////		DEBUGGER


//////////////////////////////////////					STATE 0000000000000000000000000000000000
void STATE0()
{
	/// kirmizimi testi       for (mainL = 2; mainL < pic.size() ; mainL+=3) offfff 2den basla
	for (mainL; mainL < LIMI; mainL += 3)
	{
		if (pic[mainL] > RTr)
		{
			if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg)
			{
				stateR();

			}

		}
	}

}












////////////////////////////////////					STATE 1111111111111111111111111111111111111  burada firstphase gereksiz olabilir
bool stateR() {
	red1 = 1;
	paras = 0;
	std::cout << "stateR" << mainL / 3 << std::endl;
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3)
	{
		//ilk 10 pixel kirmizi değilse direk don				
		if (pic[mainL] > RTr)
		{
			if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg)
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
	for (mainL; mainL < LIMI; mainL += 3)
	{
		if (pic[mainL] > RTr) {
			if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg){
				red1++;
			}
			else if (pic[mainL] > Wrbg){
				if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg){
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



}


//////////////////////////////////  buradan sadece state 0 a donus var 
void stateRW(){
	std::cout << "stateRW" << mainL / 3 << " red1  " << red1 << std::endl;

	paras = 0;						////////// burada geleck parazit degeri hesaplanabilir ama algoritmayi cok yavaslatabilir
	white1 = 1;

	//ilk 10 pixel
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3) {
		if ((pic[mainL] < Wrbg)){
			STATE0();
			break;
		}
		if ((pic[mainL - 2]) < Wrbg && (pic[mainL - 1] < Wrbg)) {
			STATE0();
			break;
		}
	}
	white1 += 10;

	for (mainL; mainL < LIMI; mainL += 3){
		if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg){
			if (pic[mainL]>RTr){
				stateRWR();
				break;
			}
		}

		if (pic[mainL] > Wrbg){
			if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg) {
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
	std::cout << "stateRWR" << mainL / 3 << "  white1  " << white1 << std::endl;
	paras = 0;
	red2 = 1;
	firstPhase = mainL + (white1 * 3) - 3;
	for (mainL; mainL < firstPhase; mainL += 3)									///bu *3 ten eksik olabilir
	{

		if (pic[mainL] < RTr)
		{
			STATE0();
			break;
		}if ((pic[mainL - 2]) > RTb && (pic[mainL - 1] > RTg))
		{
			STATE0();
			break;
		}
		red2++;
	}
	red2 = white1 + 1;																		//yukariyi degistirirsen burayida degistir

	std::cout << "RWR ye kadar dogru galiba" << std::endl;
	//system("pause");
	mainL += ((red2 / 4) * 3);							//burayi napcaz bilmiyom
	stateRWRW();






}


void stateRWRW(){
	std::cout << "stateRWRW" << mainL / 3 << " red2 " << red2 << std::endl;
	white2 = 0;
	firstPhase = mainL + (white1 * 3);
	paras = (white1 / 3);
	for (mainL; mainL < firstPhase; mainL += 3)
	{
		std::cout << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << std::endl;

		if (pic[mainL] > Wrbg){
			if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg) {
				white2++;
			}
			else
			{
				//std::cout << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << std::endl;
				paras--;
				if (paras == 0){
					STATE0();
					break;
				}
			}
		}
	}
	//system("pause");
	std::cout << "STATE RWRW YUPP" << std::endl;
	jumpC1();

}







void jumpC1(){
	paras = 0;
	std::cout << "jumpC1 before " << mainL / 3 << " white2 " << white2 << std::endl;
	Cwhite = 0;
	mainL += (white1 * 6);
	std::cout << "jumpC1 after " << mainL / 3 << std::endl;
	firstPhase = mainL + ((white1) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (pic[mainL] > Wrbg){
			if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg) {
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

	std::cout << "after jumpC1 " << mainL / 3 << std::endl;
	jumpC1void();
}

void jumpC1void(){
	paras = 0;
	mainL += ((white1 / 2) * 3);
	std::cout << "jumpC1 startp  " << mainL / 3 << std::endl;
	firstPhase = mainL + ((white1 / 2) * 3);
	for (mainL; mainL < firstPhase; mainL += 3){
		if (pic[mainL]>RTr){
			if (pic[mainL - 2] < RTb && pic[mainL] < RTg){
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
	if (C2red < paras * 3){
		STATE0();
	}
	std::cout << "leaving jumpC1 " << mainL / 3 << std::endl;
	jumpA();
	
	

}

void jumpA(){
	paras = 0;
	//mainL = 


}