#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <EEPROMEx.h>
#include <SoftwareSerial.h>  // for serial communication
#include <TinyGPS.h>

int sensorPin = A0;   // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor
//float voltage;
//int addressByte;

LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4); // set LCD pins
SoftwareSerial gprsSerial(8,9); // Rx, Tx
//SoftwareSerial ss(8,9);

float flat = 28.63 ,flon = 77.21;
int year = 0;
byte month =0 , day = 0, hour = 0 , minu = 0, second, hundredths;
unsigned long fix_age;
unsigned long timestart=0;
unsigned long timekeeper=0;
boolean fillScreen = false;
//TinyGPS gps;
char PLACE[25];
boolean updated;

float curr_volume=0;
float prev_volume;
int check=0;

boolean filling=false; 
//float volBeforeRefill=0; 
float volAfterRefill=0;
float volFilled=0;  
float total;
float volArray[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
float avgVolume=0;
int index=0;

float fuel_vol;
float fuel_vol_firsttime;
//int speedometer;

//int sensorPin1 = A1; 
//float sensorValue1 = 0;
//byte voltage1;
int accX, accY, accZ, sum1, sum2;
byte accXPin = A1, accYPin = A2, accZPin = A3;
int difference;
byte intrupt = 0;
byte v1;
byte speedometer=1;

float total1;
float a;
float b;
float x;
float t1;
float t2;
float o1;
//char mobile [6];

int writ;

int toggleindex=0;


byte d1[]={0,0,0,0,0,0,0,0,0,0};
byte m1[]={0,0,0,0,0,0,0,0,0,0};
byte y1[]={0,0,0,0,0,0,0,0,0,0};
byte h1[]={0,0,0,0,0,0,0,0,0,0};
byte mi1[]={0,0,0,0,0,0,0,0,0,0};

//int volu[]={0,0,0,0,0,0,0,0,0,0};
int mon[]={0,0,0,0,0,0,0,0,0,0};


int buttonstart = A4; 
int buttonright = A5;
int buttonleft = A3;
String remdate="";
//String remfuel="";
int mov;

//SerialGSM gprsSerial(2,3); // Rx, Tx
char ctrlZ = 0x1A;
char price[6];
char ss2[6];
char temp;
int z = 0;
float PRICE=70.44;


void checktoggle()                  //checks for toggle at different parts of code
{
  
  toggledetected();
  if(digitalRead(buttonstart) == 1){
    while(digitalRead(buttonstart) == 1){}
    lcd.clear();
    //Serial.println("Reset");
    fillScreen = false;
  }
}

void toggledetected(){							//if toggle is there then print last date and fuel vol in LCD
  mov=toggleindex;								// mov starts form toggle index
  
  if(digitalRead(buttonright)==1)
  {
    fillScreen = true;
    //Serial.println("Right Toggle");
    while(digitalRead(buttonright)==1){}
    
    mov=(mov+1)%10;
    remdate=getdate(mov);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Last Fills");
    lcd.setCursor(0,1);
    lcd.print(remdate);
    remdate=getfuel(mov);
    lcd.setCursor(-3,2);
    lcd.print(remdate);
    
  } 
  if(digitalRead(buttonleft)==1)
  {
    fillScreen = true;
//  Serial.println("Left Toggle");
  while(digitalRead(buttonleft)==1){}
    
    mov=(mov+9)%10;
    remdate=getdate(mov);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Last Fills");
    lcd.setCursor(0,1);
    lcd.print(remdate);
    remdate=getfuel(mov);
    lcd.setCursor(-3,2);
    lcd.print(remdate);
  } 
  
}

String getdate(int k){
  
  String rem;
  if(d1[k]<10)
  rem+="0";
  rem+=d1[k];
  rem+="/";
  
  
  if(m1[k]<10)
  rem+="0";
  rem+=m1[k];
  rem+="/";
  
  
  if(y1[k]<10)
  rem+="0";
  rem+=y1[k];
  rem+=" ";
  
  if(h1[k]<10)
  rem+="0";
  rem+=h1[k];
  rem+=":";
  
  
  if(mi1[k]<10)
   rem+="0";
  rem+=mi1[k];
  
  
  return rem;
}

String getfuel(int k){
  String rem = "";
  //rem+=(int)(mon[k]*PRICE);
  rem+=(int) ((1000.0/PRICE)*mon[k]);
  rem+="ml. Rs.";
  rem+=mon[k];
  return rem;
}

void printtimelcd(){
  lcd.setCursor(0, 0);
  if(day<10)
  lcd.print('0');
  lcd.print(day);
  
  lcd.print('/');
  
  if(month<10)
  lcd.print('0');
  lcd.print(month);
  lcd.print('/');
  lcd.print(year);
  lcd.print(' ');
  
  if(hour<10)
  lcd.print('0');
  lcd.print(hour);
  lcd.print(':');
  
  if(minu<10)
  lcd.print('0');
  lcd.print(minu);
  
}


////




//void printtimelcd1(){
//  lcd.setCursor(0, 1);
//  if(day<10)
//  lcd.print("0");
//  lcd.print(day);
//  
//  lcd.print("/");
//  
//  if(month<10)
//  lcd.print("0");
//  lcd.print(month);
//  lcd.print("/");
//  if(year<10)
//  lcd.print("0");
//  lcd.print(year);
//  lcd.print("  ");
//  
//  if(hour<10)
//  lcd.print("0");
//  lcd.print(hour);
//  lcd.print(":");
//  
//  if(minu<10)
//  lcd.print("0");
//  lcd.print(minu);
//  
//}


//void printtime()
//{
//  if(day<10)
//  Serial.print("0");
//  Serial.print(day);
//  
//  Serial.print("/");
//  
//  if(month<10)
//  Serial.print("0");
//  Serial.print(month);
//  Serial.print("/");
//  if(year<10)
//  Serial.print("0");
//  Serial.print(year);
//  Serial.print("  ");
//  
//  if(hour<10)
//  Serial.print("0");
//  Serial.print(hour);
//  Serial.print(":");
//  
//  if(minu<10)
//  Serial.print("0");
//  Serial.println(minu);
//}


void checktime(){
  if((timekeeper-timestart)>60000)
  {
    timestart=timestart+60000;
    updateminute();
    //printtime();
    if(fillScreen == false){
      printtimelcd();}
  }
}

void updateminute(){
  minu=(minu+1)%60;
  if(minu==0)
  updatehour();
}

void updatehour(){
  hour=(hour+1)%24;
  if(hour==0)
  updateday();
}

void updateday(){;
  if(day==29 && year%4==0 && month==2)
  {
    day=1;
    month=3;
  }
  
  else if(day==28 && month==2 && year%4 != 0)
  {
    day=1;
    month=3;
  }
  
  if(day==30 && (month==4 || month==6 || month==8 || month==10 || month==12))
    {
      day=1;
      updatemonth();
    }
   if(day==31 && (month==1 || month==3 || month==5 || month==7 || month==9 || month==11))
    {
      day=1;
      month++;
    }
    else
    day++;
}

void updatemonth(){
  if (month==12)
  {
    month==1;
    updateyear();
  }
  else
  month++;
  
}

void updateyear(){
  year=(year+1)%100;
}


static float VoltageVolume[51][2] PROGMEM = {
0.71,	11400,
15.44,	12025,
31.35,	12650,
47.71,	13275,
63.24,	13900,
78.7,	14525,
94.08,	15150,
109.58,	15775,
125.07,	16400,
140.3,	17025,
155.69,	17650,
171.13,	18275,
186.34,	18900,
200.48,	19525,
215.48,	20150,
230.77,	20775,
245.89,	21400,
261.17,	22025,
276.91,	22650,
292.42,	23275,
308.03,	23900,
323.99,	24525,
338.46,	25150,
352.96,	25775,
366.99,	26400,
380.88,	27025,
394.58,	27650,
408.09,	28275,
422.02,	28900,
435.88,	29525,
449.35,	30150,
462.99,	30785,
476.09,	31420,
489.81,	32055,
503.03,	32690,
516.95,	33325,
530.1,	33960,
543.87,	34595,
557.34,	35230,
571.09,	35865,
585.26,	36500,
599.69,	37135,
614.13,	37770,
628.98,	38405,
643.67,	39040,
658.49,	39675,
673.01,	40310,
688.97,	40945,
705.93,	41580,
723.01,	42215,
740.32,	42850,

};


float lookup(float a1)
{
  if(a1<=.71)
    return 11400;
  if(a1>=740.32)
    return 42650;
  for(int i=0;i<51;i++)
  {
    t1=pgm_read_float(&(VoltageVolume[i+1][0]));
    t2=pgm_read_float(&(VoltageVolume[i][0]));
    if (t1>a1 && t2<=a1)
    {
       o1=pgm_read_float(&(VoltageVolume[i][1]));
        return o1 + (((a1-t2)/(t1-t2))*630.00);
    }
  }
}
void readAcc(){
  

for(int i=0 ; i<10; i++){
  accX = analogRead(accXPin);
  sum2=sum2+accX;
  delay(3);
}
sum2=sum2/10;
difference = sum2 - sum1;
Serial.print(" difference   :");
Serial.println(difference);
sum1 = sum2;
}

void findspeedo(){
  checktoggle();

if(speedometer == 0){
  readAcc();
  if(abs(difference) > 1){
    //readAcc();
   // if(abs(difference) > 1){
      //readAcc();
      speedometer = 1; 
   //   }
      
    }
}
if(speedometer == 1){
  readAcc();
  if(abs(difference) < 1){
    readAcc();
    if(abs(difference) < 1){
      readAcc();
      if(abs(difference) < 1){
        speedometer = 0;
      }
      
    }
    
  }
}
//Serial.println(speedometer);


}


float calculateAvgs1(){
  findspeedo();
  
  
// it is delay(8000) ; 
for(int l=0;l<160;l++)
{
delay(30);
timekeeper=millis();
checktime();
checktoggle();
}
total1=0;
for(int i=0;i<4000;i++){
   if(i%1000==0)
    {findspeedo();
    timekeeper=millis();
      checktime();

     }
    if(speedometer==1)
    {Serial.println("intruppt**");
    return 0;
    break;}
    sensorValue = analogRead(sensorPin);
    //voltage= (5.0*sensorValue*10)/1023.00;
    //voltage=voltage/10;
    if(i%500==0)
    Serial.println();
	total1=(lookup(sensorValue))/400.00+total1;
//	delay(1);
  checktoggle();
}
Serial.print("avg fllng: "); 
Serial.println(total1/10.0);
return total1/10.0;
 
}


float calculateAvgs(){
  
total1=0;
for(int i=0;i<4000;i++){
  if(i%1000==0)
  {findspeedo();
  timekeeper=millis();
  checktime();
  }
  if(speedometer==1)
    {Serial.println("intruppt**");
      return 0;
    break;}
    sensorValue = analogRead(sensorPin);
    //voltage= (5.0*sensorValue*10.000)/1023.00;
    //voltage=voltage/10.0;
    if(i%500==0)
    Serial.println(sensorValue);
	total1=lookup(sensorValue)/400.0+total1;
	delay(1);
      checktoggle();
}
Serial.print("avg while filing="); 
Serial.print(total1/10.0);
return total1/10.0;
 
}


void sendMessage(float k2,float k3){
  char mobile [6];
//
  gprsSerial.listen();
  gprsSerial.println("AT+CMGF=1");
    delay(1000);
  gprsSerial.println("AT+CMGS=\"9999779476\"");  // Phone number
  delay(3000);
  
  gprsSerial.print("\nVolume : \r");
  dtostrf(k2, 5, 0, mobile);
  gprsSerial.print(mobile);
  
  gprsSerial.print("\nPlace :");
  gprsSerial.print(PLACE);
  
  
  gprsSerial.print("\nAmount Rs. ");
  dtostrf(k3, 5, 0, mobile);
  gprsSerial.println(mobile);
  
  gprsSerial.print("\nVehichle Number : Getz ");
  
  //gprsSerial.println("\nThe vehicle number is DL 4CS 4837");

  delay(200);
  gprsSerial.println("\n");
  gprsSerial.println(ctrlZ);
  Serial.println("Sending message!");

}


void setupGSM(){

  
//  gprsSerial.Verbose(true);
//  gprsSerial.Boot(); 
//  gprsSerial.FwdSMS2Serial();
//gprsSerial.begin(9600);
  Serial.println("SIM900...");

  //Serial.println("Done!...");

  gprsSerial.flush();

  Serial.flush();

  

  // signal quality

  gprsSerial.println("AT+CSQ");

  delay(100); 

  toSerial();

    
  // attach or detach from GPRS service 

  gprsSerial.println("AT+CGATT?");

  delay(100);

  toSerial();

        

  

  // bearer settings

  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");

  delay(2000);

  toSerial();

    

  // bearer settings

  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"www\"");

  delay(2000);

  toSerial();

        

  // bearer settings

  gprsSerial.println("AT+SAPBR=1,1");

  delay(2000);

  toSerial();
  
  //lcd.print()

}


