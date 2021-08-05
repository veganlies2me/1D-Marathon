/// @description Draws d-pad button to help navigating the menu
if(gamepad_is_connected(0))draw_sprite_ext(s_joypad,0,x-139,y+25,1,1,180,c_white,1)