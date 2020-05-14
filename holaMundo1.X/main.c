// PIC16F886 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f886.h>
#include <stdio.h>

#define _XTAL_FREQ 8000000 //macro para la funci�n de espera (delay())


// Funci�n de configuraci�n de USART
void configurarUsart(void){
    //Registros necesarios
    //1. puerto de comunicaci�n, RX como entrada y TX como salida
    TRISCbits.TRISC6 = 0;//tx
    TRISCbits.TRISC7 = 1;//rx
    //2. generador de tiempo (Baudrate)
    SPBRGH = 0;
    SPBRG = 12; //calculado con la tabla en el datasheet
    //3. habilitar m�dulo (puerto serie)
    RCSTAbits.SPEN = 1; 
    //4. habilitar transmisor (TX)
    TXSTAbits.TXEN = 1; 
    TXIF = 0; //bandera en ceros de transmisi�n
    CREN = 1; //habilita receptor

}

void enviarCaracterTx(char c){
    while(!TRMT){};
    TXREG = c;
}


void enviarString(char * cadenaTexto){
    unsigned int i = 0; //contador de letras
    while(cadenaTexto[i]) //si hay a�n una letra en cola
        enviarCaracterTx(cadenaTexto[i++]); //mandar letra y luego aumentar contador
}


void configADC(){
    //funci�n de configuraci�n del convertidor an�logo a Digital
    //1. puerto de entrada
    TRISAbits.TRISA1 = 1; //pin como entrada
    
    //2. seleccion de canal
    ADCON0bits.CHS = 1; //SELECCIONA EL CANAL 1
    //3. referencias
    ADCON1bits.VCFG1 = 0; //-VREF ES TIERRA (0V)
    ADCON1bits.VCFG0 = 0; //+VREF ES 5V
    //4. reloj de operaci�n
    ADCON0bits.ADCS = 2; //  reloj de conversi�n: Fosc / 32
    //6. formato del resultado
    ADFM = 1;
    //7. habilitar el m�dulo
    ADCON0bits.ADON = 1;    
    
    ANSEL = 3;
}



void main(void) {
    configurarUsart();
    configADC();
    //configuracion inicial
    TRISBbits.TRISB0 = 0; //pin B0 es una salida
    unsigned int lecturaADC = 0;
    char texto[20];
    while(1){
        PORTBbits.RB0 = 1;//salida en alto
        __delay_ms(500);
        RB0  = 0;
        __delay_ms(500);
        enviarString("Tomando una muestra del canal 1\r\n");
        ADCON0bits.GO = 1; //inicia conversi�n
        while(ADCON0bits.GO);
        lecturaADC = (ADRESH << 8) + ADRESL;
        sprintf(texto, "el valor es: %u\r\n", lecturaADC);
        enviarString(texto);
    }
    
    return;
}
