#pragma once
#include "Tree.hpp"

template <class T>
class Iterator
{
public:
	Iterator() { m_pTree = NULL; }
	Iterator(Tree<T>* pTree) { m_pTree = pTree; }
	~Iterator() {}
	T& getData(){ return m_pTree->getData(); }
	Tree<T>*  getTree(){ return m_pTree; }
	bool end() const { return (m_pTree == NULL); }
protected:
	Tree<T>* m_pTree;
};


///////////////////////////////////////////////////////////////
// INORDER
///////////////////////////////////////////////////////////////
template <class T>
class IteratorInOrder : public Iterator<T>
{
public:
	IteratorInOrder() {}
	IteratorInOrder(Tree<T>* pTree) : Iterator<T>::Iterator(pTree) { }
	~IteratorInOrder() {}
	//prefixe ++it
	IteratorInOrder<T>& operator++();
	//postfixe it++
	IteratorInOrder<T> operator++(int);
	void begin(Tree<T>* t);
};

//operator ++ prefixe
template <class T>
IteratorInOrder<T>& IteratorInOrder<T>::operator++()
{
	//if m_pTree ==NULL can not increment more.
	if (Iterator<T>::m_pTree != NULL)
	{//We explore right son of the tree
		if (Iterator<T>::m_pTree->m_right != NULL)
		{
			IteratorInOrder<T> it;
			it.begin((Iterator<T>::m_pTree->m_right));
			Iterator<T>::m_pTree = it.m_pTree;
		}
		else
		{//The tree is explored and we go back to parent
			Tree<T>* parent;
			parent = Iterator<T>::m_pTree->m_father;
			if (parent != NULL)
			{
				//It can be left son then we explore parent
				if (Iterator<T>::m_pTree == parent->m_left)
				{
					Iterator<T>::m_pTree = parent;
				}
				else
				{//It can be right son the we go up to father's father till it is the right son or till the end
					bool fillDret = true;
					while ((fillDret) && (parent !=NULL))
					{
						fillDret = (Iterator<T>::m_pTree == parent->m_right);
						Iterator<T>::m_pTree = parent;
						parent = parent->m_father;						
					}
					if ((parent==NULL) && (fillDret))
					{ //if we arrive to root and it was its right son we have finished then m_pTree is NULL
						Iterator<T>::m_pTree = parent;
					}//if we end while because it was not its right son but the left one then m_pTree is its parent so it is OK
				}				
			}
			else
			{
				Iterator<T>::m_pTree = parent;
			}
		}
	}
	return *this;
}

//operator ++ postfixe
//Return value before increment
template <class T>
IteratorInOrder<T> IteratorInOrder<T>::operator++(int)
{
	IteratorInOrder<T> iPost;
	iPost = *this;

	//Go to next node in postordre
	++(*this);

	return iPost;
}

template <class T>
void IteratorInOrder<T>::begin(Tree<T>* t)
{//Primer node arbre segons recorregut inordre: fill de mes a esquerra del fill de mes a esquerra de l'arbre.
	Iterator<T>::m_pTree = t;
	if (!(t==NULL))
	{
		if (t->m_left != NULL)
		{
			Iterator<T>::m_pTree = t->m_left;
			while (Iterator<T>::m_pTree->m_left != NULL)
			{
				Iterator<T>::m_pTree = Iterator<T>::m_pTree->m_left;
			}
		}
	}
}

///////////////////////////////////////////////////////////////
// PREORDER
///////////////////////////////////////////////////////////////
template <class T>
class IteratorPreOrder : public Iterator<T>
{
public:
	IteratorPreOrder() {}
	IteratorPreOrder(Tree<T>* pTree) :Iterator<T>::Iterator(pTree) { }
	~IteratorPreOrder() {}
	//prefixe ++it
	IteratorPreOrder<T>& operator++();
	//postfixe it++
	IteratorPreOrder<T> operator++(int);
	void begin(Tree<T>* t);
};

//operator ++ prefixe
template <class T>
IteratorPreOrder<T>& IteratorPreOrder<T>::operator++()
{
	//if m_pTree ==NULL can not increment more.
	if (Iterator<T>::m_pTree != NULL)
	{
		if (Iterator<T>::m_pTree->m_left == NULL)
		{//if there is not a left son lets see right one
			if (Iterator<T>::m_pTree->m_right== NULL)
			{//if there is not a left son neither a right one we go up to our brother or the first brother of our ancients
				Tree<T>* parent;
				parent = Iterator<T>::m_pTree->m_father;
				bool fillDret = true;
				while ((fillDret) && (parent != NULL))
				{
					fillDret = (Iterator<T>::m_pTree == parent->m_right);
					Iterator<T>::m_pTree = parent;
					parent = parent->m_father;
				}
				if ((parent == NULL) && (fillDret))
				{ //if we arrive to root and it was its right son we have finished then m_pTree is NULL
					Iterator<T>::m_pTree = parent;
				}
				else
				{//if we end while because it was not its right son but the left one then m_pTree must be its brother
					Iterator<T>::m_pTree = Iterator<T>::m_pTree->m_right;
				}
			}
			else
			{//if there is a right son and not a left one this rightson is our next element
				Iterator<T>::m_pTree = Iterator<T>::m_pTree->m_right;
			}
		}
		else
		{//if there is a leftson it is our next element
			Iterator<T>::m_pTree = Iterator<T>::m_pTree->m_left;
		}
	}
	return *this;
}

//operator ++ postfixe
//Return value before increment
template <class T>
IteratorPreOrder<T> IteratorPreOrder<T>::operator++(int)
{
	IteratorPreOrder<T> iPost;
	iPost = *this;

	//Go to next node in postordre
	++(*this);

	return iPost;
}

template <class T>
void IteratorPreOrder<T>::begin(Tree<T>* t)
{//Ens posicionem al primer node de l'arbre segons recorregut preordre: arrel.
	if (t != NULL)
		if (!t->isEmpty())
			Iterator<T>::m_pTree = t;
}