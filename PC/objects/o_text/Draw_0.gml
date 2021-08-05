/// @description Draws text
draw_set_font(BIG);
if(room=Title){draw_text_transformed_color(x,y,"   1D  ",3,3,0,c_black,c_black,c_black,c_black,100);
draw_text_transformed_color(x,y+50,"MARATHON",3,3,0,c_black,c_black,c_black,c_black,100);
}
if(room=Info)draw_text_transformed_color(x,y,"Credits-Font: Style 7",2,2,0,c_black,c_black,c_black,c_black,100);