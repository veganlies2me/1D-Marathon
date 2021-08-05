/// @description Gets bigger or smaller
if(point_in_rectangle(mouse_x,mouse_y,x-sprite_width/2,y-sprite_height/2,x+sprite_width/2,y+sprite_height/2))
{
	image_yscale=2.5;
	image_xscale=2.5;
}
else
{
	image_yscale=2;
	image_xscale=2;
}
if(gamepad_button_check_pressed(0,gp_face1))room_goto(Title);//if dpad button is pressed
