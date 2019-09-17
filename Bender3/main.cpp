// main.cpp: define el punto de entrada de la aplicación de consola.
//

//Difinicions amb la variable d'activació de la llibreria gràfica, __viz_graphics__
#include "Definitions.h"

//Includes de les llibreries gràfiques
#ifdef GRAPHICS
	#define SDL_MAIN_HANDLED 
	#include "lib\libreria.h"
	#include <windows.h>
#endif 

#include "Bender.h"
#include "Laberint.h"
#include "Cua.h"
#include "Pila.h"
#include <string>
#include <fstream>
#include "Clau.h"
#include "Clauer.h"

using namespace std;

//Funció per la lectura del fitxer del laberint
bool readFixerEntrada(const string& filename, int *X, int *Y, Bender *robot, Laberint *tauler)
{
	string excepcio;
	ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		int numNodes = 0;
		int benderX, benderY;
		int valor, search1 = 0, search2;
		file >> benderY >> benderX;
		file >> *Y >> *X;
		robot->inicialitzar(benderX, benderY);
		tauler->iniciar(*X, *Y);
		if (!file.eof())
		{
			for (int i = 0; i < *X; i++)
			{
				for (int j = 0; j < *Y; j++)
				{
					file >> valor;
					tauler->setCasella(j, i, valor);
				}
			}
		}
		file.close();
	}
	else
	{
		// Llença una excepcio de que no s'ha pogut obrir el fitxer
		excepcio = "fitxerMapa";
		throw excepcio;
	}
	return false;
}

//Funció per a guardar el fitxer de sortida amb els moviments
void writeFitxerSortida(const string& filename, Cua<Punt>& moviments, int cervesses)
{
	string excepcio;
	ofstream fileOut;
	fileOut.open(filename);
	if (fileOut.is_open())
	{
		Punt aux;
		fileOut << cervesses << endl;
		while (!moviments.esBuida())
		{
			aux = moviments.getPrimer();
			fileOut << aux.getY() << " " << aux.getX() << endl;
			moviments.treu();
		}
		fileOut.close();
	}
	else
	{
		// Llença una excepcio de que no s'ha pogut obrir el fitxer
		excepcio = "fitxerRecorregut";
		throw excepcio;
	}
}

//Funció per a inicialitzar els Sprites de les classes Bender i Laberint
void inicialitzarSprites(Bender& robot, Laberint& taulell)
{
	taulell.iniSprite();
	robot.iniSprite();
}

//Funció per a pintar els elements del joc (robot i laberint)
void dibuixarElements(Bender& robot, Laberint& taulell)
{
	taulell.dibuixaLaberint();
	robot.dibuixaRobot();
}

// Funció per guardar a la Cua la posició actual d'en Bender
void guardarPosicio(Bender& bender, Cua<Punt>& moviments)
{
	Punt actual;
	actual.setX(bender.getPosX() / MIDACASELLA);
	actual.setY(bender.getPosY() / MIDACASELLA);
	moviments.afegeix(actual);
}

// Funció per llegir els fitxers de les claus i portes
void readFitxerClaus(const string &filename, Cua<Clau>& clauOporta)
{
	string excepcio;
	ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		Clau clau;
		int nPorta;
		string contrasenya;
		file >> nPorta;
		while (!file.eof())
		{
			clau.setnPorta(nPorta);
			file >> contrasenya;
			clau.setContrasenya(contrasenya);
			clauOporta.afegeix(clau);
			file >> nPorta;
		}
		file.close();
	}
	else
	{
		// Llença una excepcio de que no s'ha pogut obrir el fitxer
		excepcio = "fitxerClauPorta";
		throw excepcio;
	}
}


