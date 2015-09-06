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

#ifndef __ACTION_H__
#define __ACTION_H__

#include <Arduino.h>

#define ACTION_COMPLETE (0L)

class Action {
public:

	//return delay in milliseconds till next progress call;
	virtual long start()    = 0;
	virtual long progress() = 0;
	virtual void cancel()   = 0;
};

class SingleAction : public Action {
public:
    virtual long progress();
	virtual void cancel();
};

class Delay : public SingleAction {
public:
    Delay(long milliseconds) : milliseconds(milliseconds) {}

    virtual long start();
protected:
    long milliseconds;
};

class RedundantSingleAction : public SingleAction {
public:
	RedundantSingleAction(int maxAttempts, long msCheckDelay) : maxAttempts(maxAttempts), msCheckDelay(msCheckDelay) {}

	virtual long start();
	virtual long progress();
	virtual void cancel();

	virtual void 	execute() = 0;
	virtual boolean check()   = 0;

protected:
	int  attempts;
	int  maxAttempts;
	long msCheckDelay;
};

#endif //__ACTION_H__
