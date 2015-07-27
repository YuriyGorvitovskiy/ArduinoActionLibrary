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

class ActionMultiplex : public Action {
protected:

	Action** 	actions;
	long*		timers;
	long		delay;	
public:

	ActionMultiplex();

	// the last action has to be NULL
	void init(Action** actions);

	virtual long start();
	virtual long progress();
	virtual void cancel();	
};


#endif //__ACTION_MULTIPLEX_H__