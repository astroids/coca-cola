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



std::vector<unsigned short> pic;
std::ifstream f("lolcpp.txt");
int redFlag = 0;
int whiteFlag = 0;
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
	print();
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


void incRed()
{
	
	redFlag++;
	std::cout << "yis RED "<< redFlag << std::endl;
}
void incWhite()
{
	whiteFlag++;
	std::cout << "yis WHT " << whiteFlag << std::endl;
}

//////////////////////////////////		PARAS
void incPara(){
	std::cout << "yis parazit" << std::endl;
	paras++;
	if (paras > 3){
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

	if (whiteFlag > 3){
		fadeToBlack();
	}
	redFlag = 0;
	whiteFlag = 0;
	resetPara;
}


bool isItWhite()
{
	std::cout << "WHT?" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << std::endl;
	if (pic[mainL] > 111)
	{
		if (pic[mainL - 2] < 111 && pic[mainL - 1] < 111)
		{
			incWhite();
#ifdef DEFRW_P 
			std::cout << "white  "<< whiteFlag  <<" ----"<<pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << " " << std::endl;
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

//////////////////////////////////		RED
bool isItRed()
{
	std::cout << "RED?" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << std::endl;
	if (pic[mainL] > 85)
	{
		if (pic[mainL - 2] < 35 && pic[mainL - 1] < 35)
		{
			incRed();
			resetPara();
#ifdef DEFR_P			
			std::cout << "RED  " << redFlag << " ----" << pic[mainL - 2] << " " << pic[mainL - 1] << " " << pic[mainL] << " " << std::endl;
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


void fadeToBlack()
{
#ifdef FADE
	size_t from = mainL - ((whiteFlag + redFlag)*3);
//	std::cout << "fading-----------" << std::endl;
	//if ((mainL - from)>200){
	std::cout << mainL - from << std::endl;

	system("pause");

	for(size_t i = from; i < mainL; i++)
	{
		pic[i] = 0;
		std::cout << pic[i] << " ";
		if ((i % 3)==0)std::cout << "\n";

	}
//	std::cout << "-----------------------------------------" << std::endl;
	resetRWFlags();

#endif
}


void RWAnalize()
{
	/// deneme amacli looppp geri duzelet           for (mainL = 2; mainL < pic.size() ; mainL+=3) offfff 2den basla
	for (mainL = 2; mainL < 500; mainL+=3)
	{
		if ((isItRed() == false) && redFlag > 0)
		{
			if (!isItWhite())
			{
				incPara();

			}if (whiteFlag>0){
				incWhite(); 
			}
		
			
		}

	}
}
