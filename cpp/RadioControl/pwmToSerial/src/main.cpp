#include <Arduino.h>
#define FBWARDSPEED_PIN A0
#define LRSPEED_PIN A1
#define ANGULARVELOCITY_PIN A3
#define MAXSPEED_PIN A2

#define validArea 7

int fbspeed=0;
int lrspeed=0;
int angular=0;
int maxVelocity=0;
int lastfbspeed=0;
int lastlrspeed=0;
int lastangular=0;
int lastmaxVelocity=0;

float lxspeed=0;
float lyspeed=0;
float angularspeed=0;
float maxspeed=0;

int maxValue[]={1000,2000};

void setup() {
    pinMode(FBWARDSPEED_PIN,INPUT);
    pinMode(LRSPEED_PIN,INPUT);
    pinMode(ANGULARVELOCITY_PIN, INPUT);
    pinMode(MAXSPEED_PIN, INPUT);
    Serial.begin(9600);
}


void loop() {

    fbspeed=pulseIn(FBWARDSPEED_PIN,HIGH);
    lrspeed=pulseIn(LRSPEED_PIN,HIGH);
    angular=pulseIn(ANGULARVELOCITY_PIN,HIGH);
    maxVelocity=pulseIn(MAXSPEED_PIN,HIGH);


    if(abs(lastfbspeed-fbspeed)>validArea){
      lastfbspeed=fbspeed;
      lxspeed=float(fbspeed-maxValue[0])/(maxValue[1]-maxValue[0])*2-1;
    }
    if(abs(lastlrspeed-lrspeed)>validArea){
      lastlrspeed=lrspeed;
      lyspeed=float(lrspeed-maxValue[0])/(maxValue[1]-maxValue[0])*2-1;
    }
    if(abs(lastangular-angular)>validArea){
      lastangular=angular;
      angularspeed=float(angular-maxValue[0])/(maxValue[1]-maxValue[0])*2-1;
    }
    if(abs(lastmaxVelocity-maxVelocity)>validArea){
      lastmaxVelocity=maxVelocity;
      maxspeed=float(maxVelocity-maxValue[0])/(maxValue[1]-maxValue[0])*2-1;
    }

    Serial.print(lxspeed);
    Serial.print(" ");
    Serial.print(lyspeed);
    Serial.print(" ");
    Serial.print(angularspeed);
    Serial.print(" ");
    Serial.println(maxspeed);

    delay(50);

}
