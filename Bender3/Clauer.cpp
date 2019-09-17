#include "Clauer.h"

Clauer::Clauer(const string& fitxerClauerEntrada)
{
	m_clauer.read(fitxerClauerEntrada);
}

void Clauer::afegirClau(Clau& clau)
{
	m_clauer.insert(clau);
}

string Clauer::obtenirContrasenya(Clau numeroPorta)
{
	string contrasenya;
	BBTree<Clau>* pAct = dynamic_cast<BBTree<Clau>*> (pAct = &m_clauer);
	pAct = m_clauer.cerca(numeroPorta);
	if (pAct != NULL)
	{
		contrasenya = pAct->getData().getContrasenya();
	}
	return contrasenya;
}

void Clauer::escriureFitxer(const string& fitxerClauerSortida)
{
	int altura = m_clauer.level(&m_clauer);

	ofstream fileOut;
	fileOut.open(fitxerClauerSortida);
	if (fileOut.is_open())
	{
		fileOut << altura << endl;
		m_clauer.preorderWrite(fileOut, altura+1);
		fileOut.close();
	}
}