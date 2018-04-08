/*
 * file:	search.h
 * author:	GAndaLF
 * brief:	Search module public API.
 */

#ifndef _SEARCH_H_
#define _SEARCH_H_

void search_state_machine_init(void);
void search_state_machine(void);
bool search_is_finished(void);

#endif /* _SEARCH_H_ */
