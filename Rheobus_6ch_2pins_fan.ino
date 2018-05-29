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

char swStart;

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
swStart=0;

LedStart(); //Visu de mise en route. Peut etre supprimé.
  
}

void loop() {
  
 Mode();
 
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
  bouton();
  //Les valeurs PWM(*,*,*,*,*,*) sont à régler selon le type de ventilateur
  //et la valeur de la resistance précédant le transistor
  if(mode==0){swStart=0; PWM(0,0,0,0,0,0);}
  else if(mode==1){start(); PWM(70,70,65,65,65,65);}
  else if(mode==2){         PWM(75,75,70,70,70,70);}
  else if(mode==3){         PWM(82,82,80,80,80,80);}
  else if(mode==4){         PWM(255,255,255,255,255,255);}
}

void bouton(){
  etatBP = digitalRead(BP);
  if(etatBP == LOW && etatBP != etatBPprec){
     mode++;
     if(mode==5){mode=0;}
     etatBPprec=etatBP;
     Led();
     }
  if(etatBP == HIGH){ etatBPprec=etatBP; }
}

void Led(){ //Visualisation du mode
  for(int i=0; i<mode+1;i++){
     digitalWrite(LED, HIGH);
     delay(600/(mode+1));
     digitalWrite(LED, LOW);
     if(mode!=0){delay(600/(mode+1));}
     }
}

void start(){ //Simule un pic de courant pour démarrer le moteur
  if(swStart==0){
     PWM(255,255,255,255,255,255);
     delay(300);
     swStart=1;
     }
 }
 
void LedStart(){ //Visu de mise en route. Peut etre supprimé.
  for(int i=1; i<10;i++){
     digitalWrite(LED, HIGH);
     delay(100/(i+1));
     digitalWrite(LED, LOW);
     delay(100/(i+1));
     }
 }
 

