#ifndef PATH_H
#define PATH_H

#include <bin/Graphics/LinLeg.h>
#include <SFML/Graphics.hpp>

class Path {

public:
	sf::Sprite** ppSprite; // for array of sprite pointers (a different object can be drawn on each Leg)

	// for use with Legs
	LinLeg** ppLeg; // for array of Leg pointers
	float xi; // the common start positions
	float yi;
	float* px;
	float* py;
	float* ptLeg;
	int nLegs;
	int nLegs_inUse; // <= nLegs

	// Path use and timing
	bool inUse;
	bool done;
	int delay;
	int launch_dt;

	// functions
	void reset(bool InUse, int Delay = 0);
	void move();
	void draw(sf::RenderWindow *pWndw);
	Path(int N_legs, int Delay, int Launch_dt, float Xi, float Yi);
	~Path();
};

#endif // PATH_H