// Funció principal
int main(int argc, char* argv[])
{
	string excepcio;
	try
	{
		// Si el nombre d'arguments és correcte:
		if (argc == 7)
		{
			Bender bender;
			Laberint laberint;
			Cua<Punt> moviments;
			Punt actual;
			Pila<Punt> movimentsPossibles;
			int cervesses = 0;
			bool final = false;
			int midaX;
			int midaY;
			Clauer clauer(argv[3]);
			Cua<Clau> claus;
			Cua<Clau> portes;
			Graph<int, int> grafLaberint;
			

			// Llegim els fitxers de les claus i les portes
			readFitxerClaus(argv[5], claus);
			readFitxerClaus(argv[6], portes);

			//Llegim el fitxer on s'emmagatzema el laberint
			if (!readFixerEntrada(argv[1], &midaX, &midaY, &bender, &laberint))
			{
				#ifdef GRAPHICS
				SDL_SetMainReady();
				SDL_Init(SDL_INIT_VIDEO);

				// Declaració de lobjecte de la classe Game canviant el tamany per defecte de la pantalla
				Game joc(midaX * MIDACASELLA, (midaY * MIDACASELLA)+100);

				// Inicialització de lentorn gràfic. Sha de cridar abans de declarar o 
				// utilitzar qualsevol altre element de la llibreria
				joc.Init();

				// Inicialització dels sprites de les classes
				inicialitzarSprites(bender, laberint);

				//Pantalla gràfica
				joc.Video_ShowWindow();
				#endif

				// Si el laberint no conté cap cicle continuem, sino excepció
				if (!laberint.conteCicles(&grafLaberint))
				{
					// Guardem posició inicial només en cas de que no hi hagi només 1 posició al laberint
					if ((midaX != 1) && (midaY != 1))
					{
						guardarPosicio(bender, moviments);
					}

					// Bucle principal del joc
					do {
						#if GRAPHICS
						// Dibuixa laberint i robot a la nova posició
						dibuixarElements(bender, laberint);
						laberint.pintarMarcador(cervesses, 20, 30);

						joc.VideoUpdate();
						Sleep(500);
						#endif

						// Mou el robot i guarda la nova posició i actualitza la posició anterior
						final = !(bender.moureRobot(laberint, cervesses, movimentsPossibles, claus, clauer, portes));
						if (!final)
						{
							guardarPosicio(bender, moviments);
						}
					} while (!final); // Mentres que en Bender no arriba a un cul de sac de tornada no acaba el joc

					// Guardem els punts X,Y del camí seguit
					writeFitxerSortida(argv[2], moviments, cervesses);
					// Guardem el clauer final
					clauer.escriureFitxer(argv[4]);
				}
				else // Si el laberint conté cicles, llancem excepció de cicles
				{
					excepcio = "cicles";
					throw excepcio;
				}
			}
			#if GRAPHICS
			//Instruccio necesaria per poder finalitzar els gràfics
			SDL_Quit();
			#endif
		}
		else // Si el nombre d'arguments no és correcte llencem una excepció de que el nombre d'arguments és incorrecte
		{
			excepcio = "arguments";
			throw excepcio;
		}
	}
	catch (string opcio) // Si hem llençat una excepció, mostrem el missatge d'error corresponent
	{
		if (opcio == "arguments") // Número d'arguments incorrectes
		{
			cout << "ERROR: Numero de argumentos incorrectos. Se esperaban 6" << endl;
		}
		else
		{
			if (opcio == "cicles") // El mapa conté cicles
			{
				cout << "ERROR: el laberinto " << argv[1] << " de entrada tiene ciclos y no se puede resolver" << endl;
			}
			else
			{
				cout << "ERROR: No se pudo abrir el archivo "; // Aquest missatge es igual per totes les excepcions de fitxers
				if (opcio == "fitxerMapa") // El fitxer del mapa no s'ha pogut obrir
				{
					cout << argv[1] << endl;
				}
				else
				{
					if (opcio == "fitxerRecorregut") // No s'ha pogut obrir el fitxer de sortida del recorregut
					{
						cout << argv[2] << endl;
					}
					else
					{
						if (opcio == "fitxerClauPorta") // No s'ha pogut obrir el fitxer amb les claus o les portes del mapa
						{
							cout << argv[5] << " o el archivo " << argv[6] << endl;
						}
					}
				}
			}
		}
	}
	return 0;
}
