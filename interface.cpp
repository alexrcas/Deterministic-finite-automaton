#include "interface.hpp"

void Interface::display_menu()
{
	cout<<"\n===== MENU PRINCIPAL ====="<<endl;
	cout<<"1. Ver fichero"<<endl;
	cout<<"2. Mostrar DFA"<<endl;
	cout<<"3. Identificar estados de muerte"<<endl;
	cout<<"4. Analizar cadena"<<endl;
	cout<<"5. Abrir un nuevo fichero"<<endl;
	cout<<"6. Minimizar DFA"<<endl;
	cout<<"7. Salir"<<endl;
}

void Interface::select_option(char op, dfa& DFA, ifstream* file)
{
	char string[256];
	switch(op)
	{
		case '1':
			DFA.print_info();
			break;
		case '2':
			DFA.print_DFA();
			break;
		case '3':
			DFA.print_dead_states();
			break;
		case '4':
			cout<<"Introducir cadena: ";
			cin>> string;
			if(DFA.trace_string(string))
				cout<<"\nCADENA ACEPTADA"<<endl;
			else
				cout<<"\nCADENA RECHAZADA"<<endl;
			break;
		case '5':
			op='5';
			file->close();
			break;
		case '6':
			cout<<"Minimizar"<<endl;
			DFA.minimize();
			delete &DFA;
			DFA = *new const dfa (*new ifstream("minimized.dfa"));
			break;
		case '7':
			file->close();
			exit(0);
			break;
		default:
		cout<<"Opcion no valida!"<<endl;
	}
}