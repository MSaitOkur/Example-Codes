#ifndef PIMPLE_H_INCLUDED
#define PIMPLE_H_INCLUDED

class Myclass{
public:
	Myclass();
	~Myclass();
	void Myfunc();
	
private:
	struct pimpl;
	pimpl* mp;
};


#endif // PIMPLE_H_INCLUDED