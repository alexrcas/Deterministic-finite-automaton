#pragma once

#include <iostream>
#include <vector>
#include "transition_t.hpp"

using namespace std;

/**
@class state
@brief Representa un estado del autómata
*/

class transition_t;

class state {
	private:
		int id_; ///<@brief ID del estado
		bool accept_;	///<@brief Indica si el estado es de aceptación
	public:
		inline state(): id_(0), accept_(false) {}	///<@brief Constructor por defecto
		inline state(int id, bool accept): id_(id), accept_(accept) {} ///<@brief Constructor @param id ID del estado @param accept Indica si el estado es de aceptación
		inline state(const state& Q): id_(Q.id_), accept_(Q.accept_) {}///<@brief Constructor de copia
		inline ~state() {} ///<@brief Destructor
		inline bool is_accept() const { return accept_; }	///<@brief Obtiene si el estado es de aceptación @returns TRUE si el estado es de aceptación
		inline bool& get_accept() { return accept_; }	///<@brief Obtiene si el estado es de aceptación @returns TRUE si el estado es de aceptación
		inline int get_id() const { return id_; }	///<@brief Devuelve la ID del estado @returns ID del estado
		inline int& get_id() { return id_; }	///<@brief Devuelve la ID del estado @returns ID del estado
		inline bool operator==(const state& Q) const { return id_ == Q.id_; }	///<@brief Sobrecarga del operador de comparación @returns Devuelve si los estados son iguales
		bool is_deadstate(vector<transition_t>);	///<@brief Obtiene si el estado es de muerte @param Conjunto de transiciones del autómata @returns TRUE si el estado es de muerte
		void print();	///@brief Muestra por pantalla la información del estado
};