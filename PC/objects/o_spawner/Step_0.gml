/// @description Spawning birds and hurdles
alarm[0]=irandom(300);//spawn rate for obstacles
alarm[1]=irandom(800);//spawn rate for birds
if(o_player.isdead=true)instance_destroy();//stop spawning once dead