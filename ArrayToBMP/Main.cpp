#include "arrayToBMP.h"

int main()
{
	size_t size = 1000;
	size_t size2 = size * size;
	rgb24_t* colors = new rgb24_t[size2];
	for (size_t i = 0; i < size2; i++)
	{
		colors[i] = (rgb24_t)(i * 3.14159265359);
	}
	
	arrayToBMP::ArrayToBMP(colors, size, size,".\\test.bmp");
	std::cout << "finished" << std::endl;
	delete[] colors;
	return 0;
}