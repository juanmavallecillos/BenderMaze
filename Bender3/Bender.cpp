#include "Bender.h"

Bender::Bender()
{
}
Bender::~Bender()
{
}

void Bender::inicialitzar(const int x, const int y)
{
	m_anteriorX = -1;
	m_anteriorY = -1;
	setPosX(x * MIDACASELLA);
	setPosY(y * MIDACASELLA);
	m_avanca = true;
}

void Bender::iniSprite()
{
	#ifdef GRAPHICS
	m_robot.Create("data/bender.png");
	m_moviments[0].Create("data/avanca.png");
	m_moviments[1].Create("data/retrocedeix.png");
	m_moviments[2].Create("data/fonsMoviment.png");
	#endif
}

int Bender::getPosX() const
{
	return m_posicioX;
}

int Bender::getPosY() const
{
	return m_posicioY;
}

void Bender::setPosX(const int x)
{
	m_posicioX = x;
}

void Bender::setPosY(const int y)
{
	m_posicioY = y;
}

void Bender::dibuixaRobot()
{
	#ifdef GRAPHICS
	m_robot.Draw(getPosX(), getPosY() + 100);
	m_moviments[2].Draw(450, 30);
	if (m_avanca)
	{
		m_moviments[0].Draw(500, 30);
	}
	else
	{
		m_moviments[1].Draw(450, 30);
	}
	#endif
}

