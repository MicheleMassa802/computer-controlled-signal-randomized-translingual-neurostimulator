/*
 * TLNS.c
 *
 * Created: 06.10.2020 21:22:45
 * Author : Ondine
 */ 

#define F_CPU 2000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>


uint16_t previous_k1held = 0;
uint16_t k1held = 0;
uint16_t k2held = 0;
uint8_t intensity = 1; //governs pulse width. 1 = 20us (barely perceptible), 2= 40us (good minimum level), 3 = 60us ("medium"), 4 = ("strong")
uint8_t global_intensity = 8;
uint8_t bit_pattern[11] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};



void setup_pins_and_interrupts(void){
	PORTA_DIR = 0x00;
	PORTA_PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc; //disable digital input buffer on PA7 for ADC use
	//PORTA_PIN7CTRL = PORT_ISC_BOTHEDGES_gc;
	//PORTA_INTCTRL = PORT_INT0LVL_HI_gc;
	//PORTA_INT0MASK = 0x80;
	PORTB_DIR = 0x00;
	PORTC_DIR = 0x00;
	PORTD_DIR = 0x00;
	PORTE_DIR = 0x00;
	PORTF_DIR = 0x00;
	PORTH_DIR = 0x00;
	PORTJ_DIR = 0x00;
	PORTK_DIR = 0x00;
	PORTQ_DIR = 0x02;
	PORTQ_OUT = 0x02;
	//PORTQ_PIN0CTRL = PORT_ISC_BOTHEDGES_gc;
	//PORTQ_INTCTRL = PORT_INT1LVL_HI_gc;
	//PORTQ_INT1MASK = 0x01;
	PORTR_DIR = 0x00;
	//PMIC_CTRL |= PMIC_HILVLEN_bm;
	ADCA_CTRLB = ADC_RESOLUTION_12BIT_gc;           //12-bit right-adjusted unsigned result
	ADCA_REFCTRL = ADC_REFSEL_INT1V_gc;             //internal 1.0V reference
	ADCA_PRESCALER = ADC_PRESCALER_DIV8_gc;         //2MHz / 8 = 250kHz ADC clock
	ADCA_CH0_CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;//single-ended input, no gain
	ADCA_CH0_MUXCTRL = ADC_CH_MUXPOS_PIN7_gc;       //PA7 as positive input
	ADCA_CTRLA = ADC_ENABLE_bm;                     //enable ADCA
}


void write_bit_pattern(void){
	if(global_intensity<5){
		intensity = 1;
	}else if (global_intensity>=5 && global_intensity<9){
		intensity = 2;
	}else if(global_intensity>=9 && global_intensity<13){
		intensity = 3;
	}else{
		intensity = 4;
	}
	
	if(bit_pattern[0] != 0x00){
		PORTA_DIR = 0x7F;
		PORTA_OUT = bit_pattern[0];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTA_OUTTGL = 0x7F;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTA_DIR = 0x00;			
	}else if(bit_pattern[1] != 0x00){
		PORTB_DIR = 0xFF;
		PORTB_OUT = bit_pattern[1];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTB_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTB_DIR = 0x00;
	}else if(bit_pattern[2] != 0x00){
		PORTC_DIR = 0xFF;
		PORTC_OUT = bit_pattern[2];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTC_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTC_DIR = 0x00;
	}else if(bit_pattern[3] != 0x00){
		PORTD_DIR = 0xFF;
		PORTD_OUT = bit_pattern[3];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTD_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTD_DIR = 0x00;
	}else if(bit_pattern[4] != 0x00){
		PORTE_DIR = 0xFF;
		PORTE_OUT = bit_pattern[4];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTE_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTE_DIR = 0x00;
	}else if(bit_pattern[5] != 0x00){
		PORTF_DIR = 0xFF;
		PORTF_OUT = bit_pattern[5];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTF_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTF_DIR = 0x00;
	}else if(bit_pattern[6] != 0x00){
		PORTH_DIR = 0xFF;
		PORTH_OUT = bit_pattern[6];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTH_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTH_DIR = 0x00;
	}else if(bit_pattern[7] != 0x00){
		PORTJ_DIR = 0xFF;
		PORTJ_OUT = bit_pattern[7];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTJ_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTJ_DIR = 0x00;
	}else if(bit_pattern[8] != 0x00){
		PORTK_DIR = 0xFF;
		PORTK_OUT = bit_pattern[8];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTK_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTK_DIR = 0x00;
	}else if(bit_pattern[9] != 0x00){
		PORTQ_DIR = 0xFE;
		PORTQ_OUT = bit_pattern[9];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTQ_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTQ_DIR = 0x02;
		PORTQ_OUTSET = 0x02;
	}else if(bit_pattern[10] != 0x00){
		PORTR_DIR = 0xFF;
		PORTR_OUT = bit_pattern[10];
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTR_OUTTGL = 0xFF;
		for(uint8_t i=0; i<intensity; i++){
			_delay_us(10);
		}
		PORTR_DIR = 0x00;
	}
}


