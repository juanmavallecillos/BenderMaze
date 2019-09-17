#pragma once
//Difinicions amb la variable d'activació de la llibreria gràfica, __viz_graphics__
#include "Definitions.h"
#include "Graph.hpp"

#ifdef GRAPHICS
	#include "lib/libreria.h"
#endif

const int MIDACASELLA = 60;

class Laberint
{
public:
	Laberint();
	~Laberint();
	void iniSprite();
	void iniciar(const int x, const int y);
	void setCasella(int x, int y, int a);
	int getCasella(int x, int y) const;
	void dibuixaLaberint();
	void setMidaX(int a);
	void setMidaY(int a);
	int getMidaX() const;
	int getMidaY() const;
	// Funcio per saber si el laberint conté cicles
	bool conteCicles(Graph<int, int>* graf);
	void pintarMarcador(int valor, int posX, int posY);

private:
	int **m_tauler;
	int m_midaX;
	int m_midaY;
	#ifdef GRAPHICS
	Sprite m_caselles[6];
	Sprite digits[10];
	#endif
};
