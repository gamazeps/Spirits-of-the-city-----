#ifndef PIR_THREAD_H
#define PIR_THREAD_H

// Définit tous les combien on regarde s'il y a un passant
#define PRESENCE_CHECK_TIME_MILLISECONDS 100

// Indique si on a détecté quelqu'un ou pas
extern volatile bool presence_detected;

void startPirThread(void);

#endif
