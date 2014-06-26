#ifndef SEM_H
#define SEM_H

#include "ch.h"

//Allow led thread to sleep while no one is there
extern Semaphore presence_sem;

//Lock PIR censor during an animation
extern Semaphore animation_sem;


#endif
