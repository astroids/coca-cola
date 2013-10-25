#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <future>

#define DEFRW
#define DEFRW_P
//#define DEFR
//#define DEFR_P
//#define FADE
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
bool isItRed(int i);
void resetRWFlags();
bool isItWhite(int i);
void print();
void readFile();
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



void resetRWFlags()
{

	if (whiteFlag > 3){
		fadeToBlack(mainL);
	}
	redFlag = 0;
	whiteFlag = 0;

}


bool isItWhite(int i)
{
	if (pic[i] > 120)
	{
		if (pic[i - 2] < 120 && pic[i - 1] < 120)
		{
			incWhite();
#ifdef DEFRW 
			std::cout << pic[i - 2] << " " << pic[i - 1] << " " << pic[i] << " " << std::endl;
#endif
#ifdef DEFRW_P
			system("pause");
#endif

			return true;
		}
		else return false;
	}
	else return false;
}

//////////////////////////////////		RED
bool isItRed(int i)
{
	if (pic[i] > 85)
	{
		if (pic[i - 2] < 30 && pic[i - 1] < 30)
		{
			incRed();
#ifdef DEFR_P			
			std::cout << pic[i - 2] << " " << pic[i - 1]<< " " << pic[i] <<" " << std::endl;
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

	for (mainL = 0; mainL < pic.size(); mainL++)
	{
		if ((isItRed(mainL) == false) && redFlag > 0)
		{
			if (!isItWhite(mainL))
			{
				incPara();

			}
		}

	}
}
