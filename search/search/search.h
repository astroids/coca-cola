#ifdef SEARCHING_EXPORTS
#define SEARCHING_API __declspec(dllexport)
#else 
#define SEARCHING_API __declspec(dllimport)
#endif
extern "C" {
		//r8 de gitti register yetmicek :D
	void _declspec(dllexport) adjustb(unsigned char*  a, short bar, INT32 size,unsigned char* orig);
};

