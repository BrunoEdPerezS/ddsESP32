//Codigo de prueba para DDS 
 #include "wavetables.h"
//Definiciones----------------------------------
#define BUTTON 33
hw_timer_t *My_timer = NULL;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile int count =0; 
unsigned long buttonTIME = 0;  
unsigned long lastBTIME = 0; 

   //Variables para el dds
uint32_t f = 5000;
uint32_t M = f*(pow(2,32))/100000;

   //contadores
uint32_t acumuladorFASE = 0x00000000;
uint8_t  addressPOINTER = 0x00;

//escribir la ISR del DSS----------------------------
void IRAM_ATTR onTimer(){
acumuladorFASE = acumuladorFASE + M;
addressPOINTER = acumuladorFASE >> 24; //Shiftear los bits


// Condiciones para el cambio de onda
if (count ==0)
{
   dacWrite(25, SINE[addressPOINTER]);
}
if (count ==1)
{
   dacWrite(25, SAW[addressPOINTER]);
}
if (count ==2)
{
   dacWrite(25, TRIANGLE[addressPOINTER]);
}
if (count ==3)
{
   dacWrite(25, SQUARE[addressPOINTER]);
}
}

//ISR del selector
void IRAM_ATTR selector(){
   buttonTIME = millis();
//Condicion para el debounce
if (buttonTIME - lastBTIME > 250)
{
   //Aumento del contador
   if (count == 3) {
      count = 0;
   }
   else {
      count = count + 1;
   }

lastBTIME = buttonTIME;
 }
}


void setup() {

//setup del timer a 100 kHz

My_timer = timerBegin(0, 80, true);
timerAttachInterrupt(My_timer, &onTimer, true);
timerAlarmWrite(My_timer,10, true);
timerAlarmEnable(My_timer); 


//interrupcion para el el switcheo
pinMode(BUTTON, INPUT_PULLDOWN);
attachInterrupt(BUTTON, selector, FALLING);
}

void loop() {
    //No hay nada corriendo en el loop
}