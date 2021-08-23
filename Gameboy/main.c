#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
#include <time.h>
#include "title_map.c"
#include "title_tiles.c"
#include "playersprite.c"
#include "arrowsprite.c"
#include "hurdlesprite.c"
#include "birdsprite.c"
#include <gb/font.h>
#include <gb/console.h>

uint16_t seed;//seed for random

uint8_t arrowpos;

//score
UINT16 score;
extern UINT16 maxscore;
extern void init_sram();

UINT8 playerspriteindex;
UINT8 animationcount;
UINT8 jumpanimationcount;
//frames for player

UINT8 isjump;//jumping? 0 means not,1 means yes

UINT8 sounddelay;

UINT8 birdspriteindex;
UINT8 birdmove;
UINT8 birdismoving;
UINT8 birdappear;
UINT8 birdanimationcount;
//bird

UINT8 hurdlemove;
UINT8 hurdleismoving;
UINT8 hurdleappear;
//hurdle

UINT8 gamestate;

//font stuff
const unsigned char font[]={1,38,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
	0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,
    0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,
	0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x30,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};const
//assigning the tiles ascii values
#include "font.c"
font_t mainfont;

UINT8 press;//is a button pressed?

void altdelay(UINT8 x)//alternative delay
{
    UINT8 i;
    for(i=1;i<=x;i++)wait_vbl_done();
}

uint8_t last_keys, cur_keys , new_keys ,rel_keys;

void update_input()
{
    last_keys = cur_keys;
    cur_keys = joypad();
    new_keys = ~last_keys & cur_keys;
    rel_keys = last_keys & ~cur_keys;
}//input function, thank you Eievui

void titleinit() //initializing the titlescreen ... no pun here
{
    set_sprite_data(0,3,Arrow);
    set_sprite_tile(0,0);
    set_bkg_data(0,81,title_tiles);
    set_bkg_tiles(0,0,20,18,title_map);
    SHOW_BKG;
    DISPLAY_ON;
    SHOW_SPRITES;
}

void gameinit()    //initializing the gameplay ... it's game day innit?
{
    seed = DIV_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
    HIDE_BKG;
    score=0;
    HIDE_SPRITES;
    //initializing font
    font_init();
    mainfont=font_load(font);
    font_set(mainfont);
    //turning on sound
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
    //hurdle
    set_sprite_data(2,1,Hurdle);
    set_sprite_tile(2,0);
    hurdlemove=0;
    hurdleismoving=0;
    hurdleappear=0;
    move_sprite(2,86,hurdlemove);
    //bird
    set_sprite_data(3,2,Bird);
    set_sprite_data(4,2,Bird);
    set_sprite_tile(3,0);
    set_sprite_tile(4,0);
    birdmove=0;
    birdismoving=0;
    birdappear=0;
    birdanimationcount=0;
    birdspriteindex=0;
    move_sprite(3,86,birdmove);
    move_sprite(4,86,birdmove+8);
    set_sprite_prop(4,S_FLIPY);
    //player
    playerspriteindex=0;
    isjump=0;
    set_sprite_data(0,3,Player);
    set_sprite_data(1,3,Player);
    set_sprite_tile(0,0);
    set_sprite_tile(1,0);
    move_sprite(0,86,133);
    move_sprite(1,86,141);
    set_sprite_prop(1,S_FLIPY);
    SHOW_SPRITES;
    animationcount=0;
    sounddelay=0;
    jumpanimationcount=0;
    press=0;
    init_sram();
    gamestate=2;
}

void goinnit() //game over initialization ... it's go time , innit?
{
    HIDE_BKG;
    HIDE_SPRITES;
    arrowpos=0;
    font_init();
    mainfont=font_load(font);
    font_set(mainfont);
    ENABLE_RAM_MBC1;
    printf("\n\n     GAME OVER\n");
    printf("\n\n SCORE %u ",(score/10));
    if((score/10)>maxscore)maxscore=score/10;
    printf("\n MAX SCORE %u",maxscore);
    printf("\n\n\n\n   RETRY");
    printf("\n   RETURN");
    DISABLE_RAM_MBC1;
    press=0;
    gamestate=3;
}

