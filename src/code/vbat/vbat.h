/*
 * file:	vbat.h
 * author:	GAndaLF
 * brief:	Battery voltage monitor.
 */

#ifndef _VBAT_H_
#define _VBAT_H_

/**
 * Initialise battery voltage monitor task to work.
 *
 * Battery voltage monitor task periodically checks if battery voltage drops below
 * threshold and sets LED.
 */
void vbat_task_init(void);

#endif /* _VBAT_H_ */
