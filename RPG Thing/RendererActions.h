#pragma once

class Renderer;

// Makes WASD strafe the camera relative to the renderer's yaww
extern void wasd_strafes_camera(Renderer* r);

// Makes middle mouse button rotate the renderer's yaww
extern void mm_drag_rotates_camera(Renderer* r);

// Makes the scroll wheel move the camera along the yz axis
// - Moves relative to the renderer's yaww
extern void scroll_zooms_camera(Renderer* r);

// Assigns the minimum window size to defaults
extern void set_min_window_size();

// Makes the camera move isometrically
extern void isometric_mount_camera(Renderer* r);

// Set up all camera movement
extern void setup_camera_movement(Renderer* r);
