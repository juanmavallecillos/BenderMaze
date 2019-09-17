#pragma once
#include <fstream>
#include <iostream>

using namespace std;

template <class T>
class BTree {
public:
	BTree();
	BTree(const BTree<T>& t);
	BTree(const T& data);
	virtual ~BTree();
	
	virtual BTree<T>* newTree(T* pdata);
	virtual BTree<T>& operator=(const BTree<T>& t);
	virtual BTree<T>* insertSon(T& el);
	virtual void read(string nomFitxer);
	void print();
		
	bool isLeave() const { return ((m_left == NULL) && (m_right == NULL)); }
	bool isEmpty() const { return (m_data == NULL); }
	
	virtual BTree<T>* getRight() { return m_right; }
	virtual BTree<T>* getLeft() { return m_left; }
	virtual BTree<T>* getFather(){return m_father;}
	virtual T& getData() { return (*m_data); }

	void setData(T& d) { if (m_data == NULL) m_data = new(T); (*m_data) = d; }
	void setFather(BTree<T>* f) { m_father = f; }
	
	bool isLeftSon() { return (m_father->m_left == this); }
	bool isRightSon(){ return (m_father->m_right == this); }
	
	void eliminaLeft() { if (m_left != NULL) delete m_left; m_left = NULL; }
	void eliminaRight() { if (m_right != NULL) delete m_right; m_right = NULL; }
	
	void setValLeft(T& val) { if (m_left == NULL) { m_left = newTree(val); } else { m_left->setData(val); } }
	void setValRight(T& val) { if (m_right == NULL) { m_right = newTree(val); } else { m_right->setData(val); } }
	virtual void setLeft(BTree<T>* tleft) { m_left = tleft; m_left->m_father = this; }
	virtual void setRight(BTree<T>* tright) { m_right = tright; m_right->m_father = this; }


protected:
	BTree<T>* m_left;
	BTree<T>* m_right;
	BTree<T>* m_father;
	T* m_data;
	
	virtual void readTreeRec(ifstream& fitxerNodes, int h, BTree<T>* father);
	virtual void readInfoNode(ifstream& fitxerNodes);
	void printArbreRec(int n);
	virtual void printInfoNode();
};

template<class T>
BTree<T>* BTree<T>::newTree(T* pdata)
{
	BTree<T>* pT=new BTree<T>;
	if (pdata != NULL)
	{
		pT->m_data = new(T);
		(*pT->m_data) = (*pdata);
	}
	return pT;
} 

template <class T>
BTree<T>* BTree<T>::insertSon(T& el)
{
	//Afegim al fill esquerre si no te i si te al fill dret.
	//si te als dos retornem NULL i no afegim
	BTree<T>* pNodeAct = NULL;
	if (m_left == NULL)
	{
		pNodeAct = newTree(&el);
		m_left = pNodeAct;
		pNodeAct->m_father = this;
	}
	else 
	if (m_right == NULL)
	{
		pNodeAct = newTree(&el);
		m_right = pNodeAct;
		pNodeAct->m_father = this;
	}

	return pNodeAct;
}


template<class T>
BTree<T>& BTree<T>::operator=(const BTree<T>& t)
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
BTree<T>::BTree()
{//Inicialitzem tota l'estructura
	m_left = NULL;
	m_right = NULL;
	m_father = NULL;
	m_data = NULL;
}

template<class T>
BTree<T>::BTree(const T& data)
{//Inicialitzem tota l'estructura
	m_left = NULL;
	m_right = NULL;
	m_father = NULL;
	m_data = new(T);
	(*m_data) = data;
}

template<class T>
BTree<T>::BTree(const BTree<T>& t)
{
	(*this) = t;
}

template<class T>
BTree<T>::~BTree()
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
void BTree<T>::readInfoNode(ifstream& fitxerNodes)
{
	fitxerNodes >> (*m_data);
}
template<class T>
void BTree<T>::readTreeRec(ifstream& fitxerNodes, int h, BTree<T>* father)
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
void BTree<T>::read(string nomFitxer)
{
	ifstream fitxerNodes;

	fitxerNodes.open(nomFitxer.c_str());
	if (fitxerNodes.is_open())
	{
		//Llegim alçada arbre binari
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
void BTree<T>::printInfoNode()
{
	cout << (*m_data);
}

template<class T>
void BTree<T>::printArbreRec(int n)
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
					cout << "ERROR FATHER-LEFTSON" <<endl;
				}
				m_left->printArbreRec(n + 1);
			}
			else
			{
				for (int i = 0; i < n+1; i++)
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
void BTree<T>::print()
{
	printArbreRec(0);
}


