// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
//1. registros de configuración 
#define _XTAL_FREQ 8000000 //PARA LAS RUTINAS DE DEMORA

//2. programa principal 
void main(void) {
    //Habilitamos un puerto de salida
    TRISBbits.TRISB0 = 0;//salida
    TRISBbits.TRISB1 = 1; //entrada
    TRISBbits.TRISB4 = 0; //salida
    int auxiliar;
    
    while(1){//siempre debe haber un ciclo principal
        //ahora leyendo una entrada y negandola en la salida
        PORTBbits.RB0 = 1;//alto
        __delay_ms(500);
        RB0 = 0;
        __delay_ms(500);
        auxiliar = RB1;
        RB4 = auxiliar; //LEE BIT EN RB1 Y LO PONE EN B4
        
        
        
    }
    
    return;
}
