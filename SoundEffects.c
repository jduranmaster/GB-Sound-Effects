//*****************************************
//		SoundEffects for GameBoy. 
// Programmed by jduranmaster a.k.a. Ryoga
//*****************************************

#include <gb/gb.h>
#include <gb/drawing.h>

#include "_SFX.h"

UBYTE tile_offset = 1;
UBYTE tile_height = 18;

static const unsigned char TEXT_cEMPTY[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void PRINT_MAIN_SFX_MENU(void);
void PLAY_A_SOUND_EFFECT(void);
void PLAY_B_SOUND_EFFECT(void);
void CLEAR_SCREEN_LINE (UBYTE y);
void CLEAR_SCREEN_BACKGROUND (void);
void PLAY_CURSOR_SOUND_EFFECT(void);
void PLAY_SELECT_SOUND_EFFECT(void);
void INIT_REGISTERS_SOUND_EFECTS(void);
void PRINT_MESSAGE(int x, int y, char *c);
UBYTE PLAY_START_SOUND_EFFECT(UBYTE sfx_two_notes_on);
void PLOT_BACKGROUND_IMAGE(int coord_X, int coord_Y, int tam_tile_X, int tam_tile_Y, unsigned char *tile_data, unsigned char *map_data);

void main(){
	
	UBYTE key_pressed = 0;
	UBYTE sfx_on = 0;
	UBYTE sfx_two_notes_on = 0;
    
	PLOT_BACKGROUND_IMAGE(0, 0, 20, 18, _SFX_tile_data, _SFX_map_data);
	PRINT_MAIN_SFX_MENU();
	INIT_REGISTERS_SOUND_EFECTS();

	while(1){
		key_pressed = joypad();
		
		if( key_pressed & (J_START) && sfx_on == 0){
			PRINT_MESSAGE(9,9,"P ");
			delay(200);
			sfx_on = 1;
			sfx_two_notes_on = PLAY_START_SOUND_EFFECT(sfx_two_notes_on);
		}else{
			PRINT_MESSAGE(9,9,"NP");
		}
		if(sfx_two_notes_on){
			sfx_two_notes_on = PLAY_START_SOUND_EFFECT(sfx_two_notes_on);
		}
		
		if( key_pressed & (J_SELECT) && sfx_on == 0){
			PRINT_MESSAGE(9,10,"P ");
			delay(200);
			PLAY_SELECT_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,10,"NP");
		}

		if( key_pressed & (J_UP) && sfx_on == 0){
			PRINT_MESSAGE(9,5,"P ");
			delay(200);
			PLAY_CURSOR_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,5,"NP");
		}

		if( key_pressed & (J_DOWN) && sfx_on == 0){
			PRINT_MESSAGE(9,6,"P ");
			delay(200);
			PLAY_CURSOR_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,6,"NP");
		}

		if( key_pressed & (J_LEFT) && sfx_on == 0){
			PRINT_MESSAGE(9,7,"P ");
			delay(200);
			PLAY_CURSOR_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,7,"NP");
		}

		if( key_pressed & (J_RIGHT) && sfx_on == 0){
			PRINT_MESSAGE(9,8,"P ");
			delay(200);
			PLAY_CURSOR_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,8,"NP");
		}

		if( key_pressed & (J_A) && sfx_on == 0){
			PRINT_MESSAGE(9,11,"P ");
			delay(200);
			PLAY_A_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,11,"NP");
		}

		if( key_pressed & (J_B) && sfx_on == 0){
			PRINT_MESSAGE(9,12,"P ");
			delay(200);
			PLAY_B_SOUND_EFFECT();
			sfx_on = 1;
		}else{
			PRINT_MESSAGE(9,12,"NP");
		}

		if( !( key_pressed & J_SELECT ) && !( key_pressed & J_A ) && !( key_pressed & J_START ) && !( key_pressed & J_B )
			&& !( key_pressed & J_UP ) && !( key_pressed & J_DOWN ) && !( key_pressed & J_RIGHT ) && !( key_pressed & J_LEFT ) && sfx_on == 1 ){
			sfx_on = 0;
		}
	}
}

