#pragma once

#include "state.hpp"

class state;

using namespace std;

/**
@class transition_t
@brief Representa una transición para un estado y un símbolo de entrada
*/
class transition_t {
	private:
		state* src_;	///<@brief Estado inicial
		state* dest_;	///<@brief Estado al que se transita
		char symbol_;	///<@brief Símbolo de entrada para el estado inicial
	public:
		inline transition_t(state& src, state& dest, char symbol): src_(&src), dest_(&dest), symbol_(symbol) {}	///<@brief Constructor
		~transition_t() {}; ///<@brief Destructor
		inline state* get_src() const { return src_; } ///<@brief Devuelve el estado inicial @returns Puntero al estado inicial
		inline state* get_dest() const { return dest_; }	///<@brief Devuelve el estado final @returns Puntero al estado final
		inline char get_symbol() const { return symbol_; }	///<@brief Devuelve el símbolo necesario para la transición @returns Símbolo para realizar la transición
};