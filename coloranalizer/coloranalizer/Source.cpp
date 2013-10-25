#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>



void main(){
	std::vector<unsigned char> pic;
	std::ifstream f("lolcpp.txt");
	unsigned char temp;

	if (f){
		while (f.good())
		{
			f >> temp;
			pic.push_back(temp);
		}
	}
	for (size_t i = 0; i < pic.size(); i++)
	{
		std::cout << pic[i];
	}
	system("pause");
}