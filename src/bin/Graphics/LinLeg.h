#ifndef LINLEG_H
#define LINLEG_H

#include<cmath>

class LinLeg {
public:

	float period = 0;
	float posix = 0;
	float posiy = 0;
	float velix = 0;
	float veliy = 0;

	//** member functions **
	float x(float t);
	float y(float t);

//	void INIT(float* pxi, float* pyi, float Vxi, float Vyi, float per );
	void INIT(float xi, float yi, float xf, float yf, float speed);

	LinLeg(void);
	LinLeg(float* pxi, float* pyi, float Vxi, float Vyi, float per);
	LinLeg(float xi, float yi, float xf, float yf, float speed);
};

#endif // LINLEG_H
