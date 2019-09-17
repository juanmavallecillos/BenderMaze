#pragma once
#include <fstream>
#include <iostream>

using namespace std;

template<class T>
class IteratorPreOrder;
template<class T>
class IteratorPostOrder;
template<class T>
class IteratorInOrder;
template<class T>
class Iterator;


template <class T>
class Tree {
public:
	Tree();
	Tree(const Tree<T>& t);
	virtual ~Tree();

	virtual Tree<T>* newTree(T* pdata);
	virtual Tree<T>& operator=(const Tree<T>& t);

	virtual void read(string nomFitxer);
	void print();

	bool isLeave() const { return ((m_left == NULL) && (m_right == NULL)); }
	bool isEmpty() const { return (m_data == NULL); }

	virtual Tree<T>* getRight() { return m_right; }
	virtual Tree<T>* getLeft() { return m_left; }
	virtual Tree<T>* getFather() { return m_father; }
	virtual T& getData() { return (*m_data); }

	void setData(T& d) { if (m_data == NULL) m_data = new(T); (*m_data) = d; }
	void setFather(Tree<T>* f) { m_father = f; }

	bool isLeftSon() { return (m_father->m_left == this); }
	bool isRightSon() { return (m_father->m_right == this); }

	void eliminaLeft() { if (m_left != NULL) delete m_left; m_left = NULL; }
	void eliminaRight() { if (m_right != NULL) delete m_right; m_right = NULL; }

	void inorder();
	void preorder();
	void preorderWrite(ofstream& fileOut, int h);

	friend Iterator<T>;
	friend IteratorPostOrder<T>;
	friend IteratorPreOrder<T>;
	friend IteratorInOrder<T>;

	void setValLeft(T& val) { if (m_left == NULL) { m_left = newTree(val); } else { m_left->setData(val); } }
	void setValRight(T& val) { if (m_right == NULL) { m_right = newTree(val); } else { m_right->setData(val); } }
	virtual void setLeft(Tree<T>* tleft) { m_left = tleft; m_left->m_father = this; }
	virtual void setRight(Tree<T>* tright) { m_right = tright; m_right->m_father = this; }


protected:
	Tree<T>* m_left;
	Tree<T>* m_right;
	Tree<T>* m_father;
	T* m_data;

	virtual void readTreeRec(ifstream& fitxerNodes, int h, Tree<T>* father);
	virtual void readInfoNode(ifstream& fitxerNodes);
	void printArbreRec(int n);
	virtual void printInfoNode();
};

template<class T>
Tree<T>* Tree<T>::newTree(T* pdata)
{
	Tree<T>* pT = new Tree<T>;
	if (pdata != NULL)
	{
		pT->m_data = new(T);
		(*pT->m_data) = (*pdata);
	}
	return pT;
}


template<class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& t)
{
	if (this != &t)
	{
		if (m_left != NULL)
		{
			delete m_left;
		}

		if (t.m_left != NULL)
		{
			m_left = newTree(NULL);
			(*m_left) = (*t.m_left);
			m_left->m_father = this;
		}
		else
		{
			m_left = NULL;
		}

		if (m_right != NULL)
		{
			delete m_right;
		}

		if (t.m_right != NULL)
		{
			m_right = newTree(NULL);
			(*m_right) = (*t.m_right);
			m_right->m_father = this;
		}
		else
		{
			m_right = NULL;
		}

		if (m_data != NULL)
		{
			delete m_data;
		}

		if (t.m_data != NULL)
		{
			m_data = new(T);
			(*m_data) = (*t.m_data);
		}
		else
		{
			m_data = NULL;
		}

		m_father = NULL;
	}
	return (*this);
}

template<class T>
Tree<T>::Tree()
{//Inicialitzem tota l'estructura
	m_left = NULL;
	m_right = NULL;
	m_father = NULL;
	m_data = NULL;
}

template<class T>
Tree<T>::Tree(const Tree<T>& t)
{
	(*this) = t;
}

template<class T>
Tree<T>::~Tree()
{
	if (m_right != NULL)
	{
		delete m_right;
		m_right = NULL;
	}

	if (m_left != NULL)
	{
		delete m_left;
		m_left = NULL;
	}

	if (m_data != NULL)
	{
		delete m_data;
		m_data = NULL;
	}

	m_father = NULL;
}

