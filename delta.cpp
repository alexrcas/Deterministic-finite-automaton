#include "delta.hpp"

state* delta::get_transition(state& Q, char s)
{
	for(int i=0;i<E_.size();i++)
	{
		if((*E_[i].get_src() == Q) && (E_[i].get_symbol() == s))
			return  E_[i].get_dest();
	}
	return NULL;
}

int delta::get_sub_id(state& Q, set<set<state*> > P)
{
	set<state*> q_set;
	state* aux;
	for(set<set<state*> >::iterator i = P.begin(); i!= P.end(); i++)
	{
		q_set = *i;
		for(set<state*>::iterator j = q_set.begin(); j!= q_set.end(); j++)
		{
			aux = *j;
			if(*aux == Q)
				return distance(P.begin(), i);
		}
	}
}