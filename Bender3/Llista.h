#pragma once
#include "Contenidor.h"

template <class L>
class Llista : public Contenidor<L>
{
public:
	Llista();
	~Llista();

	Node<L> *getInici() const { return Contenidor<L>::getInici(); };
	Node<L> *insereixNext(const L& p, Node<L> *posicio) { return Contenidor<L>::insereixNext(p, posicio); };
	Node<L> *eliminaNext(Node<L> *posicio) { return Contenidor<L>::eliminaNext(posicio); };
};

template <class L>
Llista<L>::Llista()
{
	//ctor
	this->m_primer = NULL;
}

template <class L>
Llista<L>::~Llista()
{
	//dtor
	while (this->m_primer != NULL)
		eliminaNext(NULL);
}