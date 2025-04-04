#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
  uint64_t encoded = remove_from_head(&q->data);
  return deserialize(encoded);
  
  //return (struct game_state){0};
}

int number_of_moves(struct game_state start) {
  return start.num_steps;
  
}
