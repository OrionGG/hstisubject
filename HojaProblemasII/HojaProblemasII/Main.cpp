#include ".\Header Files\Ejercicio1.h"
#include ".\Header Files\Ejercicio4.h"
#include ".\Header Files\Ejercicio5.h"


int main( int argc, char** argv )
{
	if(argc > 0){
		char* filename = argv[argc-1];
		Ejercicio1::run(filename);
	}

	return EXIT_SUCCESS;
}
