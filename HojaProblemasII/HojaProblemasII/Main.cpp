#include ".\Header Files\Ejercicio1.h"
#include ".\Header Files\Ejercicio2.h"
#include ".\Header Files\Ejercicio4.h"
#include ".\Header Files\Ejercicio5.h"
#include ".\Header Files\Ejercicio6.h"


vector<int> getEjerciciosToRun(int argc, char** argv){
	vector<int> vResult;
	for(int i = 1; i < argc; i++){
		string sArgv = argv[i];
		if(sArgv == "Ejercicio1" || sArgv == "Ejercicio2" 
			|| sArgv == "Ejercicio4" || sArgv == "Ejercicio5" 
			|| sArgv == "Ejercicio6"){
				
			vResult.push_back(i);
		}
	}
	
	return vResult;
}

int main( int argc, char** argv ){
	
	if(argc > 1){

		vector<int> vEjercicioParam = getEjerciciosToRun(argc, argv);

		for(int i = 0; i < vEjercicioParam.size(); i++){
			int iParam = vEjercicioParam.at(i);
			string sSelectedEjercicio = argv[iParam];
			if(sSelectedEjercicio == "Ejercicio1"){
				if(argc > iParam){
					Ejercicio1::run(argv[iParam+1]);
				}
			}
			else if (sSelectedEjercicio == "Ejercicio2"){
				if(argc > iParam){
					Ejercicio2::run(argv[iParam+1]);
				}

			}
			else if (sSelectedEjercicio == "Ejercicio4"){
				if(argc > iParam){
					Ejercicio4::run(argv[iParam+1]);
				}

			}
			else if (sSelectedEjercicio == "Ejercicio5"){
				if(argc > iParam){
					Ejercicio5::run(argv[iParam+1]);
				}

			}
			else if (sSelectedEjercicio == "Ejercicio6"){
				if(argc > iParam){
					Ejercicio6::run(argv[iParam+1]);
				}

			}
		}
	}

	return EXIT_SUCCESS;
}