void PRINT_MAIN_SFX_MENU(void){
	PRINT_MESSAGE(1, 1, "----------------");
	PRINT_MESSAGE(1, 2, "SFX FOR GAMEBOY");
	PRINT_MESSAGE(1, 3, "----------------");
	PRINT_MESSAGE(1, 5,"Up    : NP");
	PRINT_MESSAGE(1, 6,"Down  : NP");
	PRINT_MESSAGE(1, 7,"Left  : NP");
	PRINT_MESSAGE(1, 8,"Right : NP");
	PRINT_MESSAGE(1, 9,"Start : NP");
	PRINT_MESSAGE(1, 10,"Select: NP");
	PRINT_MESSAGE(1, 11,"A     : NP");
	PRINT_MESSAGE(1, 12,"B     : NP");
	PRINT_MESSAGE(1, 14, "----------------");
	PRINT_MESSAGE(4, 15, "RYOGA 2014");
	PRINT_MESSAGE(1, 16, "----------------");
}

void INIT_REGISTERS_SOUND_EFECTS(void){
	NR52_REG = 0xF8U;
	NR51_REG = 0x00U;
	NR50_REG = 0x77U;
}

void PLAY_A_SOUND_EFFECT(void){
	NR10_REG = 0x34U;
	NR11_REG = 0x70U;
	NR12_REG = 0xF0U;
	NR13_REG = 0x0AU;
	NR14_REG = 0xC6U;
	NR51_REG |= 0x11;
}

void PLAY_B_SOUND_EFFECT(void){
	NR10_REG = 0x34U;
	NR11_REG = 0x80U;
	NR12_REG = 0xF0U;
	NR13_REG = 0x0AU;
	NR14_REG = 0xC6U;
	NR51_REG |= 0x11;
}

void PLAY_SELECT_SOUND_EFFECT(void){
	NR10_REG = 0x04U;
	NR11_REG = 0xFEU;
	NR12_REG = 0xA1U;
	NR13_REG = 0x8FU;
	NR14_REG = 0x86U;
	NR51_REG = 0xF7;
}

UBYTE PLAY_START_SOUND_EFFECT(UBYTE sfx_two_notes_on){
	if( NR52_REG & 0x02 ){
		return 0x01;
	}else if( sfx_two_notes_on ){
		//segunda nota
		NR21_REG = 0x80U;
		NR22_REG = 0x73U;
		NR23_REG = 0x9FU;
		NR24_REG = 0xC7U;
		NR51_REG |= 0x22;
		return 0x00;
	}else{
		// primera nota.
		NR21_REG = 0xAEU;
		NR22_REG = 0x68U;
		NR23_REG = 0xDBU;
		NR24_REG = 0xC7U;
		NR51_REG |= 0x22;
		return 0x01;
	}
}

void PLAY_CURSOR_SOUND_EFFECT(void){
	NR10_REG = 0x38U;
	NR11_REG = 0x70U;
	NR12_REG = 0xE0U;
	NR13_REG = 0x0AU;
	NR14_REG = 0xC6U;
	NR51_REG |= 0x11;
}

void PRINT_MESSAGE(int x, int y, char *c){
	gotogxy(x,y);
	gprintf(c);
}

void CLEAR_SCREEN_LINE ( UBYTE y ){
	UBYTE x;
	for (x = y*20 ; x < (y+1)*20 ; x++ ){
		set_bkg_data (x+tile_offset,1,(unsigned char *)TEXT_cEMPTY);
	}
}

void CLEAR_SCREEN_BACKGROUND(void){
	UBYTE x;
	for ( x = 0 ; x < tile_height ; x++ ){
		CLEAR_SCREEN_LINE ( x );
	}
}

void PLOT_BACKGROUND_IMAGE(int coord_X, int coord_Y, int tam_tile_X, int tam_tile_Y, unsigned char *tile_data, unsigned char *map_data){
	set_bkg_data(coord_X, coord_Y, tile_data);
	set_bkg_tiles(coord_X, coord_Y, tam_tile_X, tam_tile_Y, map_data);
	SHOW_BKG;
	DISPLAY_ON;
	delay(2000);
}