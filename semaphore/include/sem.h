#ifndef _sem_h
#define _sem_h

int sem_get(int key, int size);
int sem_down(int id, int block, ...);
int sem_up(int id);

#endif /* _sem_h */
