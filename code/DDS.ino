//Codigo de prueba para DDS 
 #include "wavetables.h"
//Definiciones----------------------------------
#define LED 26
#define BUTTON 33
hw_timer_t *My_timer = NULL;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile int count =0; 
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

   //Variables para el dds
uint32_t f = 5000;
uint32_t M = f*(pow(2,32))/100000; //44100 sample rate
   //contadores
uint32_t phase_accumulator = 0x00000000;
uint8_t  address_pointer = 0x00;
volatile bool trigger = false;

//escribir la ISR del DSS----------------------------
void IRAM_ATTR onTimer(){
digitalWrite(LED, !digitalRead(LED));
phase_accumulator = phase_accumulator + M;
address_pointer = phase_accumulator >> 24; // shift 22 bit
if (count ==0)
{
   dacWrite(25, SINE[address_pointer]);
}
if (count ==1)
{
   dacWrite(25, SAW[address_pointer]);
}
if (count ==2)
{
   dacWrite(25, TRIANGLE[address_pointer]);
}
if (count ==3)
{
   dacWrite(25, SQUARE[address_pointer]);
}
trigger = true;
}

//ISR del selector
void IRAM_ATTR selector(){

   button_time = millis();
   if (button_time - last_button_time > 250)
{

   if (count == 3) {
      count = 0;
   }
   else {
      count = count + 1;
   }
last_button_time = button_time;
 }
}


void setup() {
//setup del timer a 100 kHz
pinMode(LED, OUTPUT);
pinMode(BUTTON, INPUT_PULLDOWN);
My_timer = timerBegin(0, 80, true);
timerAttachInterrupt(My_timer, &onTimer, true);
timerAlarmWrite(My_timer,10, true);
timerAlarmEnable(My_timer); 
//Serial.begin(115200);

//interrupcion para el el switcheo
attachInterrupt(BUTTON, selector, FALLING);
}

void loop() {
}