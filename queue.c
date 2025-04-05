#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) {
  size_t encoded = remove_from_head (&q->data);
  return deserialize(encoded);
  
  //return (struct game_state){0};
}
/*
int is_solved(struct game_state state) {
  int val = 1;
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (r == 3 && c == 3) {
      if (state.board[r][c] != 0) {
        return 0;
      }
      }
      else {
      if (state.board[r][c] != val) {
        return 0;
      }
      val++;
      }
    }
  } 
}
*/


int number_of_moves(struct game_state start) {
  struct queue q = {0}; 
  struct linked_list visited = {0};   

  //start
  enqueue(&q, start);
  insert_at_head(&visited, serialize(start));

  while (q.data.head != NULL) {
    struct game_state curr = dequeue(&q);

    //solved
    if (is_solved(curr)) {
      free_list(&visited);
      free_list(&q.data);
      return curr.num_steps;
    }

    //moves
    int r = curr.empty_row;
    int c = curr.empty_col;
    int dr[] = {-1, 1, 0, 0}; // up, down, left, right
    int dc[] = {0, 0, -1, 1};

    //up
    if (r > 0) {
      struct game_state next = curr;
      next.board[r][c] = next.board[r-1][c];
      next.board[r-1][c] = 0;
      next.empty_row = r - 1;
      next.empty_col = c;
      next.num_steps = curr.num_steps + 1;

      if (!is_solved(next)) {
        size_t encoded = serialize(next);
        int seen = 0;
        struct list_node *node = visited.head;
        while (node != NULL) {
          if (node->value == encoded) {
            seen = 1;
            break;
          }
          node = node->next;
        }

        if (!seen) {
          insert_at_head(&visited, encoded);
          enqueue(&q, next);
        }
      }
    }

    //down
    if (r < 3) {
      struct game_state next = curr;
      next.board[r][c] = next.board[r+1][c];
      next.board[r+1][c] = 0;
      next.empty_row = r + 1;
      next.empty_col = c;
      next.num_steps = curr.num_steps + 1;

      if (!is_solved(next)) {
        size_t encoded = serialize(next);
        int seen = 0;
        struct list_node *node = visited.head;
        while (node != NULL) {
          if (node->value == encoded) {
            seen = 1;
            break;
          }
          node = node->next;
        }

        if (!seen) {
          insert_at_head(&visited, encoded);
          enqueue(&q, next);
        }
      }
    }

    //left
    if (c > 0) {
      struct game_state next = curr;
      next.board[r][c] = next.board[r][c-1];
      next.board[r][c-1] = 0;
      next.empty_row = r;
      next.empty_col = c - 1;
      next.num_steps = curr.num_steps + 1;

      if (!is_solved(next)) {
        size_t encoded = serialize(next);
        int seen = 0;
        struct list_node *node = visited.head;
        while (node != NULL) {
          if (node->value == encoded) {
            seen = 1;
            break;
          }
          node = node->next;
        }

        if (!seen) {
          insert_at_head(&visited, encoded);
          enqueue(&q, next);
        }
      }
    }

    //right
    if (c < 3) {
      struct game_state next = curr;
      next.board[r][c] = next.board[r][c+1];
      next.board[r][c+1] = 0;
      next.empty_row = r;
      next.empty_col = c + 1;
      next.num_steps = curr.num_steps + 1;

      if (!is_solved(next)) {
        size_t encoded = serialize(next);
        int seen = 0;
        struct list_node *node = visited.head;
        while (node != NULL) {
          if (node->value == encoded) {
            seen = 1;
            break;
          }
          node = node->next;
        }

        if (!seen) {
          insert_at_head(&visited, encoded);
          enqueue(&q, next);
        }
      }
    }
  }

  //no sol
  free_list(&visited);
  free_list(&q.data);
  return -1;
}