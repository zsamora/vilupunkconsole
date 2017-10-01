/*=======================================================
 Arduino Punk Console  
=======================================================*/
// Mapeo de los pins para INPUT y OUTPUT
#define AnalogInTempo 0
#define AnalogInDuration 1
#define AnalogInFrequency 2
#define DigitalInSwitch0 2
#define DigitalInSwitch1 3
#define DigitalInSwitch2 4
#define DigitalInSwitch3 5
#define DigitalInSwitch4 6
#define DigitalInSwitch5 7
#define DigitalInSwitch6 8
#define DigitalInSwitch7 9
#define DigitalOutSignal 10
// Inicializacion del array de frecuencias
int steps[] = {100,120,140,160,180,200,220,240 }; // Setup inicial
int duration = 50;
int pitchval = 1;
int fPlayMode = true;
int lastPushedStep = -1;
// Inicializacion del tempo
int tempo = 900;
void setup() { 
// Seteo de los pines
  pinMode (DigitalInSwitch0, INPUT);
  pinMode (DigitalInSwitch1, INPUT);
  pinMode (DigitalInSwitch2, INPUT);
  pinMode (DigitalInSwitch3, INPUT);
  pinMode (DigitalInSwitch4, INPUT);
  pinMode (DigitalInSwitch5, INPUT);
  pinMode (DigitalInSwitch6, INPUT);
  pinMode (DigitalInSwitch7, INPUT);
  pinMode (DigitalOutSignal, OUTPUT);
  Serial.begin(9600);
} 
void loop() {
// Secuencia principal de loopeo  
for (int i=0; i<8; i++) { // booleano para la reproduccion del sonido
// lectura de botones presionados
    readSwitches();
// lectura de potenciometros (duracion y tempo)
    readPots();
// Si esta encedido
// freqout va a emitir la frecuencia de sonido almacenada en la posicion i
      freqout (steps[i], duration);
// Pausa entre loops
    delay (tempo);
  }
} 
// Lee los valores actuales de los potenciometros de Duracion y de Tempo
void readPots () {  
  tempo = (analogRead (AnalogInTempo) *1.9);
  duration = (analogRead (AnalogInDuration));
}
// Lee el valor actual de los switches (HIGH o LOW).
// Si alguno esta presionado, va a reemplazar en la posicion que le corresponde
// por el valor que lee del potenciometro de frecuencia
void readSwitches() {
  if (digitalRead (DigitalInSwitch0) == HIGH) {
    steps[0] = analogRead(AnalogInFrequency);
    lastPushedStep =1;
  } 
  else if (digitalRead (DigitalInSwitch1) == HIGH) {
  steps[1] = analogRead(AnalogInFrequency);
  lastPushedStep = 2;
  } 
  else if (digitalRead (DigitalInSwitch2) == HIGH) {
    steps[2] = analogRead(AnalogInFrequency);
    lastPushedStep = 3 ;
  }
}
void freqout(int freq, int t) { 
  int hperiod;
  long cycles, i; 
  hperiod = (500000/ ((freq -7) * pitchval));               
  cycles = ((long)freq * (long)t) /1000;    
  for (i=0; i<= cycles; i++) {  
    digitalWrite(DigitalOutSignal, HIGH);
    delayMicroseconds(hperiod); 
    digitalWrite(DigitalOutSignal, LOW);  
    delayMicroseconds(hperiod -1);     
  } 
}
