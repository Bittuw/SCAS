// skud.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int main(int argc, char** argv)
{
	if (argc > 1) {
		if (strncmp(argv[1], "-start", strlen(argv[1])));
		if (strncmp(argv[1], "-stop", strlen(argv[1])));
		if (strncmp(argv[1], "-find_device", strlen(argv[1])));
		if (strncmp(argv[1], "-h", strlen(argv[1])));
	}
	else {
		return -1;
	}

	return 0;
}

