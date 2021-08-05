/// @description Player handling
if(state=0)canjump=true;//state 0 means walking, 1 means jumping
else canjump=false;//while jumping, you can't just jump again
if(isdead=true){
	image_speed=0;
	audio_stop_all();
	if(!instance_exists(o_game_over))instance_create_layer(683,384,"Instances_1",o_game_over);//create prompt once lost
}
if(gamepad_button_check_pressed(0,gp_face1))//controller handles jumping
{
	if(isdead==false){
    if(canjump=true){
    state=1;//jumping
    sprite_index=s_playerjump;
    audio_stop_all();
    audio_play_sound(jump,1,false);
    alarm[0]=70;
}
}
}