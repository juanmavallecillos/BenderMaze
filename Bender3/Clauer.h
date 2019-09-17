#pragma once
#include "Tree.hpp"
#include "Clau.h"
#include "Iterator.hpp"
class Clauer
{
public:
	Clauer() {};
	~Clauer() {};
	Clauer(const string& fitxerClauerEntrada);
	void afegirClau(Clau& clau);
	string obtenirContrasenya(Clau numeroPorta);
	void escriureFitxer(const string& fitxerClauerSortida);
	void pintarClauer() { m_clauer.print(); }
private:
	BBTree<Clau> m_clauer;
};