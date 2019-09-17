#pragma once
#include "Node_graph.hpp"

template <class C>
class Contenidor
{
public:
	Contenidor();
	~Contenidor();

	bool esBuida() const;

protected:
	Node<C> *getInici() const;
	Node<C> *insereixNext(const C& p, Node<C> *posicio);
	Node<C> *eliminaNext(Node<C> *posicio);

	Node<C> *m_primer;
};

template <class C>
Contenidor<C>::Contenidor()
{
	m_primer = NULL;
}

template <class C>
Contenidor<C>::~Contenidor()
{
}

template <class C>
bool Contenidor<C>::esBuida() const
{
	return (m_primer == NULL);
}

template <class C>
Node<C> *Contenidor<C>::getInici() const
{
	return m_primer;
}

template <class C>
Node<C> *Contenidor<C>::insereixNext(const C& p, Node<C> *posicio)
{
	Node<C>* aux = new Node<C>;
	if (aux != NULL)
	{
		aux->setValor(p);
		if (posicio == NULL)
		{
			aux->setNext(m_primer);
			m_primer = aux;
		}
		else
		{
			aux->setNext(posicio->getNext());
			posicio->setNext(aux);
		}
	}
	return aux;
}

template <class C>
Node<C> *Contenidor<C>::eliminaNext(Node<C> *posicio)
{
	Node<C>* aux;
	Node<C> *seguent = NULL;
	if (posicio == NULL)
	{
		aux = m_primer;
		m_primer = aux->getNext();
		delete aux;
		seguent = m_primer;
	}
	else
	{
		aux = posicio->getNext();
		if (aux != NULL)
		{
			posicio->setNext(aux->getNext());
			seguent = aux->getNext();
			delete aux;
		}
	}
	return seguent;
}