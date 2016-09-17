#pragma once

#include <iostream>
#include <cstdlib>
#include "dfa.hpp"

using namespace std;

/**
@class Interface
@brief Ofrece una interfaz para aligerar el código en el programa principal
*/

class Interface {
	public:
		inline Interface() {}	///<@brief Constructor
		inline ~Interface() {}	///<@brief Destructor
		void display_menu();	///<@brief Muestra el menú
		void select_option(char, dfa&, ifstream*);	///<@brief Ofrece la interacción al usuario @param op Opción elegida @parm DFA Referencia a un DFA @param file Puntero al fichero de entrada
};