/// @description Creates retry and return buttons
image_xscale=4;
image_yscale=4;
instance_create_layer(500,550,"Instances_2",o_retry);
instance_create_layer(1060,550,"Instances_2",o_return);
ini_open("maxscore.vl2m");//savefile
if(o_score.score_ - o_score.score_%1>o_maxscore.maxscore)
{
	o_maxscore.maxscore=o_score.score_ - o_score.score_%1
	ini_write_real("score","score",o_maxscore.maxscore)//load from savefile
}
ini_close();