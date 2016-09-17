#pragma once

#include <set>
#include <algorithm>
#include <fstream>
#include <cstring>
#include "state.hpp"
#include "transition_t.hpp"
#include "delta.hpp"

using namespace std;

/**
@class dfa
@brief Representa un Autómata Finito Determinista
*/

class dfa {
	private:
		vector<state> Q_;	///<@brief Conjunto de estados
		set<char> E_; ///<@brief Alfabeto
		delta D_;	///<@brief Función de transición
		unsigned int S_;	///<@brief ID del estado inicial
		ifstream* file_;	///<@brief Fichero de entrada
		int nt_;	///<@brief Numero de transiciones
	public:
		dfa(ifstream&);	///<@Constructor @param file Fichero de entrada
		inline ~dfa() {}	///<@brief Destructor
		bool trace_string(char* string); ///<@brief Traza una cadena @param Cadena @returns TRUE si la cadena es aceptada
		void print_info();	///<@brief Muestra el fichero de entrada
		void print_DFA();	///<@brief Muestra el DFA
		void print_dead_states();	///<@brief Muestra los estados de muerte
		
		void minimize();	///<@brief Minimiza el DFA
	private:
		set<set<state*> >  init_minimize();
		int get_subset(set<set<state*> >, state&, char);
		set<set<state*> > descomp(set<set<state*> >, char);
		void build_minimized(set<set<state*> >);
		bool accept_subset(set<state*>);
		void print_set(set<state*> Q); 
		void print_pi(set<set<state*> > P);
};
