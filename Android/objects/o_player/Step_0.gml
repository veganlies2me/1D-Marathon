/// @description Player handling
if(state=0)canjump=true;
else canjump=false;//while jumping, you can't just jump again
if(isdead=true){
	image_speed=0;
	audio_stop_all();
	instance_destroy(o_endgame)
	if(!instance_exists(o_gameover))instance_create_layer(783,384,"Instances_1",o_gameover);//create prompt once lost
}