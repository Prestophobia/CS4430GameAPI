/**
 * @file /CS4430GameAPI/src/include/FrameState.h
 * @author Neek
 * @date Nov 28, 2017
 * @brief .
 *
 * @details .
 */

#ifndef INCLUDE_FRAMESTATE_H_
#define INCLUDE_FRAMESTATE_H_

#include <string>

class FrameState {
public:
	int frame_number = -1;
	double time = -1;
	std::string input;
	std::string state;

	FrameState() {

	}

	FrameState(int frame_number, double time, std::string input,
			std::string state) :
			frame_number(frame_number), time(time), input(input), state(state) {

	}
};

#endif /* INCLUDE_FRAMESTATE_H_ */