//Example of inorder path
template<class T>
void Tree<T>::inorder()
{
	if (m_data != NULL)
	{
		if (m_left != NULL)
			m_left->inorder();
		std::cout << (*m_data) << std::endl;
		if (m_right != NULL)
			m_right->inorder();
	}
}


/////////////////////////////////////////////////////////////////////////////
// read(nomFitxer):                                                        //
//                 Metode public que obre fitxer i crida a metode privat   //
// readTreeRec(ifstream& fitxerNodes, int h, Tree<T>* father)              //
//            metode privat que llegeix arbre de forma recursiva           //
//Lectura d'un fitxer a on tindrem                                         //
//alcada                                                                   //
//estat: 0 o 1 segons sigui buit o amb informacio al costat dada           //
//Esta en inordre Imnordre(FillEsq) Arrel Inordre(FillDret)                //
/////////////////////////////////////////////////////////////////////////////
template<class T>
void Tree<T>::readInfoNode(ifstream& fitxerNodes)
{
	fitxerNodes >> (*m_data);
}

template<class T>
void Tree<T>::readTreeRec(ifstream& fitxerNodes, int h, Tree<T>* father)
{
	if (fitxerNodes.is_open())
	{
		m_father = father;
		if (!fitxerNodes.eof())
		{
			m_data = new(T);
			this->readInfoNode(fitxerNodes);
			if (h > 0)
			{
				if (!fitxerNodes.eof())
				{
					int estat;
					fitxerNodes >> estat;
					if (estat == 1)
					{
						m_left = newTree(NULL);
						m_left->readTreeRec(fitxerNodes, h - 1, this);
					}
				}
				if (!fitxerNodes.eof())
				{
					int estat;
					fitxerNodes >> estat;
					if (estat == 1)
					{
						m_right = newTree(NULL);
						m_right->readTreeRec(fitxerNodes, h - 1, this);
					}
				}
			}
		}
	}
}

template<class T>
void Tree<T>::read(string nomFitxer)
{
	ifstream fitxerNodes;

	fitxerNodes.open(nomFitxer.c_str());
	if (fitxerNodes.is_open())
	{
		//Llegim al�ada arbre binari
		int h;
		fitxerNodes >> h;
		if (!fitxerNodes.eof())
		{
			int estat;
			fitxerNodes >> estat;
			if (estat == 1)
			{
				if ((m_data != NULL) || (m_left != NULL) || (m_right != NULL))
				{
					delete this;
				}
				readTreeRec(fitxerNodes, h, NULL);
			}
		}
		fitxerNodes.close();
	}
}

/////////////////////////////////////////////////////////////////////////////
// print():                                                                //
//         Metode public presenta arbre per pantalla                       //
// readArbreRec(int n)                                                     //
//         Metode privat que escriu arbre per pantalla de forma recursiva  //
// |--arrel                                                                //
// |---->FillDret1                                                         //
// |------>FillDret2                                                       //
// |------>FillEsquerre2                                                   //
// |---->FillEsquerre1                                                     //
//alcada                                                                   //
//estat: 0 o 1 segons sigui buit o amb informacio al costat dada           //
//Esta en inordre Imnordre(FillEsq) Arrel Inordre(FillDret)                //
/////////////////////////////////////////////////////////////////////////////
template<class T>
void Tree<T>::printInfoNode()
{
	cout << (*m_data);
}

template<class T>
void Tree<T>::printArbreRec(int n)
{
	if (isEmpty())
	{//Pintem arbre buit
		for (int i = 0; i < n; i++)
		{
			cout << "|--";
		}
		cout << "-->BUIT" << endl;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			cout << "|--";
		}
		cout << "|-->";
		this->printInfoNode();
		cout << endl;

		if (!isLeave())
		{
			if (m_left != NULL)
			{
				if (this != m_left->m_father)
				{
					cout << "ERROR FATHER-LEFTSON" << endl;
				}
				m_left->printArbreRec(n + 1);
			}
			else
			{
				for (int i = 0; i < n + 1; i++)
				{
					cout << "|--";
				}
				cout << "|-->BUIT" << endl;
			}
			if (m_right != NULL)
			{
				if (this != m_right->m_father)
				{
					cout << "ERROR FATHER-RIGHTSON" << endl;
				}
				m_right->printArbreRec(n + 1);
			}
			else
			{
				for (int i = 0; i < n + 1; i++)
				{
					cout << "|--";
				}
				cout << "|-->BUIT" << endl;
			}
		}
	}
}

