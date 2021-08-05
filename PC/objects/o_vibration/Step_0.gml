/// @description Press to toggle vibration
if(gamepad_button_check_pressed(0,gp_select))
{
	if(global.vibration==0)global.vibration=1;
	else global.vibration=0;
}
if(global.vibration==0)image_index=0;
else image_index=1;