bool Bender::moureRobot(Laberint &tauler, int &beer, Pila<Punt>& movimentsPossibles, Cua<Clau>& clausCua, Clauer& clauer, Cua<Clau>& portes)
{
	bool moviment = false;
	bool porta = false;
	int possiblesMoves = 0;
	Punt p;
	Clau aux;
	bool left = false, up = false, right = false, down = false;
	// Comprovem quants moviments pot fer
	if (tauler.getCasella(m_posicioX / MIDACASELLA, m_posicioY / MIDACASELLA) == 2)
	{
		PlaySound(TEXT("data/gulp.wav"), NULL, SND_ASYNC);
		beer++;
		tauler.setCasella(m_posicioX / MIDACASELLA, m_posicioY / MIDACASELLA, 1);
	}
	else
	{
		if (tauler.getCasella(m_posicioX / MIDACASELLA, m_posicioY / MIDACASELLA) == 4)
		{
			PlaySound(TEXT("data/takekey.wav"), NULL, SND_ASYNC);
			tauler.setCasella(m_posicioX / MIDACASELLA, m_posicioY / MIDACASELLA, 1);
			if (!clausCua.esBuida())
			{
				aux = clausCua.getPrimer();
				clauer.afegirClau(aux);
				clausCua.treu();
			}
		}
		else
		{
			if (tauler.getCasella(m_posicioX / MIDACASELLA, m_posicioY / MIDACASELLA) == 3)
			{
				if (!portes.esBuida())
				{
					if (portes.getPrimer().getContrasenya() == clauer.obtenirContrasenya(portes.getPrimer()))
					{
						PlaySound(TEXT("data/opendoor.wav"), NULL, SND_SYNC);
						tauler.setCasella(m_posicioX / MIDACASELLA, m_posicioY / MIDACASELLA, 1);
						portes.treu();
					}
					else
					{
						PlaySound(TEXT("data/lockeddoor.wav"), NULL, SND_SYNC);
						portes.treu();
						porta = true;
					}
				}
				else
				{
					porta = true;
				}
			}
		}
	}

	if ((m_posicioX != 0) && ((tauler.getCasella((m_posicioX / MIDACASELLA) - 1, m_posicioY / MIDACASELLA) != 0) && ((m_anteriorX != (m_posicioX - MIDACASELLA)) || (m_anteriorY != m_posicioY))))
	{
		possiblesMoves++;
		left = true;
	}

	if ((m_posicioY != 0) && ((tauler.getCasella(m_posicioX / MIDACASELLA, (m_posicioY / MIDACASELLA) - 1) != 0) && ((m_anteriorX != m_posicioX) || (m_anteriorY != (m_posicioY - MIDACASELLA)))))
	{
		possiblesMoves++;
		up = true;
	}

	if ((m_posicioX / MIDACASELLA != (tauler.getMidaX() - 1)) && ((tauler.getCasella((m_posicioX / MIDACASELLA) + 1, m_posicioY / MIDACASELLA) != 0) && ((m_anteriorX != (m_posicioX + MIDACASELLA)) || (m_anteriorY != m_posicioY))))
	{
		possiblesMoves++;
		right = true;
	}

	if ((m_posicioY / MIDACASELLA != (tauler.getMidaY() - 1)) && ((tauler.getCasella(m_posicioX / MIDACASELLA, (m_posicioY / MIDACASELLA) + 1) != 0) && ((m_anteriorX != m_posicioX) || (m_anteriorY != (m_posicioY + MIDACASELLA)))))
	{
		down = true;
		possiblesMoves++;
	}

	// Si només hem contat un moviment, el fa directament
	if ((possiblesMoves == 1) && (!porta))
	{
		if (left)
		{
			m_anteriorX = m_posicioX;
			m_anteriorY = m_posicioY;
			m_posicioX -= MIDACASELLA;
			moviment = true;
		}
		else
		{
			if (up)
			{
				m_anteriorY = m_posicioY;
				m_anteriorX = m_posicioX;
				m_posicioY -= MIDACASELLA;
				moviment = true;
			}
			else
			{
				if (right)
				{
					m_anteriorX = m_posicioX;
					m_anteriorY = m_posicioY;
					m_posicioX += MIDACASELLA;
					moviment = true;
				}
				else
				{
					if (down)
					{
						m_anteriorY = m_posicioY;
						m_anteriorX = m_posicioX;
						m_posicioY += MIDACASELLA;
						moviment = true;
					}
				}
			}
		}
	}
	else // Si té més d'un moviment possible llavors:
	{
		if ((possiblesMoves == 0) || (porta)) // No pot fer cap moviment (Hem arribat a un cul de sac)
		{
			if (m_avanca) // Si arribem a un cul de sac i estem avançant, podem continuar retrocedint per on hem vingut
			{
				if (!movimentsPossibles.esBuida())
				{
					int aux;
					aux = m_anteriorX;
					m_anteriorX = m_posicioX;
					m_posicioX = aux;
					aux = m_anteriorY;
					m_anteriorY = m_posicioY;
					m_posicioY = aux;
					m_avanca = false;
					moviment = true;
				}
			}
			else // Si no estem avançant significa que hem arribat al punt inicial, per tant, acaba el joc
			{
				PlaySound(TEXT("data/win.wav"), NULL, SND_SYNC);
				moviment = false;
			}
		}
		else // Podem fer més d'un moviment, som a una bifurcació
		{
			if (m_avanca) // Si arribem a la bifurcació per primera vegada
			{
				// Guardem la posició per on hem vingut amb el distinctiu (endavant = false) ja que es per on hem vingut
				p.setX(((m_posicioX / MIDACASELLA) - (m_anteriorX / MIDACASELLA)) * -1);
				p.setY(((m_posicioY / MIDACASELLA) - (m_anteriorY / MIDACASELLA)) * -1);
				p.setEndavant(false);
				movimentsPossibles.push(p);
				// Guardem les altres possibles opcions per ordre
				if (down)
				{
					p.setX(0);
					p.setY(1);
					p.setEndavant(true);
					movimentsPossibles.push(p);
				}
				if (right)
				{
					p.setX(1);
					p.setY(0);
					p.setEndavant(true);
					movimentsPossibles.push(p);
				}
				if (up)
				{
					p.setX(0);
					p.setY(-1);
					p.setEndavant(true);
					movimentsPossibles.push(p);
				}
				if (left)
				{
					p.setX(-1);
					p.setY(0);
					p.setEndavant(true);
					movimentsPossibles.push(p);
				}

				// Avançem per el sentit que ha quedat adalt de tot de la pila i el treiem de la pila
				m_anteriorX = m_posicioX;
				m_anteriorY = m_posicioY;
				m_posicioX += (movimentsPossibles.top().getX()) * MIDACASELLA;
				m_posicioY += (movimentsPossibles.top().getY()) * MIDACASELLA;
				movimentsPossibles.pop();
				moviment = true;
			}
			else // Si arribem a una bifurcació per segon ( o més ) cop
			{
				// Avançem per el següent sentit
				m_anteriorX = m_posicioX;
				m_anteriorY = m_posicioY;
				p = movimentsPossibles.top();
				m_posicioX += p.getX() * MIDACASELLA;
				m_posicioY += p.getY() * MIDACASELLA;
				movimentsPossibles.pop();
				moviment = true;
				// Si la posicio a la que hem avançat no es de tornada, tornem  
				// a indicar que estem avançant per una zona encara desconeguda
				if (p.getEndavant())
				{
					m_avanca = true;
				}
			}
		}

	}
	return moviment;
}