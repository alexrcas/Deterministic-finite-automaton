/**
@mainpage
@brief Simulación de un Autómata Finito Determinista (DFA)
@author Alexis Rodríguez Casañas (L10)
@date 13/10/2015
*/
#include "dfa.hpp"
#include "interface.hpp"

int main(int argc, char** argv)
{
	dfa* DFA;
	ifstream* file;
	Interface I;
	char filename[256];
	char op;
	
	do {
		if(argc==2)
		{
			strcpy(filename, argv[1]);
			argc=0;
		}
		else
		{
		cout<<"Nombre del fichero (0 para salir): ";
		cin>>filename;
		}
		file = new ifstream(filename);
		if(file->is_open())
		{
			DFA = new dfa(*file);
			do
			{
				I.display_menu();
				cin>>op;
				I.select_option(op, *DFA, file);
			}while(op!='5');
		}
		else
			cerr<<"ERROR. No se encuentra el fichero"<<endl;
	}while(strcmp(filename, "0"));
	return 0;
}