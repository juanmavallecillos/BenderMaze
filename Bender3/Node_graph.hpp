#pragma once
#include <iostream> // biblioteca que contiene las funciones de entrada y salida de c++ . Viene Input/Output Stream
#include <cstdlib>
#include "Punt.h"
using namespace std;

template <class TDada>
class Node
{
public:
	Node() : m_valor(TDada()), m_next(NULL) {};
	~Node() { m_next = NULL; };
	Node(const TDada& valor) : m_valor(valor), m_next(NULL) {};
	Node(const Node<TDada>& n) { (*this) = n; }
	Node<TDada>* getNext() { return m_next; };
	void setNext(Node<TDada>* next) { m_next = next; }
	TDada& getValor() { return m_valor; }
	void setValor(const TDada& valor) { m_valor = valor; }
	Node<TDada>* getNode() { return this; };
	Node<TDada>& operator=(const Node<TDada>& n) { m_valor = n.m_valor; m_next = n.m_next; }
	friend std::ostream& operator<<(std::ostream& out, const Node<TDada>& nod)
	{
		out << nod.m_valor << endl;
		return out;
	}
private:
	TDada m_valor;
	Node<TDada>* m_next;
};