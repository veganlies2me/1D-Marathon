/// @description Saves score and vibration
ini_open("maxscore.vl2m");
ini_write_real("score","score",maxscore)//save
ini_write_real("vibration","vibration",global.vibration)//load from savefile
ini_close();