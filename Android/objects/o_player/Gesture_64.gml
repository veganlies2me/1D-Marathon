/// @description Jumping
if(isdead==false){
if(canjump=true){
state=1;//jumping
sprite_index=s_playerjump;
audio_stop_all();
audio_play_sound(jump,1,false);
alarm[0]=70;
}
}