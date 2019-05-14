#include "strutil.h"

#include <string.h>
#include <stdlib.h>

char *mystrtok(char **m,char *s,char c) {
	char *p = s ? s : *m;
	
	if(!*p)
		return NULL;
	
	*m = strchr(p,c);
  
	if(*m) 
		*(*m)++ = '\0';
	else 
		*m = p + strlen(p);
	
	return p;
}

void split_foreach(const char *text, int len, char delim, str_callback callback) {
	char buf[len];
	//memcpy(buf, text, len);
	sprintf(buf, "%s", text); 

	char *save;
	char *line;
	for (line = mystrtok(&save, buf, delim); line; 
			line = mystrtok(&save, NULL, delim)) {
		if (strlen(line)) callback(line, strlen(line));
	}

}
