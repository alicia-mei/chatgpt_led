#include <stdio.h>

#define SIM_SCGC5_PORTD (1 << 12) // Habilita o clock do PORTD
#define LED_BLUE (1 << 1) // Define o pino do LED azul (PTD1)

void delay(volatile unsigned int count) {
    while (count--) {
        __asm("nop"); // NOP para gerar atraso
    }
}

int main(void) {
    // Habilita o clock do PORTD
    *((volatile unsigned int *)0x40048038) |= SIM_SCGC5_PORTD; // SIM->SCGC5

    // Configura o pino PTD1 como saída
    *((volatile unsigned int *)0x4004C004) |= (1 << 8); // PORTD->PCR[1]
    *((volatile unsigned int *)0x400FF0D4) |= LED_BLUE; // PTD->PDDR

    printf("Piscar LED azul...\n");

    while (1) {
        // Acende o LED azul
        *((volatile unsigned int *)0x400FF0C4) |= LED_BLUE; // PTD->PSOR
        delay(48000000); // Atraso para 1 segundo

        // Apaga o LED azul
        *((volatile unsigned int *)0x400FF0C8) |= LED_BLUE; // PTD->PCOR
        delay(48000000); // Atraso para 1 segundo
    }

    return 0;
}
