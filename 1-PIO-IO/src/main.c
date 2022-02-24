/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

// Defines para o LED da Atmel

#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        ID_PIOC                  // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Defines para o botão da Atmel

#define BUT_PIO           PIOA
#define BUT_PIO_ID		  ID_PIOA
#define BUT_PIO_IDX       11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX) 

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

void init(void){
	// Inicializa clock
	sysclk_init();

	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Ativa PIOs
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	pmc_enable_periph_clk(BUT_PIO_ID);
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);

	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);
	
	pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(BUT_PIO, BUT_PIO_IDX_MASK, 1);
	pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, 1);
	pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, 1);
	pio_pull_up(BUT3_PIO, BUT3_PIO_IDX_MASK, 1);
}


 
int main(void)
{
	init();
	
	// SUPER LOOP
	// aplicacoes embarcadas no devem sair do while(1).
	while(1) {
		
		if(!pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK)) {
			// Pisca LED
			for (int i=0; i<5; i++) {
				pio_clear(LED_PIO, LED_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
				pio_set(LED_PIO, LED_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
			}
			
			pio_set(LED_PIO, LED_PIO_IDX_MASK);
			
		} 
		
		else if(!pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK)) {
			
			for (int j=0; j<5; j++) {
				pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
				pio_set(LED1_PIO, LED1_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
			}
			
			pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
			
		}
		
		else if(!pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)) {
			
			for (int k=0; k<5; k++) {
				pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
				pio_set(LED2_PIO, LED2_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
			}
			
			pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
			
		}
		
		else if(!pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)) {
			
			for (int x=0; x<5; x++) {
				pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
				pio_set(LED3_PIO, LED3_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(200);                         // delay
			}
			
			pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
			
		}
		
	}
	// Nunca devemos chegar aqui !
	return 0;
}
