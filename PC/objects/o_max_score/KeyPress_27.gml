/// @description Ends game
if(room==Gameplay)
{
	o_player.isdead=true;
    if(!instance_exists(o_game_over))instance_create_layer(683,384,"Instances_1",o_game_over)	
}
if(room==Title)game_end();