/*
 * Arduino source code used in the MagLev experiment
 */
int PinS=A0,s,k=0,u,un=0,sg,x,xn=0;
double vel,xr,xref=1.32,g,gn=0,h=0.01;
 void setup() {
  pinMode(3,OUTPUT);
  TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of                                          //31372.55 Hz
  Serial.begin(9600);
 }
 void loop() {
  // First clear the channel
  if (k==0){
     u=0;
     analogWrite(3,u);
     delay(100);
     u=255;
     analogWrite(3,u);
     delay(100);
     u=0;
     analogWrite(3,u);
     k=1;
  }
  // Read the position from PIN A0
  xr=analogRead(0);
  delayMicroseconds(20);
  // Convert (0,1024) bites to measured position.
  double x=5-xr*(5.0/1023);
  // Velocity sign function
  vel=x-xn;
  if (vel>0){
    s=1;
    }
  if (vel<=0){
    s=-1;
    }
  // Integral part (discrete evaluation and reset)
  g=-0.8*gn+h*(x-xref);
  if (abs(g)>120){
      g=0;
      }
  // Satured control input
  u=min(max(300*(x-xref)*s-70*vel+70*g+100,0),255);
  // Send to Arduino Uno through PIN 3
  analogWrite(3,u);
  // Store last valued variables, needed to
  // evaluate the velocity and integral factor
  xn=x;
  gn=g;
 }
