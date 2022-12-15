/********************************************************************************
* header.h: Inneh�ller diverse definitioner och deklarationer f�r 
*           implementering av det inbyggda systemet.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv: */
#include <avr/io.h>        /* Inneh�ller information om I/O-register s�som PORTB. */
#include <avr/interrupt.h> /* Inneh�ller information om avbrottsvektorer s�som TIMER0_OVF_vect. */

/* Makrodefinitioner: */
#define F_CPU 16000000UL    /* 16 MHz klockfrekvens. */
#define TIMER_PRESCALER 8   /* Divisionfaktor f�r timerkretsarnas uppr�kningsfrekvens. */
#define TIMER_MAX_COUNT 256 /* Alla timerkretsar r�knar upp till 256. */

#define LED1 PORTB0 /* Lysdiod 1 ansluten till pin 8 (PORTB0). */
#define LED2 PORTB1 /* Lysdiod 2 ansluten till pin 9 (PORTB1). */
#define LED3 PORTB2 /* Lysdiod 3 ansluten till pin 10 (PORTB2). */

#define LED1_TOGGLE PINB = (1 << LED1) /* Togglar lysdiod 1. */
#define LED2_TOGGLE PINB = (1 << LED2) /* Togglar lysdiod 2. */
#define LED3_TOGGLE PINB = (1 << LED3) /* Togglar lysdiod 3. */

/********************************************************************************
* timer_interrupt_interval_ms: Returnerar tiden mellan varje timergenererat 
*                              avbrott m�tt i millisekunder, vilket �r 0.128 ms 
*                              vid en klockfrekvens p� 16 MHz, prescaler p� 8 
*                              samt uppr�kning till 256. 
********************************************************************************/
static inline double timer_interrupt_interval_ms(void)
{
   const uint32_t timer_frequency = F_CPU / TIMER_PRESCALER;
   return TIMER_MAX_COUNT / (double)timer_frequency * 1000;
}

/********************************************************************************
* timer_get_max_count: Returnerar antalet timergenererade avbrott som kr�vs
*                      f�r angiven f�rdr�jningstid m�tt i millisekunder. 
*                      Ber�knat v�rde avrundas till n�rmaste heltal.
*
*                      - time_ms: F�rdr�jningstiden m�tt i millisekunder.
********************************************************************************/
static inline uint32_t timer_get_max_count(const double time_ms)
{
   return (uint32_t)(time_ms / timer_interrupt_interval_ms() + 0.5);
}

/********************************************************************************
* setup: Initierar I/O-portar samt timerkretsar.
********************************************************************************/
void setup(void);

#endif /* HEADER_H_ */