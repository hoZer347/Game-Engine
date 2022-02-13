#pragma once

// Sets up the grid for use
extern void setup_grid();

// Allows the player to interact with a grid cell
extern void grid_select();

// Finalizes the player's click after interaction
extern void grid_unselect();

// Makes the grid update when the cursor is moved
extern void cursor_updates_grid();
