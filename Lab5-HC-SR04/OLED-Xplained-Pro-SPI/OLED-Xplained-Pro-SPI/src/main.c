#include <asf.h>
#include <time.h>
#include <string.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

// ----------------------- Defines do Botão 1  -----------------------

#define BUT1_PIO					PIOD
#define BUT1_PIO_ID					ID_PIOD
#define BUT1_PIO_IDX				28
#define BUT1_PIO_IDX_MASK			(1u << BUT1_PIO_IDX)

// ----------------------- Defines do sensor  -----------------------

#define TRIG_PIO					PIOA
#define TRIG_PIO_ID					ID_PIOA
#define TRIG_PIO_IDX				3
#define TRIG_PIO_IDX_MASK			(1 << TRIG_PIO_IDX)

#define ECHO_PIO					PIOC
#define ECHO_PIO_ID					ID_PIOC
#define ECHO_PIO_IDX				19
#define ECHO_PIO_IDX_MASK			(1 << ECHO_PIO_IDX)

// ----------------------- Variáveis Globais ------------------------

volatile char echo_flag = 0;
volatile char flag_rtt_alarm = 0;
volatile double freq = (double) 1/(0.000058*2);
volatile int tempo = 0;
volatile char but1_flag = 0;
double distancias_medidas[] = {0.0, 0.0, 0.0, 0.0};


static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource);


// ----------------------- Funções -----------------------

void but1_callback(void) {
	
	but1_flag = 1;
		
}

void echo_callback(void) {
	
	if (pio_get(ECHO_PIO, PIO_INPUT, ECHO_PIO_IDX_MASK)) {
		
		echo_flag = 1;
		RTT_init(freq, 0, 0);
		
	}
	
	else {
		
		echo_flag = 0;
		tempo = rtt_read_timer_value(RTT);
		
	}
}

static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource) {

	uint16_t pllPreScale = (int) (((float) 32768) / freqPrescale);
	
	rtt_sel_source(RTT, false);
	rtt_init(RTT, pllPreScale);
	
	if (rttIRQSource & RTT_MR_ALMIEN) {
		uint32_t ul_previous_time;
		ul_previous_time = rtt_read_timer_value(RTT);
		while (ul_previous_time == rtt_read_timer_value(RTT));
		rtt_write_alarm_time(RTT, IrqNPulses+ul_previous_time);
	}

	/* config NVIC */
	NVIC_DisableIRQ(RTT_IRQn);
	NVIC_ClearPendingIRQ(RTT_IRQn);
	NVIC_SetPriority(RTT_IRQn, 4);
	NVIC_EnableIRQ(RTT_IRQn);

	/* Enable RTT interrupt */
	if (rttIRQSource & (RTT_MR_RTTINCIEN | RTT_MR_ALMIEN))
	rtt_enable_interrupt(RTT, rttIRQSource);
	else
	rtt_disable_interrupt(RTT, RTT_MR_RTTINCIEN | RTT_MR_ALMIEN);
	
}

void RTT_Handler(void) {
	uint32_t ul_status;

	/* Get RTT status - ACK */
	ul_status = rtt_get_status(RTT);

	/* IRQ due to Alarm */
	if ((ul_status & RTT_SR_ALMS) == RTT_SR_ALMS) {
		//RTT_init(4, 0, RTT_MR_RTTINCIEN);
		flag_rtt_alarm = 1;
	}
	
	/* IRQ due to Time has changed */
	if ((ul_status & RTT_SR_RTTINC) == RTT_SR_RTTINC) {

	}

}

static float get_time_rtt() {
	
	uint ul_previous_time = rtt_read_timer_value(RTT);
	
}

void trig(void) {
	
	pio_set(TRIG_PIO, TRIG_PIO_IDX_MASK);
	delay_us(10);
	pio_clear(TRIG_PIO, TRIG_PIO_IDX_MASK);

}

void lcd(float dist_calculada) {
	char string[20];
	char cm[4];
	
	if (flag_rtt_alarm || dist_calculada > 400) {
		gfx_mono_draw_string("            ", 0, 5               n, &sysfont);
			
		sprintf(string, "Erro 404");
		gfx_mono_draw_string(string, 0,0, &sysfont);
		flag_rtt_alarm = 0;
		delay_ms(200);
		
	}
	
	else {
		gfx_mono_draw_string("            ", 0, 0, &sysfont);
		
		sprintf(string, "%.1f", dist_calculada);
		gfx_mono_draw_string(string, 0, 5, &sysfont);
		
	}
	
}

void calcula_distancia() {
	
	int v_som = 340;
	float dist = (float) ((tempo/(freq*2))*v_som)*100;
	
	lcd(dist);
	
}

///////////////////////////////////////////////////////////
//                     INIT                              //
///////////////////////////////////////////////////////////
    
void io_init(void) {
	
	board_init();
	sysclk_init();
	delay_init();
	gfx_mono_ssd1306_init();
	
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(ECHO_PIO_ID);
	pmc_enable_periph_clk(TRIG_PIO_ID);
	
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP|PIO_DEBOUNCE);
	pio_configure(ECHO_PIO, PIO_INPUT, ECHO_PIO_IDX_MASK, PIO_DEBOUNCE);
	
	pio_set_debounce_filter(BUT1_PIO, BUT1_PIO_IDX_MASK, 60);
	pio_set_debounce_filter(ECHO_PIO_IDX, ECHO_PIO_IDX_MASK, 60);
	
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID,  BUT1_PIO_IDX_MASK , PIO_IT_FALL_EDGE, but1_callback);
	pio_handler_set(ECHO_PIO, ECHO_PIO_ID, ECHO_PIO_IDX_MASK , PIO_IT_EDGE, echo_callback);
	
	pio_enable_interrupt(BUT1_PIO,  BUT1_PIO_IDX_MASK);
	pio_enable_interrupt(ECHO_PIO, ECHO_PIO_IDX_MASK);
	
	pio_get_interrupt_status(BUT1_PIO);
	pio_get_interrupt_status(ECHO_PIO);
	
	pio_set_output(TRIG_PIO, TRIG_PIO_IDX_MASK, 0, 0, 0);
	

	NVIC_EnableIRQ(ECHO_PIO_ID);
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(ECHO_PIO_ID, 1);
	NVIC_SetPriority(BUT1_PIO_ID, 2);
}


///////////////////////////////////////////////////////////
//                     MAIN                              //
///////////////////////////////////////////////////////////


int main (void) {
	
	io_init();
	
	while(1) {
		
		if (but1_flag) {
			but1_flag = 0;
			trig();

		}
		
		else if (echo_flag) {
			calcula_distancia();	
		}
		
		
		pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
		
	}
}