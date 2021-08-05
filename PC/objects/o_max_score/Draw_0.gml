/// @description Drawing the max score in the titlescreen
if(room==Title){
draw_set_font(BIG);
draw_text_transformed_color(x,y,"Record = ",2,2,0,c_black,c_black,c_black,c_black,1);
draw_text_transformed_color(x+300,y,maxscore,2,2,0,c_black,c_black,c_black,c_black,1);
}