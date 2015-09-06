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

long SingleAction::progress() {
    return ACTION_COMPLETE;
}

void SingleAction::cancel() {
}

long Delay::start() {
    return milliseconds;
}

long RedundantSingleAction::start() {
    attempts = 0;
    return progress();
}

long RedundantSingleAction::progress() {
    if (attempts >= maxAttempts || (attempts > 0 && check()))
        return ACTION_COMPLETE;

    attempts++;
    execute();
    return msCheckDelay;
}

void RedundantSingleAction::cancel() {
    attempts = maxAttempts;
}
