#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <future>

//#define DEFRW
#define DEFRW_P
//#define DEFR
#define DEFR_P
#define FADE


std::vector<unsigned short> pic;
std::ifstream f("lolcpp.txt");
int redFlag = 0;
int whiteFlag = 0;
int paras = 0;
size_t mainL;

void incPara();
void fadeToBlack(int from);
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
}
void incWhite()
{
	whiteFlag++;

}

//////////////////////////////////		PARAS
void incPara(){
	paras++;
	if (paras > 3){
		resetRWFlags();
	}
}
void resetPara(){
	paras = 0;
	//resetRWFlags();
}


void resetRWFlags()
{

	if (whiteFlag > 3){
		fadeToBlack(mainL);
	}
	redFlag = 0;
	whiteFlag = 0;

}


bool isItWhite()
{
	if (pic[mainL] > 120)
	{
		if (pic[mainL - 2] < 120 && pic[mainL - 1] < 120)
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
	if (pic[mainL] > 85)
	{
		if (pic[mainL - 2] < 30 && pic[mainL - 1] < 30)
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


void fadeToBlack(int from)
{
#ifdef FADE
	size_t to = from + ((whiteFlag + redFlag)*3);

	for (int i = from; i < to; i++)
	{
		pic[i] = 0;
		std::cout << pic[i] << " ";
		if ((i % 3)==0)std::cout << "\n";

	}
	std::cout << "-----------------------------------------" << std::endl;
	resetRWFlags();
#endif
}
void RWAnalize()
{

	for (mainL = 0; mainL < pic.size(); mainL+=3)
	{
		if ((isItRed() == false) && redFlag > 0)
		{
			if (!isItWhite())
			{
				incPara();

			}if (whiteFlag){
				incWhite(); 
				resetPara();
			}
		}if (redFlag){
			incPara();
			resetPara();
		}

	}
}