template<class T>
void Tree<T>::print()
{
	printArbreRec(0);
}

template<class T>
void Tree<T>::preorder()
{
	if (m_data != NULL)
	{
		cout << (*m_data) << endl;
		if (m_left != NULL)
			m_left->preorder();
		if (m_right != NULL)
			m_right->preorder();
	}
}

template<class T>
void Tree<T>::preorderWrite(ofstream& fileOut, int h)
{
	if (m_data != NULL)
	{
		h--;
		fileOut << "1 " << (*m_data);
		if (m_left != NULL)
		{
			m_left->preorderWrite(fileOut, h);
		}
		else
		{
			if (h != 0)
			{
				fileOut << "0" << endl;
			}
		}
		if (m_right != NULL)
		{
			m_right->preorderWrite(fileOut, h);
		}
		else
		{
			if (h != 0)
			{
				fileOut << "0" << endl;
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////
//                                                                                 //
//                                                                                 //
//                         BBTree                                                  //
//                    ARBRE BINARI DE CERCA                                        //
//                                                                                 //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BBTree : public Tree<T>
{
public:
	BBTree() { m_numNodes = 1; }
	BBTree(const BBTree<T>& t);

	BBTree<T>* getRight() { return dynamic_cast<BBTree<T>*> (this->m_right); }
	BBTree<T>* getLeft() { return dynamic_cast<BBTree<T>*> (this->m_left); }
	BBTree<T>* getFather() { return dynamic_cast<BBTree<T>*> (this->m_father); }
	T& getData() { return (*(this->m_data)); }

	BBTree<T>* newTree(T* pdata);
	BBTree<T>& operator=(const BBTree<T>& t);

	~BBTree() {}

	void setRight(BBTree<T>* nouRight) { dynamic_cast<BBTree<T>*> (this->m_right) = nouRight; }
	void setLeft(BBTree<T>* nouLeft) { dynamic_cast<BBTree<T>*> (this->m_left) = nouLeft; }

	BBTree<T>* minim();
	BBTree<T>* maxim();
	virtual BBTree<T>* cerca(T& val);
	virtual BBTree<T>* insert(T& el);
	virtual BBTree<T>* esborra(T& el, bool& esbborrat);
	void calculaNumNodes();
	int level(BBTree<T>* tNode);

protected:
	int m_numNodes;

	void eliminaFulla(BBTree<T>* pAct);
	void eliminaNode1Fill(int op, BBTree<T>* pAct);
	void eliminaNode2Fill(BBTree<T>* pAct);
	void incNumNodesAncestres();
	void decNumNodesAncestres();
	void printInfoNode();

};


template <class T>
BBTree<T>::BBTree(const BBTree<T>& t)
{
	(*this) = t;
}

template<class T>
BBTree<T>* BBTree<T>::newTree(T* pdata)
{
	BBTree<T>* pT = new BBTree<T>;
	if (pdata != NULL)
	{
		pT->m_data = new(T);
		(*pT->m_data) = (*pdata);
	}
	pT->m_numNodes = 1;
	return pT;
}


template<class T>
BBTree<T>& BBTree<T>::operator=(const BBTree<T>& t)
{
	if (this != &t)
	{
		(*this) = t;
		m_numNodes = t.m_numNodes;
		if (this->m_father != NULL)
		{
			incNumNodesAncestres();
		}
	}
	return (*this);
}

template <class T>
void BBTree<T>::calculaNumNodes()
{
	m_numNodes = 1;
	if (this->m_left != NULL)
	{
		m_numNodes = m_numNodes + dynamic_cast<BBTree<T>*> (this->m_left)->m_numNodes;
	}
	if (this->m_right != NULL)
	{
		m_numNodes = m_numNodes + dynamic_cast<BBTree<T>*> (this->m_right)->m_numNodes;
	}
}
template <class T>
BBTree<T>*  BBTree<T>::minim()
{
	if (this->m_left != NULL)
	{
		BBTree<T>* pt = dynamic_cast<BBTree<T>*> (this->m_left);

		bool trobat = false;
		while (!trobat && (pt != NULL))
		{
			if (pt->m_left == NULL)
			{
				trobat = true;
			}
			else
			{
				pt = dynamic_cast<BBTree<T>*> (pt->m_left);
			}
		}
		return (pt);
	}
	else
	{
		return this;
	}
}

template <class T>
BBTree<T>*  BBTree<T>::maxim()
{
	if (this->m_right != NULL)
	{
		BBTree<T>* pt = dynamic_cast<BBTree<T>*> (this->m_right);
		bool trobat = false;
		while (!trobat && (pt != NULL))
		{
			if (pt->m_right == NULL)
			{
				trobat = true;
			}
			else
			{
				pt = dynamic_cast<BBTree<T>*> (pt->m_right);
			}
		}
		return (pt);
	}
	else
	{
		return this;
	}
}

template <class T>
BBTree<T>* BBTree<T>::cerca(T& val)
{
	BBTree<T>* pAct = this;

	bool trobat = false;
	while ((!trobat) && (pAct != NULL))
	{
		if ((*pAct->m_data) == val)
		{
			trobat = true;
		}
		else
		{
			if (val < (*pAct->m_data))
			{
				pAct = dynamic_cast<BBTree<T>*> (pAct->m_left);
			}
			else
			{
				pAct = dynamic_cast<BBTree<T>*> (pAct->m_right);
			}
		}
	}

	return pAct;
}

template <class T>
void BBTree<T>::incNumNodesAncestres()
{
	m_numNodes++;
	if (this->m_father != NULL)
		dynamic_cast<BBTree<T>*>(this->m_father)->incNumNodesAncestres();
}

template <class T>
BBTree<T>* BBTree<T>::insert(T& el)
{
	BBTree<T>* pAct = this;
	bool inserit = false;
	bool trobat = false;
	while ((!inserit) && (!trobat) && (pAct != NULL))
	{
		if ((*pAct->m_data) == el)
		{
			pAct = NULL;
			trobat = true;
		}
		else
		{
			if (el < (*pAct->m_data))
			{
				if (pAct->m_left == NULL)
				{
					pAct->m_left = newTree(&el);
					dynamic_cast<BBTree<T>*> (pAct->m_left)->m_father = pAct;
					pAct->incNumNodesAncestres();
					pAct = dynamic_cast<BBTree<T>*> (pAct->m_left);
					inserit = true;
				}
				else
				{
					pAct = dynamic_cast<BBTree<T>*> (pAct->m_left);
				}
			}
			else
			{
				if (pAct->m_right == NULL)
				{
					pAct->m_right = newTree(&el);
					dynamic_cast<BBTree<T>*> (pAct->m_right)->m_father = pAct;
					pAct->incNumNodesAncestres();
					pAct = dynamic_cast<BBTree<T>*> (pAct->m_right);
					inserit = true;
				}
				else
				{
					pAct = dynamic_cast<BBTree<T>*> (pAct->m_right);
				}
			}
		}
	}
	return pAct;
}

template <class T>
void BBTree<T>::decNumNodesAncestres()
{
	m_numNodes--;
	if (this->m_father != NULL)
		dynamic_cast<BBTree<T>*>(this->m_father)->decNumNodesAncestres();
}

template <class T>
void BBTree<T>::eliminaFulla(BBTree<T>* pAct)
{

	if (pAct->isLeftSon())
	{
		pAct = dynamic_cast<BBTree<T>*> (pAct->m_father);
		delete(pAct->m_left);
		pAct->m_left = NULL;
		pAct->decNumNodesAncestres();
	}
	else
	{
		pAct = dynamic_cast<BBTree<T>*> (pAct->m_father);
		delete(pAct->m_right);
		pAct->m_right = NULL;
		pAct->decNumNodesAncestres();
	}
}

template <class T>
void BBTree<T>::eliminaNode1Fill(int op, BBTree<T>* pAct)
{
	if (pAct->isLeftSon())
	{
		BBTree<T>* posAux = dynamic_cast<BBTree<T>*> (pAct->m_father);
		if (op == 1)
		{//Te fill esquerre
			posAux->m_left = pAct->m_left;
			dynamic_cast<BBTree<T>*> (pAct->m_left)->m_father = posAux;
		}
		else
		{//Te fill dret
			posAux->m_left = pAct->m_right;
			dynamic_cast<BBTree<T>*> (pAct->m_right)->m_father = posAux;
		}
	}
	else
	{//El node que eliminem es el fill dret del seu pare
		BBTree<T>* posAux = dynamic_cast<BBTree<T>*> (pAct->m_father);
		if (op == 1)
		{//Te fill esquerre
			posAux->m_right = pAct->m_left;
			dynamic_cast<BBTree<T>*> (pAct->m_left)->m_father = posAux;
		}
		else
		{//Te fill dret
			posAux->m_right = pAct->m_right;
			dynamic_cast<BBTree<T>*> (pAct->m_right)->m_father = posAux;
		}
	}
	BBTree<T>* pfather = dynamic_cast<BBTree<T>*> (pAct->m_father);
	pfather->decNumNodesAncestres();
	pAct->m_right = NULL;
	pAct->m_left = NULL;
	delete pAct;
	pAct = NULL;
}

template <class T>
void BBTree<T>::eliminaNode2Fill(BBTree<T>* pAct)
{//Nomes cridem a aquest metode si te fill esq i dret
	BBTree<T>* pAux = dynamic_cast<BBTree<T>*> (pAct->m_father);
	BBTree<T>* max;
	if (pAct->m_left != NULL)
	{
		BBTree<T>* pt = dynamic_cast<BBTree<T>*> (dynamic_cast<BBTree<T>*> (pAct->m_left)->m_right);
		if (pt != NULL)
		{//Busquem el maxim del fill esquerre per substituir el valor que anavem a treure
		 //Si te fill dret es el maxim del subarbre dret
			bool trobat = false;
			while (!trobat && (pt != NULL))
			{
				if (pt->m_right == NULL)
				{
					trobat = true;
				}
				else
				{
					pt = dynamic_cast<BBTree<T>*> (pt->m_right);
				}
			}
			max = pt;
		}
		else
		{//Si no te fill dret es el mateix
			max = dynamic_cast<BBTree<T>*> (this->m_left);
		}

		(*pAct->m_data) = (*max->m_data);

		//Desconectem el node maxim de arbre i esborrem i decrementem numnodes
		dynamic_cast<BBTree<T>*>(max->m_father)->decNumNodesAncestres();
		if (max->isLeftSon())
		{
			dynamic_cast<BBTree<T>*>(max->m_father)->m_left = NULL;
		}
		else
		{
			dynamic_cast<BBTree<T>*>(max->m_father)->m_right = NULL;
		}
		delete max;
	}
}

template <class T>
BBTree<T>* BBTree<T>::esborra(T& el, bool& esborrat)
{
	BBTree<T>* pAct = this;
	BBTree<T>* pFather = NULL;
	esborrat = false;
	while ((!esborrat) && (pAct != NULL))
	{
		if ((*pAct->m_data) == el)
		{
			pFather = dynamic_cast<BBTree<T>*>(pAct->m_father);
			if (pAct->m_left == NULL)
			{
				if (pAct->m_right == NULL)
				{//Eliminem fulla
					eliminaFulla(pAct);
				}
				else
				{//Eliminem node amb fill dret
					eliminaNode1Fill(2, pAct);
				}
			}
			else
			{
				if (pAct->m_right == NULL)
				{//Eliminem node amb fill esquerre
					eliminaNode1Fill(1, pAct);
				}
				else
				{//Eliminem node amb dos fills
					eliminaNode2Fill(pAct);
				}
			}
			esborrat = true;
		}
		else
		{
			if (el < (*pAct->m_data))
			{
				pAct = dynamic_cast<BBTree<T>*> (pAct->m_left);
			}
			else
			{
				pAct = dynamic_cast<BBTree<T>*>(pAct->m_right);
			}
		}
	}
	return pFather;
}

/////////////////////////////////////////////////////////////////////////////
// printInfoNode():                                                                //
/////////////////////////////////////////////////////////////////////////////
template<class T>
void BBTree<T>::printInfoNode()
{
	cout << (*(this->m_data)) << " NNod: " << m_numNodes;
}

template<class T>
int BBTree<T>::level(BBTree<T>* tNode)
{
	int altura;
	int AltIzq, AltDer;
	if (tNode == NULL)
	{
		altura = -1;
	}
	else
	{
		AltIzq = level(tNode->getLeft());
		AltDer = level(tNode->getRight());
		if (AltIzq > AltDer)
		{
			altura = AltIzq + 1;
		}
		else
		{
			altura = AltDer + 1;
		}
	}
	return altura;
}