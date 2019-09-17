#pragma once
//Difinicions amb la variable d'activació de la llibreria gràfica, __viz_graphics__
#include "Definitions.h"
#ifdef GRAPHICS
#include "lib/libreria.h"
#include <Windows.h>
#include <mmsystem.h>
#endif
#include "Laberint.h"
#include "Pila.h"
#include "Cua.h"
#include "Clauer.h"

class Bender
{
public:
	Bender();
	~Bender();
	void inicialitzar(const int x, const int y);
	void iniSprite();
	int getPosX() const;
	int getPosY() const;
	void setPosX(const int x);
	void setPosY(const int y);
	void dibuixaRobot();
	bool moureRobot(Laberint &tauler, int &beer, Pila<Punt>& movimentsPossibles, Cua<Clau>& claus, Clauer& clauer, Cua<Clau>& portes);

private:
	int m_posicioX;
	int m_posicioY;
	int m_anteriorX;
	int m_anteriorY;
	bool m_avanca;
	#ifdef GRAPHICS
	Sprite m_robot;
	Sprite m_moviments[3];
	#endif
};