void updateFromServer(int l, int pr){
  char mobile [6];

  // initialize http service

   // initialize http service
   gprsSerial.listen();
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();
   
   char address[110];
   strcpy(address, "AT+HTTPPARA=\"URL\",\"http://www.karshintech.tk/getPrice.php?lat=");
   // set http param value
   //gprsSerial.print();
   dtostrf(flat, 5, 2, mobile);
   strcat(address, mobile);
   //gprsSerial.print(mobile);
   strcat(address, "&lon=");
   dtostrf(flon, 5, 2, mobile);
   strcat(address, mobile);
   //gprsSerial.print(mobile);
   strcat(address, "&id=");
   dtostrf(l, 1, 0, mobile);
   strcat(address, mobile);
   strcat(address, "&vid=1");
   strcat(address, "&pr=");
   dtostrf(pr, 3, 0, mobile);
   strcat(address, mobile);
   strcat(address, "\"");
   Serial.println(address);
   gprsSerial.println(address);
   delay(2000);
   toSerial();
      
   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(5000);
   toSerial();
   
   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(2000);
   toSerial();
   
   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(1300);
   
   gprsSerial.println("");
   delay(5000);
   

}  
  

void toSerial()
{
  char temp;
  while(gprsSerial.available()!=0)
  {
    temp = gprsSerial.read();
    
    Serial.print(temp);
    if (temp == '#'){
      int j;
     // Serial.println("First #");
     // Serial.println("reading price");
      temp = gprsSerial.read();
      char id[2];
      id[0] = temp;
      id[1] = '\0';
      Serial.print("ID  : ");
      
      int ID = atof(id);
      Serial.println(ID);
      j=0;
      
      temp = gprsSerial.read();
      temp=gprsSerial.read();
      if(ID == 1){
        Serial.print("New Price: ");
      while(temp != '#'){
        
        price[j++] = temp;
        temp = gprsSerial.read();
      }
      price[--j] = '\0';
      Serial.println(price);
      PRICE=atof(price);
      }
      if(ID == 2){
        Serial.print("plc: ");
      while(temp != '#'){
        
        PLACE[j++] = temp;
        temp = gprsSerial.read();
      }
      PLACE[--j] = '\0';
     Serial.println(PLACE); 
     }
     
    }
  }
}   
 
