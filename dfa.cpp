#include "dfa.hpp"

dfa::dfa(ifstream& file)
{
	file_ = &file;
	int nq, id;
	bool accept;
	char s, dummy;
	char buffer[256];
	
	file >> nq >> S_;
	
	for(int i=0;i<nq;i++)
		Q_.push_back(state());
	for(int i=0;i<nq;i++)
	{
		file >> id >> accept >> nt_;
		Q_[i].get_id() = id;
		Q_[i].get_accept() = accept;
		for(int j=0;j<nt_;j++)
		{
			file >> s >> id;
			D_.get().push_back(transition_t(Q_[i], Q_[id], s));
			E_.insert(s);
		}
	}
	
}

bool dfa::trace_string(char* string)
{
	state* S = &Q_[S_];
	state* aux;
	int i=0;
	cout<<"Estado: "<< S->get_id()<<"\t";
	do {
		cout<<"Simbolo: "<<string[i]<<"\t";
		S = D_.get_transition(*S, string[i++]);
		if(S!=NULL)
		{
			cout<<"Siguiente: "<< S->get_id()<<endl;
			cout<<"Estado: "<< S->get_id()<<"\t";
		}
		else
		{
			cerr<<"\nERROR. Alfabeto no reconocido"<<endl;
			return false;
		}
	} while(i<strlen(string));
	return S->is_accept();
}

void dfa::print_info()
{
	cout<<"\nFICHERO DFA:"<<endl;
	file_->seekg(0, ios::beg);
	char aux[256];
	while(!file_->eof())
	{
		file_->getline(aux, 256);
		cout<<aux<<endl;
	}
}

void dfa::print_DFA()
{
	cout<<"\nESTADOS DEL DFA: "<<endl;
	for(int i=0;i<Q_.size();i++)
		Q_[i].print();
}

void dfa::print_dead_states()
{
	cout<<"\nESTADOS DE MUERTE: "<<endl;
	for(int i=0;i<Q_.size();i++)
	{
		if (Q_[i].is_deadstate(D_.get()))
			Q_[i].print();
	}
}

/**
@brief Obtiene el DFA mínimo
*/
void dfa::minimize()
{
	set<set<state*> > P = init_minimize();
	set<set<state*> > NP;

	NP = P;
	do
	{
		P = NP;
		for(set<char>::iterator i = E_.begin(); i!= E_.end(); i++)
		{
			NP = descomp(NP, *i);
			cout<<"Conjunto P"<<endl;
			print_pi(P);
			cout<<"Dividiendo con simbolo: "<<*i<<endl;
			print_pi(NP);
		}
	}while(NP != P);
	build_minimized(NP);
}

/**
@brief Inicializa el conjunto PI para comenzar a aplicar el algoritmo de minimización
@returns  Conjunto que contiene el subconjunto de estados finales y no finales
*/
set<set<state*> > dfa::init_minimize()
{
	set<set<state*> > P;
	set<state*> aux;
	set<state*> auxacc;
	for(int i=0;i<Q_.size();i++)
	{
		if(Q_[i].is_accept())
			auxacc.insert(&Q_[i]);
		else
			aux.insert(&Q_[i]);
	}
	P.insert(aux);
	P.insert(auxacc);
	return P;
}

/**
@brief Obtiene el índice del subconjunto al que transita un estado con un símbolo
@param P Conjunto de particiones
@param Q Estado
@param S Símbolo de entrada
@returns  Índice del subconjunto
*/
int dfa::get_subset(set<set<state*> > P, state& Q, char S)
{
	state* aux = D_.get_transition(Q, S);
	set<state*> qset;
	int dst;
	for(set<set<state*> >::iterator i = P.begin(); i!= P.end(); i++)
	{
		qset = *i;
		for(set<state*>::iterator j = qset.begin(); j!= qset.end(); j++)
		{
			if ( *j == aux )
				return distance(P.begin(), i);
		}
	}
}

/**
@brief Parte los subconjuntos en otros más pequeños con un símmbolo
@returns  Nuevo conjunto de particiones
*/
set<set<state*> > dfa::descomp(set<set<state*> > P, char symbol)
{
	set<state*> aux;
	set<state*> aux2;
	state* dmy;
	int index;
	set<state*> np;
	set<set<state*> > NP;
	for(set<set<state*> >::iterator i = P.begin(); i!= P.end(); i++)
	{
		aux = *i;
		set<state*>::iterator inx = aux.begin();
		dmy = *inx;
		index = get_subset(P, *dmy, symbol);
		for(set<state*>::iterator j = aux.begin(); j!= aux.end(); j++)
		{
			dmy = *j;
			if (index != get_subset(P, *dmy, symbol))
				np.insert(dmy);
		}
		set_difference(aux.begin(), aux.end(), np.begin(), np.end(), inserter(aux2, aux2.end()));
		NP.insert(aux2);
		NP.insert(np);
		np.clear();
		aux.clear();
		aux2.clear();
	}
	aux = *NP.begin();
	if(aux.empty())
		NP.erase(NP.begin());
	return NP;
}

void dfa::build_minimized(set<set<state*> > P)
{
	ofstream* file = new ofstream("minimized.dfa");
	state* aux;
	set<state*> qset;
	if(P.size() == Q_.size())
		cout<<"\nNo es necesario generar un nuevo DFA porque el DFA ya es minimo"<<endl;
	else
	{
		cout<<"Construyendo archivo dfa..."<<endl;
		int id = 0;
		*file << P.size()<<endl;
		*file << S_ <<endl;
		for(set<set<state*> >::iterator i = P.begin(); i!= P.end(); i++)
		{
			qset = *i;
			aux = *qset.begin();
			*file<< id <<" "<<accept_subset(qset)<<" "<<nt_<<" ";
			for(set<char>::iterator j = E_.begin(); j!= E_.end(); j++)
			{
				*file<<*j<<" ";
				*file<<D_.get_sub_id(*D_.get_transition(*aux, *j), P)<< " ";
			}
			*file<<endl;
			id++;
		}
		cout<<"Cargando nuevo archivo..."<<endl;
		file_->close();
	}
}

/**
@brief Obtiene si en un conjunto se encuentra algún estado de aceptación
@param Q set de estados
@returns Devuelve si el conjunto es de aceptación
*/
bool dfa::accept_subset(set<state*> Q)
{
	state* aux;
	for(set<state*>::iterator i = Q.begin(); i!= Q.end(); i++)
	{
		aux = *i;
		if(aux->is_accept())
			return true;
	}
	return false;
}

/**
@brief Imprime un set de estados
@param Q Set de estados
*/
void dfa::print_set(set<state*> Q)
{
	state* aux;
	for(set<state*>::iterator i = Q.begin(); i!= Q.end(); i++)
	{
		aux = *i;
		aux->print();
	}
}

/**
@brief Imprime un set que contiene sets de estados
@param Q Set de sets de estados
*/
void dfa::print_pi(set<set<state*> > P)
{
	int cnt = 0;
	for(set<set<state*> >::iterator i = P.begin(); i!= P.end(); i++)
	{
		cout<<"Subconjunto "<<cnt<<endl;
		print_set(*i);
		cnt++;
	}
}