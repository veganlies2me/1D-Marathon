/// @description Gets bigger or smaller
if(point_in_rectangle(mouse_x,mouse_y,x-sprite_width/2,y-sprite_height/2,x+sprite_width/2,y+sprite_height/2)||gamepad_button_check(0,gp_padr))
{
	image_alpha=0.5
	keycheck=1;
}//gets bigger if mouse points at it
else
{
	image_alpha=1
	keycheck=0;
}
if(keycheck==1)
{
 	image_alpha=0.5
	if(gamepad_button_check(0,gp_face1))room_goto(Title);
}//if dpad button is pressed