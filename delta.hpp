#pragma once

#include<set>
#include <algorithm>
#include "transition_t.hpp"
#include "state.hpp"

using namespace std;

/**
@class delta
@brief Representa la función de transición
*/
class delta {
	private:
		vector<transition_t> E_; ///<@brief Conjunto de transiciones
	public:
		inline delta() {} ///<@brief Constructor
		inline ~delta() {}	///<@brief Destructor
		state* get_transition(state&, char); ///<@brief Obtiene una transicion @param Q Estado actual @param s Símbolo de entrada @returns Estado siguiente
		int get_sub_id(state& Q, set<set<state*> > P);
		inline vector<transition_t>& get() { return E_; }	///<@brief Permite acceder al conjunto de transiciones @returns Conjunto de transiciones
};

