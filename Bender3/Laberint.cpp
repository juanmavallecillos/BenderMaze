#include "Laberint.h"

Laberint::Laberint()
{
}
Laberint::~Laberint()
{
}
void Laberint::iniSprite()
{
#ifdef GRAPHICS
	m_caselles[0].Create("data/cnegre.png");
	m_caselles[1].Create("data/cblanc.png");
	m_caselles[2].Create("data/beer.png");
	m_caselles[3].Create("data/porta.png");
	m_caselles[4].Create("data/clau.png");
	m_caselles[5].Create("data/beerMarcador.png");
	digits[0].Create("data/numeros/numero0000.png");	//////////////////////////////////////
	digits[1].Create("data/numeros/numero0001.png");	//
	digits[2].Create("data/numeros/numero0002.png");	//
	digits[3].Create("data/numeros/numero0003.png");	//
	digits[4].Create("data/numeros/numero0004.png");	// Inicialitzar numeros dels marcadors
	digits[5].Create("data/numeros/numero0005.png");	//
	digits[6].Create("data/numeros/numero0006.png");	//
	digits[7].Create("data/numeros/numero0007.png");	//
	digits[8].Create("data/numeros/numero0008.png");	//
	digits[9].Create("data/numeros/numero0009.png");	//////////////////////////////////////
#endif
}
void Laberint::iniciar(const int x, const int y)
{
	m_tauler = new int*[x];
	setMidaX(x);
	setMidaY(y);
	for (int i = 0; i < x; i++)
	{
		m_tauler[i] = new int[y];
	}
}

void Laberint::setCasella(int x, int y, int a)
{
	m_tauler[x][y] = a;
}

int Laberint::getCasella(int x, int y) const
{
	return m_tauler[x][y];
}

void Laberint::dibuixaLaberint()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < m_midaX; i++)
	{
		for (int j = 0; j < m_midaY; j++)
		{
			#ifdef GRAPHICS
			m_caselles[m_tauler[i][j]].Draw(x, y+100);
			#endif
			y += MIDACASELLA;
		}
		y = 0;
		x += MIDACASELLA;
	}
}

void Laberint::setMidaX(int a)
{
	m_midaX = a;
}

void Laberint::setMidaY(int a)
{
	m_midaY = a;
}

int Laberint::getMidaX() const
{
	return m_midaX;
}

int Laberint::getMidaY() const
{
	return m_midaY;
}

// Funcio per saber si el laberint conté cicles
bool Laberint::conteCicles(Graph<int, int>* graf)
{
	bool cicles = false;
	int valorNode = 0;
	Node<InfoArestaGraph<int, int>>* aresta1 = NULL;
	Node<InfoArestaGraph<int, int>>* aresta2 = NULL;
	for (int i = 0; i < m_midaX; i++)
	{
		for (int j = 0; j < m_midaY;j++)
		{
			// Si la casella on ens trobem és > 0, comprovem si té nodes adjacents abaix o a la dreta
			if (m_tauler[j][i] > 0)
			{
				if (graf->search(valorNode) == NULL)
				{
					graf->insertNode(valorNode);
				}
				if (i < m_midaX - 1) // Comprovem que no ens sortim del taulell
				{
					if (m_tauler[j][i+1] > 0) // Comprovem si hi ha node adjacent a sota
					{
						if (graf->search(valorNode + m_midaX) == NULL) // Si el node adjacent no ha sigut insertat al graf, l'insertem
						{
							graf->insertNode(valorNode + m_midaX);
						}
						graf->insertAresta(1, graf->search(valorNode), graf->search(valorNode + m_midaX), aresta1, aresta2);

					}
				}
				if (j < m_midaY - 1) // Comprovem que no ens sortim del taulell
				{
					if (m_tauler[j + 1][i] > 0) // Comprovem si hi ha node adjacent a la dreta
					{
						if (graf->search(valorNode + 1) == NULL) // Si el node adjacent no ha sigut insertat al graf, l'insertem
						{
							graf->insertNode(valorNode + 1);
						}
						graf->insertAresta(1, graf->search(valorNode), graf->search(valorNode + 1), aresta1, aresta2);
					}
				}
			}
			valorNode++;
		}
	}
	// Fem la comprovació #nodes-1 = #arestes
	if (graf->getNumNodes() - 1 != graf->getNumArestes())
	{
		cicles = true;
	}
	return cicles;
}

void Laberint::pintarMarcador(int valor, int posX, int posY)
{
	int divisor = 100;
	int posXActual = posX;
	int nActual = valor;
	bool primerDigit = true;
	int pasDigit = 20;
	m_caselles[5].Draw(5, 5);
	m_caselles[0].Draw(65, 5);
	while (divisor > 0)
	{
		int d = nActual / divisor;
		nActual = nActual % divisor;
		divisor = divisor / 10;

		if ((d > 0) || !primerDigit || (divisor == 0))
		{
			digits[d].Draw(posXActual, posY);
			primerDigit = false;
		}

		posXActual += pasDigit;
	}
}