/*
ISR(PORTA_INT0_vect){ //if switch K2 pressed
	k1held = 0;
	k2held = 0;
}

ISR(PORTQ_INT1_vect){ //if switch K1 pressed
	k1held = 0;
	k2held = 0;
}
*/


int main(void){
	setup_pins_and_interrupts();
	while(1){ //main loop
		for(uint8_t i=0;i<11;i++){
			bit_pattern[i] = 0x00; //zero out the whole bit pattern
		}
 	 //set random bit somewhere in the array
		uint8_t whichbyte = 0;
		whichbyte = rand() % 10;
		if(whichbyte == 0){
			bit_pattern[whichbyte] = (0x40 >> (rand() % 7));
		}else if(whichbyte > 0 && whichbyte < 9){
			bit_pattern[whichbyte] = (0x80 >> (rand() % 8));
		}else{//(if whichbyte == 9)
			if(rand() % 2 == 1){
				bit_pattern[rand() % 9] = (0x40 >> (rand() % 7));
			}else{
				if(rand() % 2 == 1){
					bit_pattern[9] = (0x08 >> (rand() % 2));
				}else{
					bit_pattern[10] = (0x02 >> (rand() % 2));
				}
			}
		}

        if((PORTQ_IN & 0x01) == 0){ //if switch K1 pressed
			k1held = 1;
		}else{
			k1held = 0;	
		}

        if(previous_k1held == 0 && k1held == 1){
            write_bit_pattern();
            //delay 1200us - 20*intensity (delay window shrinks as intensity is increased)
		    for(uint8_t i=6;i<(120-6*global_intensity);i++){
			    _delay_us(10);
		    }
        }

        previous_k1held = k1held;

        			
	/*
		if((PORTQ_IN & 0x01) == 0){ //if switch K1 pressed
			k1held++;
			if(k1held%20 == 1 && global_intensity < 20){
				global_intensity++;
			}
		}else{
			k1held = 0;	
		}			
			
		if((PORTA_IN & 0x80) == 0){ //if switch K2 pressed
			k2held++;
			if(k2held%20 == 1 && global_intensity > 1){
				global_intensity--;
			}
		}else{
			k2held = 0;
		}		
	*/
		PORTQ_OUTSET = 0x02;
		ADCA_CH0_CTRL |= ADC_CH_START_bm;                                              //start conversion
		while(!(ADCA_CH0_INTFLAGS & ADC_CH_CHIF_bm));                                  //wait for conversion to complete (~62us)
		ADCA_CH0_INTFLAGS = ADC_CH_CHIF_bm;                                            //clear interrupt flag
		global_intensity = (uint8_t)(((uint32_t)ADCA_CH0_RES * 20) / 4095);           //map 0-4095 to 0-20

	/*
		if(k1held > 600 || k2held > 600){
			global_intensity = 1;
			PORTQ_OUTCLR = 0x02;
			while((PORTQ_IN & 0x01) == 0 || (PORTA_IN & 0x80) == 0){}
			_delay_ms(500);
			sei();
			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_mode();
		}
    */
	}	
}
