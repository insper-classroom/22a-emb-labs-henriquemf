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

// Defines para o LAB-2

/*  Default pin configuration (no attribute). */
#define _PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define _PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define _PIO_DEGLITCH            (1u << 1)
/*  The internal debouncing filter is active. */
#define _PIO_DEBOUNCE            (1u << 3)


void _pio_set(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_SODR = ul_mask;
}

void _pio_clear(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}

void _pio_pull_up(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_pull_up_enable){
	p_pio->PIO_PUER = ul_mask;
	p_pio->PIO_PUDR = ul_pull_up_enable;
}

void _pio_set_input(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_attribute){
	
	_pio_pull_up(p_pio, ul_mask, (ul_attribute & _PIO_PULLUP));
	
	if (ul_attribute & (_PIO_DEBOUNCE|_PIO_DEGLITCH)) {
		p_pio -> PIO_IFER = ul_mask;
	} 
	
	else {
		p_pio -> PIO_IFDR = ul_mask;
	}
}

void _pio_set_output(Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_default_level, const uint32_t ul_multidrive_enable, const uint32_t ul_pull_up_enable){
	
	_pio_pull_up(p_pio, ul_mask, ul_pull_up_enable);
	
	if (ul_default_level) {
		_pio_set(p_pio,ul_mask);
	}
	else {
		_pio_clear(p_pio,ul_mask);
	}
	
	
	if (ul_multidrive_enable) {
		p_pio -> PIO_MDER = ul_mask;
	} 
	else { 
		p_pio -> PIO_MDDR = ul_mask;
	}
	
	p_pio->PIO_OER = ul_mask;  
	p_pio->PIO_PER = ul_mask;
}

uint32_t _pio_get(Pio *p_pio, const pio_type_t ul_type, const uint32_t ul_mask) {
	
	uint32_t io_line;
	
	if (ul_type == PIO_OUTPUT_0) {
		io_line = p_pio->PIO_ODSR;
	} 
	else {
		io_line = p_pio->PIO_PDSR;
	}

	if ((io_line & ul_mask) == 0) {
		return 0;
	} 
	else {
		return 1;
	}
}

void _delay_ms(int ms) {
	int i;
	
	for (i = 0; i < ms*145000 ; i++){
		asm("NOP");
	}
}

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

	_pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	_pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
	_pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
	_pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);
	
	//pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_DEFAULT);
	_pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);
	_pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);
	_pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);
	_pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, _PIO_PULLUP | _PIO_DEBOUNCE);
	
	//_pio_pull_up(BUT_PIO, BUT_PIO_IDX_MASK, 1);
	//_pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, 1);
	//_pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, 1);
	//_pio_pull_up(BUT3_PIO, BUT3_PIO_IDX_MASK, 1);
}


 
int main(void)
{
	init();
	
	// SUPER LOOP
	// aplicacoes embarcadas no devem sair do while(1).
	while(1) {
		
		if(!_pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK)) {
			// Pisca LED
			for (int i=0; i<5; i++) {
				_pio_clear(LED_PIO, LED_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
				_pio_set(LED_PIO, LED_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
			}
			
			_pio_set(LED_PIO, LED_PIO_IDX_MASK);
			
		} 
		
		else if(!_pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK)) {
			
			for (int j=0; j<5; j++) {
				_pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
				_pio_set(LED1_PIO, LED1_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
			}
			
			_pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
			
		}
		
		else if(!_pio_get(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK)) {
			
			for (int k=0; k<5; k++) {
				_pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
				_pio_set(LED2_PIO, LED2_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
			}
			
			_pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
			
		}
		
		else if(!_pio_get(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK)) {
			
			for (int x=0; x<5; x++) {
				_pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
				_pio_set(LED3_PIO, LED3_PIO_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				_delay_ms(200);                         // delay
			}
			
			_pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
			
		}
		
	}
	// Nunca devemos chegar aqui !
	return 0;
}
