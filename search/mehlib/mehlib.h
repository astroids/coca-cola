#ifdef MEHLIB_EXPORTS
#define MEHLIB_API __declspec(dllexport)
#else 
#define MEHLIB_API __declspec(dllimport)
#endif
extern "C"{
	__declspec(dllexport) void adjustASMadap(unsigned char*, short, INT32, unsigned char * ori);
}

extern "C" {
	void _declspec(dllexport) adjustb(unsigned char*  a, short bar, INT32 size, unsigned char* orig);
};

extern "C"{
	MEHLIB_API void  searchrw(unsigned char*  a, short bar, INT32 size, unsigned char* orig);

