#ifndef launch_h
#define launch_h

#define PROMPT_NEED_FAMILY 0x0100
#define PROMPT_UNED_FAMILY 0x0200

#define RET_FG (PROMPT_UNED_FAMILY | 0x01)
#define RET_BG (PROMPT_NEED_FAMILY | 0x02)
#define RET_NONE (PROMPT_NEED_FAMILY | 0x04)
#define RET_BUILTIN (PROMPT_NEED_FAMILY | 0x08);

#define NEED_TO_SHOW_PROMPT(x) ((x) & PROMPT_NEED_FAMILY)


int launch(char **argv);

#endif
