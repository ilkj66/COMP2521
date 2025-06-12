// DFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool notOutOfBound (Maze m, struct cell c);

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    int height = MazeHeight(m);
    int width = MazeWidth(m);
    bool **visited = createBoolMatrix(height, width);
    struct cell **pred = createCellMatrix(height, width);
    struct cell start = MazeGetStart(m);
    
    int rowChange[4] = {1, -1, 0, 0};
    int colChange[4] = {0, 0, 1, -1};

    struct cell curr = start;
    Stack s = StackNew();
    StackPush(s, curr);
    bool result = false;
    while (!StackIsEmpty(s)) {
        curr = StackPop(s);
        if (visited[curr.row][curr.col]) continue;

        result = MazeVisit(m, curr);
        visited[curr.row][curr.col] = true;
        if (result) break;

        for (int i = 0; i < 4; i++) {
            struct cell nxt;
            nxt.row = curr.row + rowChange[i];
            nxt.col = curr.col + colChange[i];
            if (notOutOfBound(m, nxt) && !MazeIsWall(m, nxt) && !visited[nxt.row][nxt.col]) {
                pred[nxt.row][nxt.col] = curr;
                StackPush(s, nxt);
            }
        }
    }
    // back tracking
    if (result) {
        while (curr.row != start.row || curr.col != start.col) {
            MazeMarkPath(m, curr);
            curr = pred[curr.row][curr.col];
        }
    }
    freeBoolMatrix(visited);
    freeCellMatrix(pred);
    StackFree(s);
    return result;
}

bool notOutOfBound (Maze m, struct cell c) {
    return (c.row >= 0 && c.row < MazeHeight(m) && c.col >= 0 && c.col < MazeWidth(m));
}

