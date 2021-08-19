/// @description Handles the max score and the vibration option in the save file
maxscore=0;
ini_open("maxscore.vl2m");//savefile
maxscore=ini_read_real("score","score",0)
ini_close();