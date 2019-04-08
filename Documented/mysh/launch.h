#ifndef launch_h
#define launch_h

#include "flags.h"

#define PROMPT_NEED_FAMILY  0x0100
#define PROMPT_UNED_FAMILY  0x0200

#define RET_FG 		        ADD(PROMPT_UNED_FAMILY, 0x01)
#define RET_BG 		        ADD(PROMPT_NEED_FAMILY, 0x02)
#define RET_NONE 	        ADD(PROMPT_NEED_FAMILY, 0x04)
#define RET_BUILTIN 	    ADD(PROMPT_NEED_FAMILY, 0x08);

#define NEED_TO_SHOW_PROMPT(X) HAS((X), PROMPT_NEED_FAMILY)

int launch(char **argv);

void handle(void);

#endif /* launch_h */
