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
 
#include <Arduino.h>
#include "ActionMultiplex.h"

ActionMultiplex::ActionMultiplex() :
	actions(NULL),
	timers(NULL),
	delay(ACTION_COMPLETE) {
}

void ActionMultiplex::init(Action** actions) {
	int length = 0;
	while(actions[length] != NULL)
		++length;
	
	if (timers != NULL)		
		delete timers;
		
	timers = new long[length];
	delay  = ACTION_COMPLETE;
}

long ActionMultiplex::start() {
	Action* action;
	delay = ACTION_COMPLETE;
	for(int i = 0; (action = actions[i]) != NULL; ++i) {
		long aDelay = timers[i] = action->start();
		if (delay == ACTION_COMPLETE || delay > aDelay)
			delay = aDelay;
	}
	return delay;
}

long ActionMultiplex::progress() {
	Action* action;
	long 	oldDelay = delay;
	
	delay = ACTION_COMPLETE;
	for(int i = 0; (action = actions[i]) != NULL; ++i) {
		if (timers[i] == ACTION_COMPLETE)
			continue;
			
		long aDelay = timers[i] = (timers[i] <= oldDelay ? action->progress() : timers[i] - oldDelay);
		if (delay == ACTION_COMPLETE || delay > aDelay)
			delay = aDelay;
	}
	return delay;
}

void ActionMultiplex::cancel() {
	Action* action;
	delay = ACTION_COMPLETE;
	for(int i = 0; (action = actions[i]) != NULL; ++i) {
		if (timers[i] != ACTION_COMPLETE)
			action->cancel();
	}
}


