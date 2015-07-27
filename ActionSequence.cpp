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
#include "ActionSequence.h"

ActionSequence::ActionSequence() :
	next(0) {
}

void ActionSequence::init(Action** seq) {
	next = 0;
	sequence = seq;
}

long ActionSequence::start() {
	next = 0;
	return progress();
}

long ActionSequence::progress() {
	for(Action* action = sequence[next>>1]; action != NULL; action = sequence[(++next)>>1]) {
		long delay = ((next & 1) == 0) ? action->start() : action->progress();
		if (delay != ACTION_COMPLETE) {
			next |= 1; // if sub action has not completed next call should be progress
			return delay;
		}
	}
	return ACTION_COMPLETE;
}

void ActionSequence::cancel() {
	Action* action = sequence[next>>1];
	if (action != NULL && (next & 1) == 1) // start hasn't been called, so no need to cancel
		action->cancel();
	next = 0;
}

