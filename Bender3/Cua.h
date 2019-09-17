#pragma once
#include "Contenidor.h"

template <class C>
class Cua : public Contenidor<C>
{
public:
	Cua();
	~Cua();
	void afegeix(C& valor);
	void treu();
	C &getPrimer() const;
	C &getUltim() const;
	bool esBuida() const;
private:
	Node<C>* m_ultim;
};

template <class C>
Cua<C>::Cua()
{
	m_ultim = NULL;
}

template <class C>
Cua<C>::~Cua()
{
	while (!esBuida())
		treu();
}

template <class C>
bool Cua<C>::esBuida() const
{
	return this->m_primer == NULL;
}

template <class C>
C &Cua<C>::getPrimer() const
{
	return this->m_primer->getValor();
}

template <class C>
C &Cua<C>::getUltim() const
{
	return this->m_ultim->getValor();
}

template <class C>
void Cua<C>::afegeix(C &valor)
{
	if (esBuida())
	{
		this->insereixNext(valor, NULL);
		m_ultim = this->m_primer;
	}
	else
	{
		m_ultim = this->insereixNext(valor, m_ultim);
	}
}

template <class C>
void Cua<C>::treu()
{
	this->eliminaNext(NULL);
}