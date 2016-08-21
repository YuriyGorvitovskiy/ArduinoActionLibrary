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
#include "ActionProcessor.h"

ActionProcessor Processor;

ActionProcessor::ActionProcessor() {
}

void ActionProcessor::setup() {
	for(int i = 0; i < MAX_SIMULTANEOUS_ACTIONS; ++i)
		actions[i] = NULL;
}

void ActionProcessor::loop() {
	long time = millis();
	for(int i = 0; i < MAX_SIMULTANEOUS_ACTIONS; ++i) {
		if (actions[i] == NULL || timers[i] > time)
			continue;
		long delay = actions[i]->progress();
		if(delay == ACTION_COMPLETE)
			actions[i] = NULL;
		else
			timers[i] = time + delay;
	}
}

void ActionProcessor::start(Action* action) {
	long delay = action->start();
	if(delay == ACTION_COMPLETE)
		return;

	for(int i = 0; i < MAX_SIMULTANEOUS_ACTIONS; ++i) {
		if (actions[i] == action) {
			timers[i] = millis() + delay;
			return;
		}

		if (actions[i] != NULL)
			continue;

		actions[i] = action;
		timers[i] = millis() + delay;
		return;
	}
}

void ActionProcessor::cancel(Action* action) {
	for(int i = 0; i < MAX_SIMULTANEOUS_ACTIONS; ++i) {
		if (actions[i] != action)
			continue;

		actions[i] = NULL;
		action->cancel();
		return;
	}
}
