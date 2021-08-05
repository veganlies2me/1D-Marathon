/// @description Detects controller and if there is one, adds the ability to disable vibration
if(gamepad_is_connected(0))instance_create_layer(975,691,"Instances",o_vibration);