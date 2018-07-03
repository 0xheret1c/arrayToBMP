#include "arrayToBMP.h"

int main()
{

	rgb24_t colors[1000* 1000];
	for (size_t i = 0; i < 1000 * 1000; i++)
	{
		colors[i] = (rgb24_t)i;
	}
	
	arrayToBMP::ArrayToBMP(colors, 1000, 1000,".\\test.bmp");
	std::cout << "finished" << std::endl;
	return 0;
}