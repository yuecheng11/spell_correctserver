#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_
class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}
private:
	Noncopyable(const Noncopyable &);
	Noncopyable &operator=(const Noncopyable &);
};

#endif