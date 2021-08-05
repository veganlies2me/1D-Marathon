/// @description Handles score check and endgame with the gamepade
if(room==Gameplay && gamepad_button_check_pressed(0,gp_start))
{
	o_player.isdead=true;
    if(!instance_exists(o_game_over))instance_create_layer(683,384,"Instances_1",o_game_over)	
}//ends game when start is pressed
if(room==Gameplay)if(o_score.score_-o_score.score_%1>maxscore)maxscore=o_score.score_-o_score.score_%1;//check for highest score