/// @description Draws d-pad button to help navigating the menu
if(gamepad_is_connected(0))draw_sprite_ext(s_joypad,0,x-190,y+35,1,1,90,c_white,1)