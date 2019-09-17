#pragma once

#include "Node_graph.hpp"
template <class T1, class T2>
class InfoArestaGraph;

enum EstatNode { Visitat, Processat, NoVisitat };

template <class T1, class T2>
class InfoNodeGraph
{
public:
	InfoNodeGraph() : m_valor(T1()), m_adjacents(), m_posicio(-1), m_estat(NoVisitat) {};
	~InfoNodeGraph();
	InfoNodeGraph(const T1& valor) : m_valor(valor), m_adjacents(), m_posicio(-1), m_estat(NoVisitat){};
	InfoNodeGraph(const InfoNodeGraph<T1,T2>& valor) {(*this) = valor;};
	Node<InfoArestaGraph<T1,T2>>* getFirstAdjacent() { return m_adjacents.getInici(); };
	Node<InfoArestaGraph<T1, T2>>* getLastAdjacent() { return m_adjacents.getFi(); };
	Node<InfoArestaGraph<T1, T2>>* insertNextAdjacent(InfoArestaGraph<T1,T2>& vAresta, 
		                                              Node<InfoArestaGraph<T1, T2>>* pNext) 
	                               { return m_adjacents.insereixNext(vAresta, pNext); };
    
    Node<InfoArestaGraph<T1, T2>>* insertNewAdjacent(T2 valor, Node<InfoNodeGraph<T1, T2>>* pNodeVei)
    {
        InfoArestaGraph<T1, T2> vAresta=InfoArestaGraph<T1,T2>(valor,pNodeVei);
        return m_adjacents.insereixNext(vAresta, m_adjacents.getFi());
    };

	T1& getValor() { return m_valor; }
	void setValor(const T1& valor) { m_valor = valor; }
	EstatNode getEstat() { return m_estat; }
	void setEstat(EstatNode est) { m_estat = est; }
	int getPosicio() { return m_posicio; }
	void setPosicio(int pos) { m_posicio = pos; }
	InfoNodeGraph<T1,T2>& operator=(const InfoNodeGraph<T1,T2>& valor);
	friend std::ostream& operator<<(std::ostream& out, const InfoNodeGraph<T1,T2>& nod);
	void print();
private:
	T1 m_valor;
	int m_posicio;
	EstatNode m_estat;
	Llista<InfoArestaGraph<T1,T2>> m_adjacents;	
};

template <class T1,class T2>
InfoNodeGraph<T1,T2>::~InfoNodeGraph()
{
	//posar a NULL tots els components per tal que no els elimini
	Node< InfoArestaGraph<T1,T2>>* pArestaAct = m_adjacents.getInici();
	
	while (pArestaAct != NULL)
	{
		pArestaAct->getValor().setNodeAdjacent(NULL);
		Node<InfoArestaGraph<T1,T2>>* pArestaAux = pArestaAct;
		pArestaAct = pArestaAct->getNext();
	}

}

template <class T1, class T2>
InfoNodeGraph<T1,T2>& InfoNodeGraph<T1,T2>::operator=(const InfoNodeGraph<T1,T2>& valor) {
	
	m_valor = valor.m_valor; 
	m_posicio = valor.m_posicio;
	m_estat = valor.m_estat;

	if (!m_adjacents.esBuida())
	{
		Node<InfoArestaGraph<T1,T2>>* pArestaAct = m_adjacents.getInici();

		while (pArestaAct != NULL)
		{
			pArestaAct->getValor().setNodeAdjacent(NULL);
			Node< InfoArestaGraph<T1,T2>>* pArestaAux = pArestaAct;
			pArestaAct = pArestaAct->getNext();
			delete pArestaAux;
		}
	}

	if (!valor.m_adjacents.esBuida())
	{
		Node<InfoArestaGraph<T1,T2>>* pArestaAct = m_adjacents.getInici();
		Node<InfoArestaGraph<T1,T2>>* pArestaUlt = NULL;
		while (pArestaAct != NULL)
		{
			pArestaUlt = m_adjacents.insereixNext(pArestaAct->getValor(), pArestaUlt);
			pArestaAct = pArestaAct->getNext();
		}
	}
	return (*this);
}

template <class T1, class T2 >
void InfoNodeGraph<T1,T2>::print()
{
	cout << "Valor: " << m_valor << " ; ";
	cout << "Veins: ";
	if (!m_adjacents.esBuida())
	{
		Node< InfoArestaGraph<T1,T2>>* pArestaAct = m_adjacents.getInici();

		while (pArestaAct != NULL)
		{
			pArestaAct->getValor().print();
			pArestaAct = pArestaAct->getNext();
		}
	}
}

template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const InfoNodeGraph<T1,T2>& nod)
{
	out << "Valor: " << nod.m_valor << " ; ";
	out << "Veins: ";
	if (!nod.m_adjacents.esBuida())
	{
		Node<InfoArestaGraph<T1,T2>>* pArestaAct = nod.m_adjacents.getInici();

		while (pArestaAct != NULL)
		{
			out << pArestaAct->getValor();
			pArestaAct = pArestaAct->getNext();
		}
	}
	return out;
}


//////////////////////////////////////////////////////////////////
// Informacio que guardem a les arestes
//////////////////////////////////////////////////////////////////

template <class T1, class T2>
class InfoArestaGraph
{
public:
	InfoArestaGraph() : m_valor(T2()), m_nodeAdjacent(NULL){};
	~InfoArestaGraph();
	InfoArestaGraph(const T2& valor, Node<InfoNodeGraph<T1, T2>>* nodAdjacent) : m_valor(valor), m_nodeAdjacent(nodAdjacent) {};
	InfoArestaGraph(const InfoArestaGraph<T1,T2>& areG) { (*this) = areG; };
	Node<InfoNodeGraph<T1,T2>>* getAdjacent() { return m_nodeAdjacent; };
	T2& getValor() { return m_valor; }
	void setValor(const T2& valor) { m_valor = valor; }
	void setNodeAdjacent(Node<InfoNodeGraph<T1,T2>>* pAdjacent) { m_nodeAdjacent = pAdjacent; }
	InfoArestaGraph<T1,T2>& operator=(const InfoArestaGraph<T1,T2>& valor);
	friend std::ostream& operator<<(std::ostream& out, const InfoArestaGraph<T1,T2>& are);
	void print();
private:
	T2 m_valor;
	Node<InfoNodeGraph<T1,T2>>* m_nodeAdjacent;
};

template <class T1, class T2>
InfoArestaGraph<T1,T2>::~InfoArestaGraph()
{
	m_nodeAdjacent = NULL;
}

template <class T1, class T2>
InfoArestaGraph<T1,T2>& InfoArestaGraph<T1,T2>::operator=(const InfoArestaGraph<T1,T2>& valor) {

	m_valor = valor.m_valor;

	m_nodeAdjacent = valor.m_nodeAdjacent;
	return (*this);
}

template <class T1, class T2 >
void InfoArestaGraph<T1, T2>::print()
{
	if (m_nodeAdjacent != NULL)
	{
		cout << m_nodeAdjacent->getValor().getValor() <<" [ " ;
	}
	else
	{
		cout << "NULL [ ";
	}
	cout << m_valor << " ] ; " ;
}

template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const InfoArestaGraph<T1, T2>& are)
{
	
	if (are.m_nodeAdjacent != NULL)
	{
		out << are.m_nodeAdjacent->getValor().getValor() <<" [ " ;
	}
	else
	{
		out << "NULL [ " ;
	}
	out << are.m_valor << " ] ; ";
	return out;
}
