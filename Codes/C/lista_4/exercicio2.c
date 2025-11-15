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
};

struct mempool {
  void *mem;
  size_t sz;
  size_t used;
};

int trim(char *str);
int wait_ms(uint32_t tm);
int clear_screen(void);

int worker_init(Worker *w);
void worker_destroy(Worker *w);
int worker_set_line(Worker *w, Line ln);
int worker_set_prod(Worker *w, uint32_t p);
int worker_set_name(Worker *w, const char *name);

int queue_init(WorkerQueue **q);
void queue_destroy(WorkerQueue **q);
int queue_push(WorkerQueue *q, Worker *w);
int queue_pop(WorkerQueue *q, Worker **out);
size_t queue_size(const WorkerQueue *q);

int mempool_init(MPool *pool, size_t sz);
void mempool_destroy(MPool *pool);
void *mempool_alloc(MPool *pool, size_t sz);
void mempool_reset(MPool *pool);

int main(void);
