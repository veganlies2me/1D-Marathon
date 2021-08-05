/// @description Creates retry and return buttons, vibrates if the vibration option is on
image_xscale=3;
image_yscale=3;
instance_create_layer(500,500,"Instances_2",o_retry);
instance_create_layer(860,500,"Instances_2",o_return);
if(global.vibration==0){gamepad_set_vibration(0,1,1);
alarm[0]=20;
}
ini_open("maxscore.vl2m");//savefile
ini_write_real("vibration","vibration",global.vibration)//load from savefile data about vibration
ini_close();