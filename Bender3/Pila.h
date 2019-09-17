#pragma once
#include "Contenidor.h"

template <class P>
class Pila : public Contenidor<P>
{
public:
	Pila() {};
	~Pila() {};
	void push(const P& p) { this->insereixNext(p, NULL); };
	void pop() { this->eliminaNext(NULL); };
	P& top() { return this->m_primer->getValor(); };
	bool esBuida() { return(this->m_primer == NULL); };
};
