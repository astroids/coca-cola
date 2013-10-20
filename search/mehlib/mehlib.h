#ifdef MEHLIB_EXPORTS
#define MEHLIB_API __declspec(dllexport)
#else 
#define MEHLIB_API __declspec(dllimport)
#endif
extern "C"{
	__declspec(dllexport) void adjustASMadap(unsigned char*, unsigned char *, short, INT32);
}

extern "C" {
	//r8 de gitti register yetmicek :D
	void _declspec(dllexport) adjustb(unsigned char*  a, short bar, INT32 size, unsigned char* orig);
};
