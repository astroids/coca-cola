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


/*
	her kirmizidan sonra parazit sifirlamayi kadir
	parazit limitini her redden sonra arttir

*/


size_t picsize = 0;
std::vector<unsigned short> pic;
std::ifstream f("lolcpp.txt");
int red1 = 0;
int white1 = 0;
int paras = 0;
size_t mainL;

void incPara();
void fadeToBlack();
void RWAnalize();
void incWhite();
void incRed();
bool isItRed();
void resetRWFlags();
bool isItWhite();
void print();
void readFile();
//////////////////////////////////   MAIN
void main(){

	readFile();
	//print();
	std::cout << pic.size() << std::endl;
	picsize = pic.size();
	system("pause");
	
	RWAnalize();
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
		std::cout << pic[i]<<" ";
		if ((i % 3)==0){
			std::cout << "-- ";
		}if (i % 12==0){
			std::cout << std::endl;
		}
	}

}



void incWhite()
{
	white1++;
	std::cout << "yis WHT " << white1 << std::endl;
}

//////////////////////////////////		PARAS
void incPara(){
	std::cout << "yis parazit" << std::endl;
	paras++;
	if (paras > (red1/5)){
		resetRWFlags();
	}
}
void resetPara(){
	paras = 0;
	std::cout << "parazit 0landi" << std::endl;

	//resetRWFlags();
}


void resetRWFlags()
{
	std::cout << "hepsi sifirlandi" << std::endl;

	if ((white1/3) >paras){
		fadeToBlack();
	}
	red1 = 0;
	white1 = 0;
	resetPara();
}




//////////////////////////////////		RED1111111111
bool isItRed()
{
	std::cout << "RED?" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << std::endl;
	if (pic[mainL] > 79)
	{
		if (pic[mainL - 2] < 35 && pic[mainL - 1] < 35)
		{
			incRed();
			resetPara();
#ifdef DEFR_P			
			std::cout << "RED  " << red1 << " ----" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << " " << std::endl;
#endif

#ifdef DEFR 	

			system("pause");
#endif

			return true;
		}
		else {
			
			return false;
		}
	}
	else return false;


}
void incRed()
{

	red1++;
	std::cout << "yis RED " << red1 << std::endl;
}


///////////////////////////  STATE RED  WHITE

bool isItWhite()
{
	std::cout << "WHT?" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << std::endl;
	if (pic[mainL] > 111)
	{
		if (pic[mainL - 2] < 111 && pic[mainL - 1] < 111)
		{
			incWhite();
#ifdef DEFRW_P 
			std::cout << "white  " << white1 << " ----" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << " " << std::endl;
#endif
#ifdef DEFRW
			system("pause");
#endif
			//resetPara();
			return true;
		}
		else {

			return false;
		}
	}
	else return false;
}
//////////////////////////


//////////////////////////		DEBUGGER
void fadeToBlack()
{
#ifdef FADE
	size_t from = mainL - ((white1 + red1)*3);
//	std::cout << "fading-----------" << std::endl;
	//if ((mainL - from)>200){
	std::cout << mainL - from << std::endl;

	//system("pause");

	for(size_t i = from; i < mainL; i++)
	{
		pic[i] = 0;
		std::cout << pic[i] << " ";
		if ((i % 3)==0)std::cout << "\n";

	}
//	std::cout << "-----------------------------------------" << std::endl;
	

#endif
}
//////////////////////////		DEBUGGER



void RWAnalize()
{
	/// deneme amacli looppp geri duzelet           for (mainL = 2; mainL < pic.size() ; mainL+=3) offfff 2den basla
	for (mainL = 2; mainL < 1000; mainL+=3)
	{
		//std::cout << mainL << std::endl;
		if ((isItRed() == false) && red1 > 0)
		{
			if (!isItWhite())
			{
				incPara();

			}if (white1>0){
				incWhite(); 
			}
		
			
		}

	}
}
