template <class T>
class Parell
{
public:
	Parell() { m_p1 = -1; m_p2 = -1; }
	Parell(T p1, T p2) { m_p1 = p1; m_p2 = p2; }
	Parell(Parell<T>& par1) { (*this) = par1; }
	~Parell() {}
	Parell<T>& operator=(const Parell<T>& par1) { m_p1 = par1.m_p1; m_p2 = par1.m_p2; return (*this);}
	T& getP1() { return m_p1; }
	T& getP2() { return m_p2; }

private:
	T m_p1;
	T m_p2;
};