void main()
{
    press=0;
    arrowpos=0; 
    gamestate=0;
    titleinit();
    while(1)
    {
        switch(gamestate){
            case 0: //titlescreen
            update_input();
            altdelay(5);
            if(joypad()==J_SELECT || joypad()==J_UP || joypad()==J_DOWN){
                if(press!=1)
                { press=1;
                arrowpos++;
                    arrowpos=arrowpos%2;
                }
                else if (press==1){
                }
            }
            else press=0;//handling presses
            if(arrowpos==0)move_sprite(0,65,60);
            else move_sprite(0,65,80);
            if((new_keys & J_A || new_keys & J_START) && arrowpos==0)gameinit(); 
            if((new_keys & J_A || new_keys & J_START) && arrowpos!=0)
                {
                    HIDE_BKG;
                    HIDE_SPRITES;
                    gamestate=1;
                    //initializing the info screen 
                    init_sram();
                    font_init();
                    mainfont=font_load(font);
                    font_set(mainfont);
                    ENABLE_RAM_MBC1;
                    printf("THIS IS YOU\n");
                    printf("\nTHIS IS A HURDLE\n");
                    printf("JUMP OVER IT\n");
                    printf("\nTHIS IS A BIRD\n");
                    printf("DO NOT JUMP\n");
                    printf("\nFONT MADE BY STYLE 7\n");
                    printf("GAME BY VL2M STUDIO\n");
                    printf("SPECIAL THANKS TO\n");
                    printf("CABBAGE AND GBDEV\n");
                    printf("\nMAX SCORE %u\n\n",maxscore);
                    printf("PRESS B TO RETURN");
                    DISABLE_RAM_MBC1;
                    //hurdle
                    set_sprite_data(2,1,Hurdle);
                    set_sprite_tile(2,0);
                    move_sprite(2,150,40);
                    //bird
                    set_sprite_data(3,2,Bird);
                    set_sprite_data(4,2,Bird);
                    set_sprite_tile(3,4);
                    set_sprite_tile(4,4);
                    move_sprite(3,140,58);
                    move_sprite(4,140,66);
                    set_sprite_prop(4,S_FLIPY);
                    birdspriteindex=4;
                    //player
                    set_sprite_data(0,2,Player);
                    set_sprite_data(1,2,Player);
                    set_sprite_tile(0,0);
                    set_sprite_tile(1,0);
                    move_sprite(0,120,15);
                    move_sprite(1,120,23);
                    set_sprite_prop(1,S_FLIPY);
                    playerspriteindex=1;
                    SHOW_SPRITES;
                }
            break;
            case 1: //info
                if(playerspriteindex==1)playerspriteindex=2;
                else playerspriteindex=1;
                if(birdspriteindex==4)birdspriteindex=5;
                else birdspriteindex=4;
                altdelay(10);//delaying animations
                set_sprite_tile(0,playerspriteindex);
                set_sprite_tile(1,playerspriteindex);
                set_sprite_prop(1,S_FLIPY);
                set_sprite_tile(3,birdspriteindex);
                set_sprite_tile(4,birdspriteindex);
                set_sprite_prop(4,S_FLIPY);
                if(joypad() == J_B)
                {
                    HIDE_BKG;
                    HIDE_SPRITES;
                    //getting rid of sprites that we do not need , a very bad way to do it, didn't know there was a function that actually hides them back when I was developing this
                    move_sprite(0,160,160);
                    move_sprite(1,160,160);
                    move_sprite(2,160,160);
                    move_sprite(3,160,160);
                    move_sprite(4,160,160);
                    titleinit();
                    gamestate=0;
                }
            break;
            case 2: //gameplay
            gotoxy(0,0);
            printf("%u",(score/10));
            update_input();
            //player moving process
            animationcount++;
            if (cur_keys == J_A) {
                if (press != 1) {
                    if (isjump != 1) {
                        //jump sound
                        NR10_REG = 0x64; 
                        NR11_REG = 0x7F; 
                        NR12_REG = 0xC4; 
                        NR13_REG = 0x96;
                        NR14_REG = 0x80; 
                    } //only to play once
                    isjump = 1; // is jumping
                    press = 1;
                }
            } else
                press = 0;
            if (animationcount > 5)
                animationcount = 1;
            playerspriteindex = animationcount >> 1u;
            if (isjump != 0) {
                jumpanimationcount++;
                playerspriteindex = 3;
            }
            if (jumpanimationcount == 18) {
                isjump = 0;
                jumpanimationcount = 0;
            }
            if(isjump==0) {
                sounddelay++;
                sounddelay %= 2;
                //walk sound
                if (sounddelay == 0) {
                    NR41_REG = 0x00; 
                    NR42_REG = 0x61;
                    NR43_REG = 0x99; 
                    NR44_REG = 0x80;
                }
            }
            set_sprite_tile(0,playerspriteindex);
            set_sprite_tile(1,playerspriteindex);
            set_sprite_prop(1,S_FLIPY);
            altdelay(5);
            //hurdle moving process
            if(hurdlemove==160)hurdleismoving=0;
            if(hurdleismoving==0)hurdleappear=(rand()%5)+1;
            if(hurdleappear==1)hurdleismoving=1;
            if(hurdleismoving==1)
            {
                move_sprite(2,86,hurdlemove);
                if ((score / 10) < 50)
                    hurdlemove += 3;
                if ((score / 10) > 50 && (score / 10) < 100)
                    hurdlemove += 4;
                if ((score / 10) > 100 && (score / 10) < 200)
                    hurdlemove += 5;
                if ((score / 10) > 200 && (score / 10) < 500)
                    hurdlemove += 7;
                if ((score / 10) > 500)
                    hurdlemove += 11;
                if (!(hurdlemove == 96 && !birdismoving))
                    hurdlemove -= 1;
                //an attempt to avoid impossible combos
            }
            //bird moving process
            birdanimationcount++;
            if(birdanimationcount>5)birdanimationcount=1;
            birdspriteindex=birdanimationcount/2 + 4;
            if(birdspriteindex==6)birdspriteindex=4;
            if(birdmove==175)birdismoving=0;
            if(hurdleismoving==0)birdappear=(rand()%5)+1;
            if(birdappear==1)birdismoving=1;
            if(birdismoving==1)
            {
                move_sprite(3, 86, birdmove);
                move_sprite(4, 86, birdmove+8);
                if ((score / 10) < 50)
                    birdmove += 7;
                if ((score / 10) > 50 && (score / 10) < 100)
                    birdmove += 8;
                if ((score / 10) > 100 && (score / 10) < 200)
                    birdmove += 9;
                if ((score / 10) > 200 && (score / 10) < 500)
                    birdmove += 11;
                if ((score / 10) > 500)
                    birdmove += 15;
                if (!(birdmove + 8 == 96 && !hurdleismoving))
                    birdmove -= 2;
                //an attempt to avoid impossible combos
            }
            set_sprite_tile(3,birdspriteindex);
            set_sprite_tile(4,birdspriteindex);
            set_sprite_prop(4,S_FLIPY);
            //handling collision detection
            if((hurdlemove>=133 && hurdlemove<=144)&&isjump==0)
            {
                goinnit();
            }
            if((birdmove>=133 && birdmove<=144)&&isjump==1)
            {
                goinnit();
            }
            if((birdmove+8>=133 && birdmove+8<=144)&&isjump==1)
            {
                goinnit();
            }
            if(new_keys  & J_START)
                if (press != 1) {
                        goinnit();
                        press = 1;
                    }
                else
                    press = 0;
            score++;
            break;
            //game over
            case 3:
            altdelay(5);
            set_sprite_data(0,3,Arrow);
            set_sprite_tile(0,0);
            move_sprite(1,160,160);
            move_sprite(2,160,160);
            move_sprite(3,160,160);
            move_sprite(4,160,160);
            SHOW_SPRITES;
            update_input();
            if(joypad()==J_SELECT || joypad()==J_UP || joypad()==J_DOWN){
                    if(press!=1)
                    { press=1;
                    arrowpos++;
                        arrowpos=arrowpos%2;
                    }
                    else if (press==1){
                    }
                }
            else press=0;
            if(arrowpos==0)move_sprite(0,20,95);
            if(arrowpos!=0) move_sprite(0,20,105);
            if ((new_keys & J_A || new_keys & J_START) && arrowpos==0)gameinit();
            if((new_keys & J_A || new_keys & J_START) && arrowpos!=0)
            {
                HIDE_SPRITES;
                HIDE_BKG;
                arrowpos=0;
                titleinit();
                gamestate=0;
            }
            break;
        }
    }
}
