#pragma once
#include <iostream>
#include <string>
using namespace std;
class Clau
{
public:
	void setnPorta(const int &n) { m_nPorta = n; };
	void setContrasenya(const string &contra) { m_contrasenya = contra; };
	int getnPorta() const { return m_nPorta; };
	string getContrasenya() const { return m_contrasenya; };

	friend std::ostream& operator<< (std::ostream& out, const Clau& a);
	friend std::istream& operator >> (std::istream& in, Clau& a);
	bool operator== (const Clau& a) { return(m_nPorta == a.m_nPorta && m_contrasenya == a.m_contrasenya); };
	bool operator< (const Clau& a) { return(m_nPorta < a.m_nPorta); };
	bool operator> (const Clau& a) { return(m_nPorta > a.m_nPorta); };

private:
	int m_nPorta;
	string m_contrasenya;
};