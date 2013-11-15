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
#define LIMI 1000
#define RTr 79
#define RTb 35
#define RTg 35

#define Wrbg 111


/*
her kirmizidan sonra parazit sifirlamayi kadir
parazit limitini her redden sonra arttir

*/



void STATE0();
void readFile();
bool stateR();
void stateRW();
void stateRWR();
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
int paras = 0;
size_t mainL;									/* bu sayi parametre  olarak gelmesi lzmmmm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* dll yazarken async calismazsa buraya baaakkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk*/




//////////////////////////////////   MAIN
void main(){

	readFile();
	//print();
	std::cout << pic.size() << std::endl;
	picsize = pic.size();
	system("pause");

	mainL = 2;
	STATE0();
	std::cout << "Fin" << std::endl;
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
	for (mainL; mainL < 1000; mainL += 3)
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
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3)
	{
		//ilk 10 pixel kirmizi değilse direk don				
		if (pic[mainL] < RTr)
		{
			return false;

		}if ((pic[mainL - 2]) > RTb && (pic[mainL - 1]) > RTg)
		{
			return false;
		}
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
	paras = 0;						////////// burada geleck parazit degeri hesaplanabilir ama algoritmayi cok yavaslatabilir
	white1 = 1;

	//ilk 10 pixel
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3) {
		if ((pic[mainL] < Wrbg)){
			STATE0();
		}
		if ((pic[mainL - 2]) < Wrbg && (pic[mainL - 1] < Wrbg)) {
			STATE0();
		}
	}
	white1 += 10;

	for (mainL; mainL < LIMI; mainL += 3){
		if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg){
			if (pic[mainL]>RTr){
				stateRWR();
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
			}
		}


	}
}

void stateRWR(){
	paras = 0;
	red2 = 1;
	firstPhase = mainL + (white1 * 3);
	for (mainL; mainL < firstPhase; mainL += 3)									///bu *3 ten eksik olabilir
	{
		//ilk 10 pixel kirmizi değilse direk don				
		if (pic[mainL] < RTr)
		{
			STATE0();

		}if ((pic[mainL - 2]) > RTb && (pic[mainL - 1] > RTg))
		{
			STATE0();
		}
	}
	red2 = red1 + 1;																		//yukariyi degistirirsen burayida degistir

	std::cout << "RWR ye kadar dogru galiba" << std::endl;
	system("pause");




}