void updateLocation(){
  //TinyGPS gps;
  SoftwareSerial ss(2,3);
  ss.begin(9600);
  TinyGPS gps;
//int speed =0;
  int inLoop = 0;
 // ss.listen();
// ss.begin(9600);
 delay(1000);
  Serial.println("loc");
  while (inLoop<750)
  {
    int c = ss.read();
    if (gps.encode(c))
    {
      // process new gps info here
      gps.f_get_position(&flat, &flon, &fix_age);
      if(z == 0){
      gps.crack_datetime(&year, &month, &day, &hour, &minu, &second, &hundredths, &fix_age);}
      Serial.print("Latitude :: ");
      Serial.print(flat);
      Serial.print("Longitude : ");
      Serial.print(flon);
      //Serial.print(" Speed : ");
      //speed = gps.speed();
      //Serial.print(speed);
      //speed = speed*.01852;
      //Serial.print("   Km/h  :");
      //Serial.println(speed);
      
    }
    Serial.print((char) c);
    ++inLoop;
  } 
  inLoop = 0;
}


void setup() {   
 /// GLCD.Init();
 /// GLCD.ClearScreen(); 
  lcd.clear();
  lcd.begin(16, 4);
  
  delay(500);
  
//printtimelcd1();
  //lcd.setCursor(0, 1);
  
  Serial.begin(9600);  
  Serial.println("start");
  printtimelcd();
  //lcd.print("///////////");
 gprsSerial.begin(9600);
 //setupGSM();
 delay(1000); 
 //ss.begin(9600);
  //Serial.println(prev_volume);
   Serial.println("start");
  
  //lcd.begin(16, 2); // initialise LCD 
  //lcd.print("start");
//  pinMode(7, INPUT);
//  pinMode(8,INPUT);
    pinMode(sensorPin,INPUT);
    //pinMode(sensorPin1,INPUT);
    pinMode(buttonstart,INPUT);
    pinMode(buttonright,INPUT);
    //pinMode(buttonleft,INPUT);
    
//  pinMode(5,OUTPUT);
//  pinMode(6,OUTPUT);
 // Serial.println("start");
   /// GLCD.SelectFont(System5x7, BLACK);
   accX = analogRead(accXPin);
   accY = analogRead(accYPin);
   accZ = analogRead(accZPin);
   sum1 = accX;
    EEPROM.readBlock(100,volArray,60);
    index=EEPROM.readInt(700);  
  //Serial.println(prev_volume);
 // updateFromServer(2);
 // delay(1000);
//  updateFromServer(2);
  updateLocation();
  delay(200);
  updateLocation();
  hour += 5;
  if((minu+30) > 59){
    minu = (minu+30)%60;
    hour+=1;
  } else {
    minu += 30;
  }
  
  if(hour > 23){
    hour = hour%24;
    day +=1;
  }
  
}

