#pragma once

class Grid;

extern Grid* GRID;

// Sets up the grid for use
extern void setup_grid(Grid*);

// Allows the player to interact with a grid cell
extern void g_select(Grid*);

// Finalizes the player's click after interaction
extern void g_unselect(Grid*);

// Makes the grid update when the cursor is moved
extern void g_cursor_updates_grid(Grid*);
