#include "arrayToBMP.h"

int main()
{
	rgb24_t colors[] = { 0x0000FF, 0x00FF00,
						 0xFF0000, 0xFFFFFF
				};

	
	arrayToBMP::ArrayToBMP(colors,2,2,".\\test.bmp");
	std::cout << "finished" << std::endl;
	return 0;
}