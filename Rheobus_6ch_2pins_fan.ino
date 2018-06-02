int PWM1 = 3;
int PWM2 = 5;
int PWM3 = 6;
int PWM4 = 9;
int PWM5 = 10;
int PWM6 = 11;

int BP = 19;
char etatBP;
char etatBPprec;
char mode = 0;

int LED = 18;

char fStart;

char startLed=0;
char startTime;
char count;

unsigned long temps;
unsigned long temps2;

char etatLed;

void setup() {
pinMode(PWM1, OUTPUT);
pinMode(PWM2, OUTPUT);
pinMode(PWM3, OUTPUT);
pinMode(PWM4, OUTPUT);
pinMode(PWM5, OUTPUT);
pinMode(PWM6, OUTPUT);

pinMode(BP, INPUT_PULLUP);
pinMode(LED, OUTPUT);

etatBPprec=etatBP;
PWM(0,0,0,0,0,0);
fStart=0;

LedStart(); //Visu de mise en route.
  
}

void loop() {
 bouton();
 Mode();
 Led();
}



void PWM(int v1,int v2,int v3,int v4,int v5,int v6){
  analogWrite(PWM1, v1);
  analogWrite(PWM2, v2);
  analogWrite(PWM3, v3);
  analogWrite(PWM4, v4);
  analogWrite(PWM5, v5);
  analogWrite(PWM6, v6);
}

void Mode(){
  //Les valeurs PWM(*,*,*,*,*,*) sont à régler selon le type de ventilateur
  //et la valeur de la resistance précédant le transistor
  if     (mode==0){fStart=0; PWM(0,0,0,0,0,0);}
  else if(mode==1){FanStart();   PWM(70,70,65,65,65,65);}
  else if(mode==2){           PWM(75,75,70,70,70,70);}
  else if(mode==3){           PWM(82,82,80,80,80,80);}
  else if(mode==4){           PWM(255,255,255,255,255,255);}
}

void bouton(){
  etatBP = digitalRead(BP);
  if(etatBP == LOW && etatBP != etatBPprec){
     mode++;
     etatBPprec=etatBP;
     etatLed=0; count=0; startLed=1; startTime=1;
     digitalWrite(LED, LOW);
     if(mode==5){mode=0;}
     }
  if(etatBP == HIGH){ etatBPprec=etatBP; }
}

void Led(){ //Visualisation du mode

  if(startLed==1){

     if(etatLed == 0){ digitalWrite(LED, HIGH);}
     if(etatLed == 1){digitalWrite(LED, LOW);}

    
     if(etatLed == 0){
        if(startTime==1 ){temps=millis(); startTime=2;}
        if( millis()-temps>=800/(mode+1)) {etatLed=1;startTime=2;}
        }
  
     if(etatLed == 1){
        if(startTime==2){temps2=millis();startTime=1;}
        if(millis()-temps2>=800/(mode+1)){etatLed=0;count++;startTime=1;}
        }
  
     if(count>mode){digitalWrite(LED, LOW);startLed=0; count=0;startTime=0;}
     
     }
}

void FanStart(){ //Simule un pic de courant pour démarrer le moteur en mode faible vitesse
  if(fStart==0){
     PWM(255,255,255,255,255,255);
     delay(300); //Augmenter si nécessaire
     fStart=1;
     }
 }
 
void LedStart(){ //Visu de mise en route.
     digitalWrite(LED, HIGH);
     delay(1000);
     digitalWrite(LED, LOW);
 }
 

