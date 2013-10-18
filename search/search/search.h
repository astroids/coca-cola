#ifdef SEARCHING_EXPORTS
#define SEARCHING_API __declspec(dllexport)
#else 
#define SEARCHING_API __declspec(dllimport)
#endif

/*
extern "C" {
		//r8 de gitti register yetmicek :D
	void _declspec(dllexport) adjustb(unsigned char*  a, short bar, INT32 size,unsigned char* orig);
};
*/
//																rcx,				  rdx       r8w		    r9d
extern "C"{	void _declspec (dllexport) adjustASM(unsigned char* norm, unsigned char * ori, short bar, INT32 size);}