void loop() {
  checktoggle();
  //printtimelcd();
  //lcd.print(rememberdate());
  timekeeper=millis();
 checktime();

findspeedo(); 
//Serial.println(speedometer);  
  
 // EEPROM.writeBlock(100,volArray,60);
  EEPROM.readBlock(100,volArray,120);
  Serial.print("Initial");
  for(int i=0;i<60;i++){
    //Serial.print("initail:");
    Serial.println(volArray[i]);
    Serial.println(index);
  }

total=0;
writ=1;
if(speedometer==1)
{
  checktoggle();
for(int i=0;i<100;){
    sensorValue = analogRead(sensorPin);
    //voltage= (5.0*sensorValue)/1023.00;
    if(curr_volume==0 || abs(curr_volume-lookup(sensorValue))<=1000)
      {
        
        if(i%19==0)
        findspeedo();
        
        if(speedometer==0)
        {
          writ=0;
          break;
        }
        total=(lookup(sensorValue))/100.0+total;
     //   Serial.println("lookup v:");
        Serial.println(lookup(sensorValue));
       // Serial.println(voltage);
      // Serial.println(sensorValue);
        i++;
        check=0;
         delay(10);
         timekeeper=millis();
         checktime();

    }
    else
   {
     if(abs(lookup(sensorValue)-curr_volume)>1000)
    { Serial.println(check);
    
       timekeeper=millis();
      checktime();

      findspeedo();
      if(speedometer==0)
        {
          writ=0;
          break;
        }
      if(speedometer==1)
      check=check+1;
      delay(1);
    }
   }
if(check>50)
  {
    Serial.println("HANG");
   curr_volume=0;
  i=0;
  total=0;
 }
  }
  
  if(writ==1){
  curr_volume=total;
  Serial.print("Avg curr vol:");
//  Serial.println(voltage);
  Serial.println(curr_volume);
  volArray[index]=curr_volume;
  index=(index+1)%60;
   EEPROM.writeBlock(100,volArray,60);
   EEPROM.writeInt(700,index);
  avgVolume=0;
  for(int i=0;i<60;i++)
 {
    avgVolume=avgVolume+float(volArray[i]/60.0);
    Serial.println("sdsafsacf:");
    Serial.println(volArray[i]);
    
  }
//  avgVolume=avgVolume;
////  EEPROM.writeInt(300,avgVolume);
  ///GLCD.CursorToXY(1, 1);
  Serial.print("Avrg vol: ");
 /// GLCD.print("Average vol: ");
  Serial.println(avgVolume);
  
  lcd.setCursor(-4, 2);
  if(fillScreen == false){
    lcd.print("Avg");
    lcd.setCursor(-4, 3);
    lcd.print((int)avgVolume);  }
   
  ///GLCD.print(avgVolume);
  //if(speedometer)
  //{
  //  delay(500);
  //}
} 

}
  
  
else{ 
  timekeeper=millis();
  checktime();
  checktoggle();

  fuel_vol_firsttime=calculateAvgs1();
  while(speedometer==0){
    findspeedo();
    fuel_vol=calculateAvgs();
    Serial.println("stop volume");
    
  if(!filling  && (fuel_vol>fuel_vol_firsttime+1000))
  { 
      filling=true;
      //volBeforeRefill=fuel_vol_firsttime;
  }
  delay(500);
 if(filling  && abs(fuel_vol-prev_volume)<=100)
 {
    filling=false;
    volAfterRefill=fuel_vol;  
    volFilled= volAfterRefill- fuel_vol_firsttime;
    a=volFilled/(50000.0/PRICE);
    //729.075;
    b=a;
    while(a>=1)
    a=a-1;
    b=b-a;
    if(a>0.5)
    b=b+1;
    
    
    Serial.print("vol filled:");
    Serial.println(volFilled);
   // GLCD.CursorToXY(1, 12);
    ///GLCD.print("Volume Filled: ");
    ///GLCD.print(volFilled);
    
//    lcd.setCursor(6, 2);
//    lcd.print("Fill");
//    lcd.setCursor(6, 3);
//    lcd.print((int)volFilled);
//    
    x=(50000.0/PRICE)*b;
    Serial.print("exact vol filled ");
    Serial.println(x);
   /// GLCD.CursorToXY(1, 23);
    ///GLCD.print("Exact Filled: ");
    ///GLCD.print(x);
    
     lcd.setCursor(2, 2);
    lcd.print("Fill");
    lcd.setCursor(2, 3);
    lcd.print((int)x);
    
    Serial.print("amount Rs.**");
    Serial.println(b*50);
    ///GLCD.CursorToXY(1, 34);
    ///GLCD.print("Amount: ");
    ///GLCD.print(b*50);
    
    lcd.setCursor(8, 2);
    lcd.print("Amt");
     lcd.setCursor(8, 3);
    lcd.print((int)b*50);
    
    

//    dtostrf(ss2, 5, 0,volFilled );
//    strcat(ssans, ss2);
//    
//    ssans=ssans+"ml Rs."
//    dtostrf(ss2, 4, 0,int(b*50));
//    strcat(ssans, ss2);
    
//    toggledata[toggleindex]= ssans;

   //String ssans=""+(int)volFilled +"ml "+"Rs." +int(b*50);
//    strcat(message, mobile);
  //  toggledate[toggleindex]=rememberdate();
  
  


    d1[toggleindex]=day;
    m1[toggleindex]=month;
    y1[toggleindex]=year;
    h1[toggleindex]=hour;
    mi1[toggleindex]=minu;
    
    //volu[toggleindex]=(int)volFilled;
    mon[toggleindex]=(int)(b*50);
  
  
    toggleindex=(toggleindex+1)%10;
//    for(int k=0;k<10;k++){
//      
//  if(d1[k]<10)
//  Serial.print("0");
//  Serial.print(d1[k]);
//  
//  Serial.print("/");
//  
//  if(m1[k]<10)
//  Serial.print("0");
//  Serial.print(m1[k]);
//  Serial.print("/");
//  if(y1[k]<10)
//  Serial.print("0");
//  Serial.print(y1[k]);
//  Serial.print("  ");
//  
//  if(h1[k]<10)
//  Serial.print("0");
//  Serial.print(h1[k]);
//  Serial.print(":");
//  
//  if(mi1[k]<10)
//  Serial.print("0");
//  Serial.println(mi1[k]);
//  
//      
//      
//      
//     Serial.print(volu[k]); 
//     Serial.print("ml. Rs.");
//     Serial.println(mon[k]);
//      Serial.println("");   
//    }
    //lcd.setCursor(0,1);
    //printtimelcd1();
  setupGSM();
  delay(1000);
  strcpy(PLACE, "null");
  updateFromServer(2, b*50); 
  delay(1000);
  if(strcmp(PLACE, "null")){
  updateFromServer(2, b*50); 
  delay(1000);}
  sendMessage(x, b*50.0); //   GSM CODE
    ///GLCD.CursorToXY(1, 45);
    ///GLCD.print("Message Sent");
    
    EEPROM.writeInt(50,volFilled);
    curr_volume=volFilled+avgVolume;
    for(int i=0;i<60;i++)
    {
      volArray[i]=curr_volume ;
    }
    EEPROM.writeBlock(100,volArray,60);
    break;
 } 
 prev_volume=fuel_vol;
 
 
  }
}
 
prev_volume=curr_volume;
++z;
if(z%5 == 0){
  updateLocation();
}


}
