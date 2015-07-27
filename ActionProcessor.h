/**
 ** This is Public Domain Software.
 **
 ** The author disclaims copyright to this source code.
 ** In place of a legal notice, here is a blessing:
 **
 **    May you do good and not evil.
 **    May you find forgiveness for yourself and forgive others.
 **    May you share freely, never taking more than you give.
 **/

#ifndef __ACTION_MULTIPLEX_H__
#define __ACTION_MULTIPLEX_H__

#include "Action.h"

#define MAX_SIMULTANEOUS_ACTIONS (16)

class ActionProcessor {
protected:
	Action*  actions[MAX_SIMULTANEOUS_ACTIONS];
	long 	 timers [MAX_SIMULTANEOUS_ACTIONS];

public:

	ActionProcessor();

	void setup();
	void loop();

	void start(Action* action);
	void cancel(Action* action);
};

extern ActionProcessor Processor;

#endif //__ACTION_MULTIPLEX_H__
