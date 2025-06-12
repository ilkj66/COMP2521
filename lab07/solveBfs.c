// BFS maze solver

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"

bool notOutOfBound (Maze m, struct cell c);

bool solve(Maze m) {
    int height = MazeHeight(m);
    int width = MazeWidth(m);
    struct cell **pred = createCellMatrix(height, width);
    bool **visited = createBoolMatrix(height, width);
    Queue q = QueueNew();
    // array to change the cell position
    int rowChange[4] = {1, -1, 0, 0};
    int colChange[4] = {0, 0, 1, -1};

    struct cell start = MazeGetStart(m);
    QueueEnqueue(q, start); // Enqueue the start
    struct cell curr = start;

    while (!QueueIsEmpty(q)) {
        curr = QueueDequeue(q);
        if (MazeVisit(m, curr)) { // check if arrived at the exit
            break;
        }
        for (int i = 0; i < 4; i++) {
            struct cell nxt;
            // check neighbour cells
            nxt.row = curr.row + rowChange[i];
            nxt.col = curr.col + colChange[i];
            if (notOutOfBound(m, nxt) && !MazeIsWall(m, nxt) && !visited[nxt.row][nxt.col]) { // check the cell is valid and not visited
                pred[nxt.row][nxt.col] = curr;
                visited[nxt.row][nxt.col] = true;
                QueueEnqueue(q, nxt);
            }
        }
    }
    // back tracking, mark path
    bool result = MazeVisit(m, curr);
    if (result) {
        while (curr.row != start.row || curr.col != start.col) {
            MazeMarkPath(m, curr);
            curr = pred[curr.row][curr.col];
        }
    }

    QueueFree(q);
    freeCellMatrix(pred);
    freeBoolMatrix(visited);
    return result;

}

bool notOutOfBound (Maze m, struct cell c) {
    return (c.row >= 0 && c.row < MazeHeight(m) && c.col >= 0 && c.col < MazeWidth(m));
}