#include "state.hpp"

bool state::is_deadstate(vector<transition_t> trans)
{
	bool is_dead = true;
	for(int i=0;i<trans.size();i++)
		if ((trans[i].get_src() == this) && (trans[i].get_dest() != this))
			is_dead = false;
	return is_dead;
}

void state::print()
{
	cout<<"\nID: "<<id_<<endl;
	//cout<<"ACEPTACION: "<<accept_<<endl;
}