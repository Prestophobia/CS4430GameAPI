#include <Graphics/LinLeg.h>

LinLeg::LinLeg(void) {
}

LinLeg::LinLeg(float* pxi, float* pyi, float Vxi, float Vyi, float per) {
	posix = *pxi; // Wham-Bam! No calc's req'd!!
	posiy = *pyi;

	velix = Vxi;
	veliy = Vyi;

	period = per;

	*pxi = x(per); // function modifies start pos given to end pos for use to INIT next Leg!!
	*pyi = y(per); // just pass supplied init pos from call to call

} // end of INITlin()

/*
 LinLeg* LinLeg::INITlin(float* pxi, float* pyi, float Vxi, float Vyi, float per )
 {
 posix = *pxi;// Wham-Bam! No calc's req'd!!
 posiy = *pyi;

 velix = Vxi;
 veliy = Vyi;

 period = per;

 *pxi = x(per);// function modifies start pos given to end pos for use to INIT next Leg!!
 *pyi = y(per);// just pass supplied init pos from call to call

 return( this );
 }// end of INITlin()    */

LinLeg::LinLeg(float xi, float yi, float xf, float yf, float speed) {
	posix = xi;
	posiy = yi;
	float dist = sqrt((xf - xi) * (xf - xi) + (yf - yi) * (yf - yi));
	period = dist / speed;
	velix = speed * (xf - xi) / dist;
	veliy = speed * (yf - yi) / dist;
}

void LinLeg::INIT(float xi, float yi, float xf, float yf, float speed) {
	posix = xi;
	posiy = yi;
	float dist = sqrt((xf - xi) * (xf - xi) + (yf - yi) * (yf - yi));
	period = dist / speed;
	velix = speed * (xf - xi) / dist;
	veliy = speed * (yf - yi) / dist;
	return;
}


float LinLeg::x(float t) {
	return (posix + velix * t);
} // end of virtual x(t)

float LinLeg::y(float t) {
	return (posiy + veliy * t);
} // end of virtual y(t)
