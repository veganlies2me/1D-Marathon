/// @description Handles the max score and the vibration option in the save file
maxscore=0;
global.vibration=0;
ini_open("maxscore.vl2m");//savefile
maxscore=ini_read_real("score","score",0)
global.vibration=ini_read_real("vibration","vibration",0)//load from savefile
ini_close();