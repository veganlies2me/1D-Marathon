/// @description Gets bigger or smaller
if(point_in_rectangle(mouse_x,mouse_y,x-sprite_width/2,y-sprite_height/2,x+sprite_width/2,y+sprite_height/2)||gamepad_button_check(0,gp_padu))
{
	image_yscale=2.5;
	image_xscale=2.5;
	keycheck=1;
}//gets bigger if mouse points at it
else
{
	image_yscale=2;
	image_xscale=2;
	keycheck=0;
}
if(keycheck==1)
{
 	image_yscale=2.5;
	image_xscale=2.5;
	if(gamepad_button_check(0,gp_face1))room_goto(Gameplay);
}
if(gamepad_button_check(0,gp_start))room_goto(Gameplay);//if dpad button is pressed