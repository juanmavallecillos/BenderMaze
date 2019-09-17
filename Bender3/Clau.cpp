#include "Clau.h"

std::ostream& operator <<(std::ostream & out, const Clau & a)
{
	out << a.getnPorta() << " " << a.getContrasenya() << endl;
	return out;
}

std::istream & operator >> (std::istream & in, Clau & a)
{
	in >> a.m_nPorta >> a.m_contrasenya;
	return in;
}
