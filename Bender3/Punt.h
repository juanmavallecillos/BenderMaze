#pragma once

class Punt
{
public:
	Punt() {};
	~Punt() {};
	Punt(int x, int y) : m_x(x), m_y(y) {};
	int getX() const { return m_x; };
	void setX(const int x) { m_x = x; };
	int getY() const { return m_y; };
	void setY(const int y) { m_y = y; };
	void setEndavant(const bool& e) { m_enrere = e; };
	bool getEndavant() { return m_enrere; };

private:
	int m_x;
	int m_y;
	bool m_enrere;
};
