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
  struct queue q = {0};  //in queue
  struct linked_list visited = {0};  //if its visited or not

  //start
  enqueue (&q, start);
  insert_at_head (&visited, serialize (start));

  while (q.data.head != NULL) {
    struct game_state curr = dequeue (&q);

    //if its solved?
    int solved = 1;
    int val = 1;
    for (int r = 0; r < 4 && solved; r++) {
      for (int c = 0; c < 4 && solved; c++) {
        if (r == 3 && c == 3) {
            if (curr.board[r][c] != 0) solved = 0;
        }
        else {
          if (curr.board[r][c] != val) solved = 0;
          val++;
        }
      }
    }
    if (solved) {
      free_list (&visited);
      free_list (&q.data);
      return curr.num_steps;
    }

    //moves
    int r = curr.empty_row;
    int c = curr.empty_col;
    int dr[] = {-1, 1, 0, 0}; //up, down, left, right
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4)
      {
        continue;
      }

      struct game_state next = curr;

      //swapping
      next.board[r][c] = next.board[nr][nc];
      next.board[nr][nc] = 0;
      next.empty_row = nr;
      next.empty_col = nc;
      next.num_steps = curr.num_steps + 1;

      //if seen
      size_t encoded = serialize (next);
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
        insert_at_head (&visited, encoded);
        enqueue (&q, next);
      }
    }
  }

  //no sol
  free_list (&visited);
  free_list (&q.data);
  return -1;
}