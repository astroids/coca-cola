#ifdef MEHLIB_EXPORTS
#define MEHLIB_API __declspec(dllexport)
#else 
#define MEHLIB_API __declspec(dllimport)
#endif
extern "C"{
	__declspec(dllexport) void adjustASMadap(unsigned char*, unsigned char *, short, INT32);
}