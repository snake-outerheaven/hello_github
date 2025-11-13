#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 0xF
#define MAX_WORKERS 0x14
#define MAX_WAIT 0X124F8

typedef enum line Line;
typedef struct worker Worker;
typedef struct workerqueue WorkerQueue;
typedef struct mempool MPool;

enum line {
  LINE_1,
  LINE_2,
  NULL_L,
};
struct worker {
  uint64_t id;
  char nome[MAX_BUF];
  Line l;
  uint32_t prod;
};

struct workerqueue {
  Worker *w;
  WorkerQueue *next;
  WorkerQueue *(*new)(void);
};

struct mempool {
  void *mem;
  size_t sz;
  size_t used;
};

int trim(char *str);
int wait_ms(uint32_t tm);
int clear_screen(void);

Worker worker_new(void);
void worker_free(Worker *w);
int worker_setLn(Worker *w, Line ln);
int worker_setProd(Worker *w, uint32_t p);

WorkerQueue *queue_new(void);
int queue_push(WorkerQueue **head, Worker *w);
Worker *queue_pop(WorkerQueue **head);
void queue_free(WorkerQueue **head);
int queue_size(WorkerQueue *head);

MPool *mempool_new(size_t sz);
void mempool_free(MPool *pool);
void *mempool_alloc(MPool *pool, size_t sz);
void mempool_reset(MPool *pool);

int main(void);
