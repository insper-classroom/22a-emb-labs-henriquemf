#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

//-------------------- Defines -----------------------------

// Defines para o Botão 1 da placa do LCD

#define BUT1_PIO                      PIOD
#define BUT1_PIO_ID                   ID_PIOD
#define BUT1_PIO_IDX                  28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

// Defines para o Botão 2 da placa do LCD

#define BUT2_PIO                      PIOC
#define BUT2_PIO_ID                   ID_PIOC
#define BUT2_PIO_IDX                  31
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX)

// Defines para o Botão 3 da placa do LCD

#define BUT3_PIO                      PIOA
#define BUT3_PIO_ID                   ID_PIOA
#define BUT3_PIO_IDX                  19
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)

// Defines para o LED 1 da placa do LCD

#define LED1_PIO                      PIOA
#define LED1_PIO_ID                   ID_PIOA
#define LED1_PIO_IDX                  0
#define LED1_PIO_IDX_MASK (1u << LED1_PIO_IDX)

// Defines para o LED 2 da placa do LCD

#define LED2_PIO                      PIOC
#define LED2_PIO_ID                   ID_PIOC
#define LED2_PIO_IDX                  30
#define LED2_PIO_IDX_MASK (1u << LED2_PIO_IDX)

// Defines para o LED 3 da placa do LCD

#define LED3_PIO                      PIOB
#define LED3_PIO_ID                   ID_PIOB
#define LED3_PIO_IDX                  2
#define LED3_PIO_IDX_MASK (1u << LED3_PIO_IDX)

//------------------------ Flags ----------------------------

volatile char but1Flag;
volatile char but2Flag;
volatile char but3Flag;

// Frequência como variável global

volatile int freq;

// ------------------------- Funções ------------------------

void but1Callback(void)
{
	but1Flag = 1;
}

void but2Callback(void)
{
	but2Flag = 1;
}

void but3Callback(void)
{
	but3Flag = 1;
}

void pisca_led(int n, int t){

	gfx_mono_generic_draw_filled_rect(87, 17, 31, 9, GFX_PIXEL_CLR);
	gfx_mono_generic_draw_rect(86, 16, 32, 10, GFX_PIXEL_SET);
	 
	for (int i=0; i < n; i++) {
		
		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		gfx_mono_generic_draw_vertical_line(86+i, 16, 10, GFX_PIXEL_SET);
		delay_ms(t);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		delay_ms(t);
		
	}
}

void lcdFreq(freq) {
	char f[20];
	sprintf(f, "%d ms", freq);
	gfx_mono_draw_string(f, 5,16, &sysfont);
}


//------------------------ Init -----------------------------

void io_init(void)
{
	
	board_init();
	sysclk_init();
	delay_init();
	
	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Init OLED
	gfx_mono_ssd1306_init();

	// Configura led
	pmc_enable_periph_clk(LED2_PIO_ID);
	pio_configure(LED2_PIO, PIO_OUTPUT_0, LED2_PIO_IDX_MASK, PIO_DEFAULT);
	

	// Inicializa clock do periférico PIO responsavel pelo botao
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);
	

	// Configura PIO para lidar com o pino do botão como entrada com pull-up
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT1_PIO, BUT1_PIO_IDX_MASK, 60);
	
	pio_configure(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT2_PIO, BUT2_PIO_IDX_MASK, 60);
	
	pio_configure(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT3_PIO, BUT3_PIO_IDX_MASK, 60);
	

	// Configura interrupção no pino referente ao botao e associa função de callback caso uma interrupção for gerada a função de callback é a: but_callback()
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but1Callback);
	pio_handler_set(BUT2_PIO, BUT2_PIO_ID, BUT2_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but2Callback);
	pio_handler_set(BUT3_PIO, BUT3_PIO_ID, BUT3_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but3Callback);
	

	// Ativa interrupção e limpa primeira IRQ gerada na ativacao
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT1_PIO);
	
	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT2_PIO);
	
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT3_PIO);
	
	
	// Configura NVIC para receber interrupcoes do PIO do botao com prioridade 4 (quanto mais próximo de 0 maior)
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 4); // Prioridade 4
}

//------------------------------- Main -------------------------

int main (void) {

	io_init();
	
	freq = 100;
	lcdFreq(freq);
	
	int bigNum = 10000000;

	while(1) {
		
		int k;
		
		while (but1Flag || but2Flag || but3Flag) {
			
			  for (k = 0; k < bigNum; k++) {
				  
				  if (but3Flag) {
					  freq += 100;
					  delay_ms(200);
					  lcdFreq(freq);
					  but3Flag = 0;
					  break;
				  }
				  
				  if (but2Flag == 0) {
					  
					  if((!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK)) && k >= bigNum/10) {
						  freq+=100;
						  delay_ms(300);
						  lcdFreq(freq);
						  but1Flag = 0;
						  break;
						} 
						
						else if (pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK) && k < bigNum/10 ) {
						  freq-=100;
						  delay_ms(200);
						  lcdFreq(freq);
						  but1Flag = 0;
						  break;
						}	  
				  }
				  
				  else {
					  delay_ms(200);
					  but2Flag = 0;
					  pisca_led(31, freq);
					  break;
				  }
				  
			  }
			  
			  lcdFreq(freq);
		}

		pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
	}
}


