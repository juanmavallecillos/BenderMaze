#pragma once
 
#include "Node_graph.hpp"
#include  <iostream>
 
using namespace std;
 
template <class TDada>
class Llista
{
public:
    Llista();
    Llista(const Llista<TDada>& l);
    ~Llista();
    bool esBuida() const { return (m_primer == NULL); };
    Node<TDada>* getInici() { return m_primer; };
    Node<TDada>* getFi() { return m_ultim; };
    Node<TDada>* insereixNext(const TDada& valor, Node<TDada> *posicio);
    Node<TDada>* eliminaNext(Node<TDada> *posicio);
private:
    Node<TDada>* m_primer;
    Node<TDada>* m_ultim; 
};
 
template <class TDada>
Llista<TDada>::Llista()
{
    //ctor
    m_primer = NULL;
    m_ultim = NULL;
}
 
template <class TDada>
Llista<TDada>::Llista(const Llista<TDada>& l)
{
    Node<TDada>* pAct=l.m_primer;
    Node<TDada>* pActThis = NULL;
 
    while (pAct != NULL)
    {
        pActThis = pActinsereixNext(pAct->getValor(), pActThis);
    }
}
 
template <class TDada>
Llista<TDada>::~Llista()
{
    while (m_primer != NULL)
        eliminaNext(NULL);
    //m_nodeActual = NULL;
    m_primer = NULL;
    m_ultim = NULL;
}
 
template <class TDada>
Node<TDada>* Llista<TDada>::insereixNext(const TDada& valor, Node<TDada> *posicio)
{
    Node<TDada>* aux = new Node<TDada>();
    if (aux != NULL)
    {
        aux->setValor(valor);
        if (posicio == NULL)
        {
            aux->setNext(m_primer);
            if(m_ultim==NULL)
            { 
                m_ultim = aux;
            }
            m_primer = aux;
        }
        else
        {
            aux->setNext(posicio->getNext());
            posicio->setNext(aux);
            if (posicio == m_ultim)
            {
                m_ultim = aux;
            }
        }
    }
 
    return aux;
}
 
template <class TDada>
Node<TDada>* Llista<TDada>::eliminaNext(Node<TDada>* posicio)
{
    Node<TDada>* aux;
    Node<TDada>* seguent = NULL;
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
            if (aux == m_ultim)
            {
                m_ultim = posicio;
            }
            delete aux;
        }
    }
    return seguent;
}