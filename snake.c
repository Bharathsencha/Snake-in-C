#include "raylib.h"
#include <stdlib.h>

#define CELL_SIZE 20
#define GRID_WIDTH 25
#define GRID_HEIGHT 25

typedef struct {
    int x, y;
} Vector2Int;

typedef struct {
    Vector2Int body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Vector2Int direction;
} Snake;

void ResetGame(Snake *snake, Vector2Int *food, int *score) {
    snake->length = 1;
    snake->body[0] = (Vector2Int){GRID_WIDTH / 2, GRID_HEIGHT / 2};
    snake->direction = (Vector2Int){1, 0};
    *food = (Vector2Int){rand() % GRID_WIDTH, rand() % GRID_HEIGHT};
    *score = 0;
}

int main(void) {
    InitWindow(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, "Snake Game");
    SetTargetFPS(10); 

    Snake snake;
    Vector2Int food;
    int score = 0;
    ResetGame(&snake, &food, &score);

    while (!WindowShouldClose()) {
        // Handle input
        if (IsKeyPressed(KEY_UP) && snake.direction.y == 0)    snake.direction = (Vector2Int){0, -1};
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y == 0)  snake.direction = (Vector2Int){0, 1};
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x == 0)  snake.direction = (Vector2Int){-1, 0};
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x == 0) snake.direction = (Vector2Int){1, 0};

        // Move snake
        for (int i = snake.length; i > 0; i--) {
            snake.body[i] = snake.body[i - 1];
        }
        snake.body[0].x += snake.direction.x;
        snake.body[0].y += snake.direction.y;

        // Check for collisions
        if (snake.body[0].x < 0 || snake.body[0].x >= GRID_WIDTH ||
            snake.body[0].y < 0 || snake.body[0].y >= GRID_HEIGHT) {
            ResetGame(&snake, &food, &score);
        }
        
        for (int i = 1; i < snake.length; i++) {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
                ResetGame(&snake, &food, &score);
            }
        }

        // Check if food is eaten
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            snake.length++;
            food = (Vector2Int){rand() % GRID_WIDTH, rand() % GRID_HEIGHT};
            score++;
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw snake
        for (int i = 0; i < snake.length; i++) {
            DrawRectangle(snake.body[i].x * CELL_SIZE, snake.body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
        }

        // Draw food
        DrawRectangle(food.x * CELL_SIZE, food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

        // Draw score
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
