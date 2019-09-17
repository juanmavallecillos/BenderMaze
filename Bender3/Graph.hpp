#pragma once

#include "Llista_graph.hpp"
#include "InfoGraph.hpp"
#include "Parell.hpp"
#include "BTree.hpp"

template <class T1, class T2>
class Graph
{
public:
	Graph();
	~Graph();
	void InsertVectorNodesArestes(T1 n[], Parell<int> ap[],T2 a[],int numNod, int numArestes);
    void insertAresta(T2 valor,Node<InfoNodeGraph<T1,T2>>*n1,Node<InfoNodeGraph<T1,T2>>* n2, Node<InfoArestaGraph<T1, T2>>* pArestaN1, Node<InfoArestaGraph<T1, T2>>* pArestaN2);
    Node<InfoNodeGraph<T1,T2>>* insertNode(T1 dada);
	void print();
	int getNumNodes() { return m_numNodes; }
    int getNumArestes() { return m_numArestes; }
	Node<InfoNodeGraph<T1, T2>>* search(T1 val);

private:
	Llista<InfoNodeGraph<T1,T2>> m_nodes;
	int m_numNodes;
	int m_numArestes;
	T2 m_valorArestaInfinit;
	void setIndexNoVisitat(/*Node<InfoNodeGraph<T1, T2>>* vConexio[]*/);
	void setNoVisitat();
};

template <class T1, class T2>
Graph<T1,T2>::Graph()
{
	m_numNodes=0;
	m_numArestes=0;
}

template <class T1, class T2>
Graph<T1,T2>::~Graph()
{
	
}

template <class T1, class T2>
void Graph<T1,T2>::InsertVectorNodesArestes(T1 n[], Parell<int> ap[],T2 a[], int numNods, int numArestes)
{
	//Creem node nou del graf
	Node<InfoNodeGraph<T1,T2>>** pNode= new Node<InfoNodeGraph<T1,T2>>*[numNods];
	//Inserim ordenadament tots els nodes a m_nodes guardant els seus a pauntadors a vector pNode per fer arestes
	pNode[0] = m_nodes.insereixNext(n[0], NULL);
	for (int i = 1; i < numNods; i++)
	{
		pNode[i]=m_nodes.insereixNext(n[i], pNode[i-1]);
	}
	//Inserim ordenadament totes les arestes
	for (int j = 0; j < numArestes; j++)
	{
		//Inserim aresta de Node1 a Node2
		InfoArestaGraph<T1, T2> infoAre(a[j], pNode[ap[j].getP2()]);
		pNode[ap[j].getP1()]->getValor().insertNextAdjacent(infoAre, pNode[ap[j].getP1()]->getValor().getLastAdjacent());
		//Inserim aresta de Node2 a Node1, valor es igual i vei canvia
		infoAre.setNodeAdjacent(pNode[ap[j].getP1()]);
		pNode[ap[j].getP2()]->getValor().insertNextAdjacent(infoAre, pNode[ap[j].getP2()]->getValor().getLastAdjacent());
	}
	m_numNodes = numNods;
	m_numArestes = numArestes;
	delete [] pNode;
}

template <class T1, class T2>
Node<InfoNodeGraph<T1,T2>>* Graph<T1,T2>::insertNode(T1 dada)
{
	Node<InfoNodeGraph<T1,T2>>* pNodeAct;
	pNodeAct = m_nodes.insereixNext(dada, NULL);
	m_numNodes++;
	return pNodeAct;
}

template <class T1, class T2>
void Graph<T1, T2>::insertAresta(T2 valor, Node<InfoNodeGraph<T1, T2>>* n1,   Node<InfoNodeGraph<T1, T2>>* n2, Node<InfoArestaGraph<T1, T2>>* pArestaN1, Node<InfoArestaGraph<T1, T2>>* pArestaN2)
{
    pArestaN1 = n1->getValor().insertNewAdjacent(valor, n2);
    pArestaN2 = n2->getValor().insertNewAdjacent(valor, n1);
    m_numArestes++;
}

template <class T1, class T2>
void Graph<T1, T2>::setIndexNoVisitat()
{
	Node<InfoNodeGraph<T1, T2>>* pNodeAct = m_nodes.getInici();
	for (int i = 0; i < m_numNodes; i++)
	{
		pNodeAct->getValor().setPosicio(i);
		pNodeAct->getValor().setEstat(NoVisitat);
		//	vConexio[i] = pNodeAct;
		pNodeAct = pNodeAct->getNext();
	}
}
template <class T1, class T2>
void Graph<T1, T2>::setNoVisitat()
{
	Node<InfoNodeGraph<T1, T2>>* pNodeAct = m_nodes.getInici();
	for (int i = 0; i < m_numNodes; i++)
	{
		pNodeAct->getValor().setEstat(NoVisitat);
		pNodeAct = pNodeAct->getNext();
	}
}

template <class T1, class T2>
void Graph<T1, T2>::print()
{
	Node<InfoNodeGraph<T1, T2>>* pNodeAct = m_nodes.getInici();
	int i = 0;
	while (pNodeAct != NULL)
	{
		cout << "Node: " << i << " ; ";
		pNodeAct->getValor().print();
		cout << endl;
		pNodeAct = pNodeAct->getNext();
		i++;
	}
}

template <class T1, class T2>
Node<InfoNodeGraph<T1, T2>>* Graph<T1, T2>::search(T1 val)
{
	Node<InfoNodeGraph<T1, T2>>* pNodeAct = m_nodes.getInici();
	bool trobat = false;

	while ((pNodeAct != NULL) && !trobat)
	{
		if (pNodeAct->getValor().getValor() == val)
		{
			trobat = true;
		}
		else
		{
			pNodeAct = pNodeAct->getNext();
		}
	}
	return pNodeAct;
}
