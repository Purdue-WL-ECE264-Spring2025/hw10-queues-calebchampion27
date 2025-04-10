#include "queue.h"
#include "tile_game.h"

int compare(struct game_state state1, struct game_state state2) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (state1.tiles[i][j] != state2.tiles[i][j]) {
        return 1;
      }
    }
  }
  return 0;
}

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
  size_t encoded = remove_from_head (&q->data);
  return deserialize(encoded);
  
  //return (struct game_state){0};
}

int is_finished(struct game_state board) {
  int correct = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == 3 && j == 3) {
        continue; 
      }

      if (board.tiles[i][j] != correct++) {
        return 0;   //false
      }
    }
  }

  return 1;  //true
}

int is_visited(struct linked_list *visited, size_t encoded) {
  struct game_state game = deserialize(encoded);
  struct list_node *node = visited->head;
  while (node != NULL) {
    struct game_state visit = deserialize(node->value);
    if (compare(game, visit) == 0) {
      return 1; // true
    }
    node = node->next;
  }
  return 0; // not visited
}

//which move to take
void explore_move(struct game_state *cur, struct queue *qu, struct linked_list *visited, void (*move_func)(struct game_state *), size_t encoded) {
  struct game_state new = *cur;
  move_func(&new);
  new.num_steps = cur->num_steps + 1; /////fixed

  if (!is_visited(visited, serialize(new))) {
    insert_at_head(visited, serialize(new));
    enqueue(qu, new);
  }
}

int number_of_moves(struct game_state start) {
  struct queue qu = {.data = {.head = NULL}};
  struct linked_list visited = {.head = NULL};
  
  enqueue(&qu, start);
  insert_at_head(&visited, serialize(start));

  while (qu.data.head != NULL) {
    struct game_state current = dequeue(&qu);
    //check if solved 
    if (is_finished(current)) {
      free_list(visited);
      free_list(qu.data);
      return current.num_steps;
    }

    //move
    if (current.empty_row != 0) {
      size_t encoded = serialize(current);
      explore_move(&current, &qu, &visited, move_down, encoded);
    }

    if (current.empty_row != 3) {
      size_t encoded = serialize(current);
      explore_move(&current, &qu, &visited, move_up, encoded);
    }

    if (current.empty_col != 0) {
      size_t encoded = serialize(current);
      explore_move(&current, &qu, &visited, move_left, encoded);
    }

    if (current.empty_col != 3) {
      size_t encoded = serialize(current);
      explore_move(&current, &qu, &visited, move_right, encoded);
    }
  }

  free_list(visited);
  free_list(qu.data);
  return -1;
}