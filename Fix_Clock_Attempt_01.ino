#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
bool h12=false;
bool PM=false;
const int Num0 = 2;//Definations of nixie tube pins.
const int Num1 = 3;
const int Num2 = 4;
const int Num3 = 5;
const int Num4 = 6;
const int Num5 = 7;
const int Num6 = 8;
const int Num7 = 9;
const int Num8 = 10;
const int Num9 = 11;
const int Aux = 12;
const int Latancy = 600;//ms
const int ShiftCompensation = 50;//ms actually mistap are rare.
const int TapSensor = A0;
int state = LOW;
unsigned long Prev_Trigger=0;
unsigned long Trigger;
void setup()
{
	
	pinMode(Num0, OUTPUT);//Declare pin as output mode.
	pinMode(Num1, OUTPUT);
	pinMode(Num2, OUTPUT);
	pinMode(Num3, OUTPUT);
	pinMode(Num4, OUTPUT);
	pinMode(Num5, OUTPUT);
	pinMode(Num6, OUTPUT);
	pinMode(Num7, OUTPUT);
	pinMode(Num8, OUTPUT);
	pinMode(Num9, OUTPUT);
	pinMode(TapSensor, INPUT);
	pinMode(Aux, INPUT);
	Wire.begin();
	Serial.begin(9600);
	Clock.setClockMode(h12);
	/*Clock.setSecond(0);
	Clock.setHour(19);
	Clock.setMinute(37);
	Clock.setDate(1);
	Clock.setDoW(4);
	Clock.setMonth(03);
	Clock.setYear(18);*/
}
void Display()
{
	byte hrs, mins;
	int Split[4];
	hrs = Clock.getHour(h12, PM);
	mins = Clock.getMinute();
	Split[1] = hrs % 10;
	Split[0] = (hrs - (hrs % 10)) / 10;
	Split[3] = mins % 10;
	Split[2] = (mins - (mins % 10)) / 10;
	for (int i = 0; i < 4; i++) {
		Serial.println(Split[i]);
		switch (Split[i])
		{
			case 0: digitalWrite(Num0, HIGH); delay(1400); digitalWrite(Num0, LOW); break;
			case 1: digitalWrite(Num1, HIGH); delay(1400); digitalWrite(Num1, LOW); break;
			case 2: digitalWrite(Num2, HIGH); delay(1400); digitalWrite(Num2, LOW); break;
			case 3: digitalWrite(Num3, HIGH); delay(1400); digitalWrite(Num3, LOW); break;
			case 4: digitalWrite(Num4, HIGH); delay(1400); digitalWrite(Num4, LOW); break;
			case 5: digitalWrite(Num5, HIGH); delay(1400); digitalWrite(Num5, LOW); break;
			case 6: digitalWrite(Num6, HIGH); delay(1400); digitalWrite(Num6, LOW); break;
			case 7: digitalWrite(Num7, HIGH); delay(1400); digitalWrite(Num7, LOW); break;
			case 8: digitalWrite(Num8, HIGH); delay(1400); digitalWrite(Num8, LOW); break;
			case 9: digitalWrite(Num9, HIGH); delay(1400); digitalWrite(Num9, LOW); break;
			default: digitalWrite(13, HIGH); delay(100); digitalWrite(13, LOW);
				break;
		}
		delay(500);
	}
}
int TapListen() {
	bool taped = false;
	int Tap_State = digitalRead(TapSensor);
	if (Tap_State==HIGH) {
		delay(Latancy);
		if (digitalRead(TapSensor) == Tap_State) {
			taped = true;
			return 2;
		}
		else {
			taped = true;
			return 1; 
		}
	}
	
	if (digitalRead(Aux) == LOW) {
		taped = true;
		return 3;
	}
	if (!taped) {
		return 0;
	}
}
void Adjust() {
	int adj[4] = {0};
	int counter = 0;
	int raider = 0;
	while (digitalRead(Aux) != LOW) {
		if (TapListen() == 1) {
			counter++;
			if (counter > 9 || counter < 0 || adj[0] > 2 || adj[2] > 5) {
				counter = 0;
				adj[raider] = counter;
				Serial.println("Illegal format detected, auto compensating...");
			}
			switch (adj[raider])
			{
			case 0: digitalWrite(Num0, HIGH); delay(800); digitalWrite(Num0, LOW); break;
			case 1: digitalWrite(Num1, HIGH); delay(800); digitalWrite(Num1, LOW); break;
			case 2: digitalWrite(Num2, HIGH); delay(800); digitalWrite(Num2, LOW); break;
			case 3: digitalWrite(Num3, HIGH); delay(800); digitalWrite(Num3, LOW); break;
			case 4: digitalWrite(Num4, HIGH); delay(800); digitalWrite(Num4, LOW); break;
			case 5: digitalWrite(Num5, HIGH); delay(800); digitalWrite(Num5, LOW); break;
			case 6: digitalWrite(Num6, HIGH); delay(800); digitalWrite(Num6, LOW); break;
			case 7: digitalWrite(Num7, HIGH); delay(800); digitalWrite(Num7, LOW); break;
			case 8: digitalWrite(Num8, HIGH); delay(800); digitalWrite(Num8, LOW); break;
			case 9: digitalWrite(Num9, HIGH); delay(800); digitalWrite(Num9, LOW); break;
			default: digitalWrite(13, HIGH); delay(100); digitalWrite(13, LOW);
				break;
			}
		}
		if (TapListen() == 2) {
			adj[raider] = counter;
			raider++;
			counter = 0;
			if (raider > 3 || raider < 0) {
				raider = 0;
				counter = 0;
				Serial.println("auto zero");
			}
			for (int i = 0; i < 4; i++) {
				Serial.println(adj[i]);
			}
		}
	}
	byte Hrs = adj[0] * 10 + adj[1];
	byte Mins = adj[2] * 10 + adj[3];
	Clock.setHour(Hrs);
	Clock.setMinute(Mins);
	Clock.setSecond(00);
}


void DisplayMode() {
	int t = TapListen();
	if (t == 1) {
		Display();
	}
	else if (t == 2)
	{
		Adjust();
	}
}

void loop()
{
	DisplayMode();
	
}
