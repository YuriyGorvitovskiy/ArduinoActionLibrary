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
 
#ifndef __ACTION_SEQUENCE_H__
#define __ACTION_SEQUENCE_H__

#include "Action.h"

class ActionSequence : public Action {
protected:

	Action** 	sequence;
	byte 		next; //index = next >> 1;  if ((next & 1) == 1) then call progress() else call start();
	
public:

	ActionSequence();

	// the last action has to be NULL
	// maximum length 127 elements;
	void init(Action** seq);

	virtual long start();
	virtual long progress();
	virtual void cancel();	
};


#endif //__ACTION_SEQUENCE_H__