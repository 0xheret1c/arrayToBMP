#include "arrayToBMP.h"

int main()
{
	rgb24_t colors[] = { 0xAABBCC, 0xAABBCC, 0xAABBCC,
						 0xAABBCC, 0xFFFFFF, 0xAABBCC,
						 0xAABBCC, 0xAABBCC, 0xAABBCC,
	};
	arrayToBMP::ArrayToBMP(colors,3,3,".\\test.bmp");
	std::cout << "finished" << std::endl;
	return 0;
}