#pragma config(Sensor, in1,    liftPoten,      sensorPotentiometer)
#pragma config(Sensor, in2,    handpoten,      sensorPotentiometer)
#pragma config(Sensor, in3,    leftLineTrack,  sensorNone)
#pragma config(Sensor, in4,    armPoten,       sensorPotentiometer)
#pragma config(Sensor, in5,    rightLineTrack, sensorNone)
#pragma config(Sensor, dgtl1,  le,             sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  re,             sensorQuadEncoder)
#pragma config(Motor,  port1,           baserearright, tmotorVex393, openLoop)
#pragma config(Motor,  port2,           armMot,        tmotorVex393, openLoop)
#pragma config(Motor,  port4,           backHang,      tmotorVex393, openLoop)
#pragma config(Motor,  port6,           handliftr,     tmotorVex393, openLoop)
#pragma config(Motor,  port7,           handliftl,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,           basefrontleft, tmotorVex393, openLoop)
#pragma config(Motor,  port9,           baserearleft,  tmotorVex393, openLoop)
#pragma config(Motor,  port10,          basefrontright, tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//1460 to the high fens
int liftpotenmin=400;
int liftpotenmax=1550;
int liftpot=1560;
int armpotentiometer=1700;//3450;
int armpo=950;



void backwardInLine()
{
	while(SensorValue[leftLineTrack]>1850 && SensorValue[rightLineTrack]>1850)
	{
		do{
			motor[basefrontright]=motor[baserearright]=-60;
			motor[basefrontleft]=motor[baserearleft]=-60;
		}while(SensorValue[leftLineTrack]>1000 && SensorValue[rightLineTrack]>1000);
		motor[basefrontright]=motor[baserearright]=10;
		motor[basefrontleft]=motor[baserearleft]=10;
		if(SensorValue[leftLineTrack]<=1000 || SensorValue[rightLineTrack]>1000)
		{
			while(SensorValue[rightLineTrack]>1000)
			{
				motor[basefrontright]=motor[baserearright]=-50;
				motor[basefrontleft]=motor[baserearleft]=40;
			}
			motor[basefrontright]=motor[baserearright]=10;
			motor[basefrontleft]=motor[baserearleft]=10;
		}
		else if(SensorValue[leftLineTrack]>1000 || SensorValue[rightLineTrack]<=1000)
		{
			while(SensorValue[leftLineTrack]>1000)
			{
				motor[basefrontright]=motor[baserearright]=40;
				motor[basefrontleft]=motor[baserearleft]=-50;
			}
			motor[basefrontright]=motor[baserearright]=10;
			motor[basefrontleft]=motor[baserearleft]=10;
		}
		time1[T1]=0;
		if(time1[T1]<500 && motor[baserearright]==10)
		{
			return;
		}
	}
}


void forwardInLine()
{
	while(SensorValue[leftLineTrack]>1000 && SensorValue[rightLineTrack]>1000)
	{
		do{
			motor[basefrontright]=motor[baserearright]=50;
			motor[basefrontleft]=motor[baserearleft]=50;
		}while(SensorValue[leftLineTrack]>1000 && SensorValue[rightLineTrack]>1000);
		motor[basefrontright]=motor[baserearright]=0;
		motor[basefrontleft]=motor[baserearleft]=0;
		if(SensorValue[leftLineTrack]<=1000 || SensorValue[rightLineTrack]>1000)
		{
			while(SensorValue[rightLineTrack]>1000)
			{
				motor[basefrontright]=motor[baserearright]=60;
				motor[basefrontleft]=motor[baserearleft]=-35;
			}
			motor[basefrontright]=motor[baserearright]=10;
			motor[basefrontleft]=motor[baserearleft]=10;
		}
		else if(SensorValue[leftLineTrack]>1000 || SensorValue[rightLineTrack]<=1000)
		{
			while(SensorValue[leftLineTrack]>1000)
			{
				motor[basefrontright]=motor[baserearright]=-35;
				motor[basefrontleft]=motor[baserearleft]=60;
			}
			motor[basefrontright]=motor[baserearright]=10;
			motor[basefrontleft]=motor[baserearleft]=10;
		}
		time1[T1]=0;
		if(time1[T1]<500 && motor[baserearright]==10)
		{
			return;
		}
	}
}



float distanceCal(float x)
{
	float y;
	y=(x/(PI*10.16))*360;
	return (y*0.75);
}

float shaftCal(float y)
{
	float x;
	x=(y*(3.14*10.16))/360;
	return x;
}

float calangel(float a)
{
	return (a*455)/90;
}

float distanceCalLeftRight(float x)
{
	float y;
	y=(x*700)/60;
	return y;
}




void moveLeft(float distance)
{
	SensorValue[re]=SensorValue[le]=0;
	while(abs(SensorValue[re])<abs(distanceCalLeftRight(distance)))
	{
		motor[basefrontright] =motor[baserearleft] =  127;
		motor[baserearright] =motor[basefrontleft] =  -127;
	}
	motor[basefrontright] =motor[baserearright] = motor[basefrontleft] =motor[baserearleft] = 0;
}

void moveRight(float distance)
{
	SensorValue[re]=SensorValue[le]=0;
	while(abs(SensorValue[re])<abs(distanceCalLeftRight(distance)))
	{
		motor[basefrontright] =motor[baserearleft] =  -127;
		motor[baserearright] =motor[basefrontleft] =  127;
	}
	motor[basefrontright] =motor[baserearright] = motor[basefrontleft] =motor[baserearleft] = 0;
}


void forwardAndBackward(int d,int s)
{
	SensorValue[re]=SensorValue[le]=0;
	while(abs(SensorValue[re])<abs(distanceCal(d)))
	{
		while(abs(SensorValue[re])==abs(SensorValue[le]) && abs(SensorValue[re])<abs(distanceCal(d)))
		{
			motor[basefrontright]=motor[baserearright]=s;
			motor[basefrontleft]=motor[baserearleft]=s;
		}
		while(abs(SensorValue[re])>abs(SensorValue[le]) && abs(SensorValue[re])<abs(distanceCal(d)))
		{
			motor[basefrontright]=motor[baserearright]=s-20;
			motor[basefrontleft]=motor[baserearleft]=s;
		}
		while(abs(SensorValue[re])<abs(SensorValue[le]) && abs(SensorValue[re])<abs(distanceCal(d)))
		{
			motor[basefrontright]=motor[baserearright]=s;
			motor[basefrontleft]=motor[baserearleft]=s-20;
		}
	}

	motor[basefrontright]=motor[baserearright]=0;
	motor[basefrontleft]=motor[baserearleft]=0;
}



void rotateright(int a,int s)
{
	SensorValue[re]=SensorValue[le]=0;
	while(abs(SensorValue[re])<(calangel(a)) && SensorValue[le]>(-(calangel(a))))
	{
		motor[basefrontright]=motor[baserearright]=-s+10;
		motor[basefrontleft]=motor[baserearleft]=s-10;
	}
	motor[basefrontright]=motor[baserearright]=0;
	motor[basefrontleft]=motor[baserearleft]=0;
}



void forwardWhileLiftUp(int motorSpeed,int liftSpeed, int distance, int liftpot)
{
	SensorValue[re]=SensorValue[le]=0;
	while(SensorValue[liftPoten]<liftpot)
	{
		while(SensorValue[re]==SensorValue[le] && SensorValue[liftPoten]<liftpot)
		{
			motor[basefrontright]=motor[baserearright]=motorSpeed;
			motor[basefrontleft]=motor[baserearleft]=motorSpeed;
			motor[handliftl]=motor[handliftr]=liftSpeed;
		}

		while(SensorValue[re]>SensorValue[le] && SensorValue[liftPoten]<liftpot)
		{
			motor[basefrontright]=motor[baserearright]=motorSpeed-20;
			motor[basefrontleft]=motor[baserearleft]=motorSpeed;
			motor[handliftl]=motor[handliftr]=liftSpeed;
		}
		while(SensorValue[re]<SensorValue[le] && SensorValue[liftPoten]<liftpot)
		{
			motor[basefrontright]=motor[baserearright]=motorSpeed;
			motor[basefrontleft]=motor[baserearleft]=motorSpeed-20;
			motor[handliftl]=motor[handliftr]=liftSpeed;
		}
		//  	motor[basefrontright]=motor[baserearright]=motorSpeed;//to move forward while lifting
		//motor[basefrontleft]=motor[baserearleft]=motorSpeed;

	}
	motor[handliftl]=motor[handliftr]=20;
	forwardAndBackward((distance*1.4)-shaftCal(SensorValue[re]),60);
	//motor[basefrontright]=motor[baserearright]=0;
	//motor[basefrontleft]=motor[baserearleft]=0;
}









void forwardWhileLiftDown(int motorSpeed,int liftSpeed, int distance)
{
	SensorValue[re]=SensorValue[le]=0;
	while(SensorValue[liftPoten]<liftpotenmin)
	{


		while(SensorValue[re]==SensorValue[le] && SensorValue[liftPoten]<liftpotenmin)
		{
			motor[basefrontright]=motor[baserearright]=motorSpeed;
			motor[basefrontleft]=motor[baserearleft]=motorSpeed;
			motor[handliftl]=motor[handliftr]=-liftSpeed;
		}

		while(SensorValue[re]>SensorValue[le] && SensorValue[liftPoten]<liftpotenmin)
		{
			motor[basefrontright]=motor[baserearright]=motorSpeed-20;
			motor[basefrontleft]=motor[baserearleft]=motorSpeed;
			motor[handliftl]=motor[handliftr]=-liftSpeed;
		}
		while(SensorValue[re]<SensorValue[le] && SensorValue[liftPoten]<liftpotenmin)
		{
			motor[basefrontright]=motor[baserearright]=motorSpeed;
			motor[basefrontleft]=motor[baserearleft]=motorSpeed-20;
			motor[handliftl]=motor[handliftr]=-liftSpeed;
		}
		//  	motor[basefrontright]=motor[baserearright]=motorSpeed;//to move forward while lifting
		//motor[basefrontleft]=motor[baserearleft]=motorSpeed;

	}
	motor[handliftl]=motor[handliftr]=-10;
	forwardAndBackward((distance*1.4)-shaftCal(SensorValue[re]),-60);
	//motor[basefrontright]=motor[baserearright]=0;
	//motor[basefrontleft]=motor[baserearleft]=0;
}

void rotateleft(int a,int s)
{
	SensorValue[re]=SensorValue[le]=0;
	while(abs(SensorValue[le])<(calangel(a)) && SensorValue[re]>(-(calangel(a))))
	{
		motor[basefrontright]=motor[baserearright]=s-10;
		motor[basefrontleft]=motor[baserearleft]=-s+10;
	}
	motor[basefrontright]=motor[baserearright]=0;
	motor[basefrontleft]=motor[baserearleft]=0;
}

void liftUp(int liftValue)
{
	while(SensorValue[liftPoten]<liftValue)
	{
		motor[handliftl]=motor[handliftr]=90;
	}
	motor[handliftl]=motor[handliftr]=15;
}

void liftDown(int liftValue)
{
	while(SensorValue[liftPoten]>liftValue)
	{
		motor[handliftl]=motor[handliftr]=-100;
	}
	wait1Msec(300);
	motor[handliftl]=motor[handliftr]=0;
}




void liftDown2(int liftValue)
{
	while(SensorValue[liftPoten]>liftValue)
	{
		motor[handliftl]=motor[handliftr]=-20;
	}
	motor[handliftl]=motor[handliftr]=15;
}

void closeHand(int handValue) // when the hands are opened
{
	while(SensorValue[armPoten]>handValue)
		motor[armMot]=80;

	motor[armMot]=-30;    /// -30
}

void openHand(int handValue) // when the hands are opened
{
	while(SensorValue[armPoten]<handValue)
	{
		motor[armMot]=-75;
	}
	//wait1Msec(300);
	motor[armMot]=-17;
}

void holdThemtBetter()
{
	motor[armMot]=127;

	time1[T1]=0;
	while(time1[T1]<300){}

	forwardAndBackward(15,-60);
	motor[armMot]=-50;

	time1[T1]=0;
	while(time1[T1]<400){}

	forwardAndBackward(10,60);
	motor[armMot]=127;

	time1[T1]=0;
	while(time1[T1]<400){}

	motor[armMot]=20;
}



task main()
{
	moveRight(87);
	//time1[T4]=0;
	//while(time1[T4]<200){}

	forwardAndBackward(38,100);
	//time1[T4]=0;while(time1[T4]<200){}

	motor[armMot]=127;
	time1[T4]=0;while(time1[T4]<500){}
	motor[armMot]=40;
	//time1[T4]=0;while(time1[T4]<200){}

	liftUp(liftpotenmax);
	//time1[T4]=0;while(time1[T4]<200){}

	forwardAndBackward(102,127);
	//time1[T4]=0;while(time1[T4]<200){}

	motor[armMot]=-50;
	time1[T4]=0;while(time1[T4]<400){}
	motor[armMot]=0;
	//time1[T4]=0;while(time1[T4]<200){}

	backwardInLine();
	//time1[T4]=0;while(time1[T4]<200){}

	openHand(armpotentiometer);
	//time1[T4]=0;while(time1[T4]<200){}

	while(SensorValue[liftPoten]>liftpot)
	{
		motor[handliftl]=motor[handliftr]=-20;
	}
	wait1Msec(150);
	motor[handliftl]=motor[handliftr]=15;
	//time1[T4]=0;while(time1[T4]<200){}

	forwardAndBackward(60,100);
	//time1[T4]=0;while(time1[T4]<200){}

	backwardInLine();
	//time1[T4]=0;while(time1[T4]<200){}

	motor[armMot]=127;
	wait1Msec(400);
	motor[armMot]=0;

	openHand(armpotentiometer);
	//time1[T4]=0;while(time1[T4]<200){}

	liftUp(liftpotenmax);
	//time1[T4]=0;while(time1[T4]<200){}

	moveRight(135);
	//time1[T4]=0;while(time1[T4]<200){}

	forwardAndBackward(5,100);
	//time1[T4]=0;while(time1[T4]<200){}

	backwardInLine();
	//time1[T4]=0;while(time1[T4]<200){}

	forwardAndBackward(70,100);
	//time1[T4]=0;while(time1[T4]<200){}

	backwardInLine();
	//time1[T4]=0;while(time1[T4]<200){}

	motor[armMot]=-127;
	wait1Msec(250);
	motor[armMot]=0;
	//time1[T4]=0;while(time1[T4]<200){}

	liftDown(liftpotenmin);
	//wait1Msec(200);

	rotateleft(250,100);
	//time1[T4]=0;while(time1[T4]<200){}

	forwardAndBackward(15,-100);
	//time1[T4]=0;while(time1[T4]<200){}

	moveRight(85);
	//time1[T4]=0;while(time1[T4]<200){}

	forwardInLine();
	//time1[T4]=0;while(time1[T4]<200){}

	//motor[armMot]=127;
	//time1[T4]=0;while(time1[T4]<500){}
	//motor[armMot]=20;
	holdThemtBetter(); // best function ever

	liftUp(liftpotenmax);
	//time1[T4]=0;while(time1[T4]<200){}

	rotateright(250,100);
	time1[T4]=0;while(time1[T4]<200){}

	forwardAndBackward(70,100);
	time1[T4]=0;while(time1[T4]<200){}

	//////////////////////////////////////////////////////////////////////////////////////

	//openHand(armpotentiometer);
	//time1[T4]=0;while(time1[T4]<200){}

	motor[armMot]=-127;
	time1[T4]=0;while(time1[T4]<300){}
	motor[armMot]=0;

	rotateleft(155,100);
	//time1[T4]=0;while(time1[T4]<200){}

	liftDown(liftpotenmin);

	openHand(armpo);

	forwardAndBackward(200,127);
	//time1[T4]=0;while(time1[T4]<200){}

	motor[armMot]=127;
	time1[T4]=0;while(time1[T4]<300){}
	motor[armMot]=0;

	//holdThemtBetter();

	rotateright(200,100);
	//time1[T4]=0;while(time1[T4]<200){}

	openHand(armpo);

	forwardInLine();
	time1[T4]=0;while(time1[T4]<100){}

	liftUp(liftpotenmax);

	openHand(armpotentiometer);

	forwardAndBackward(110,127);
	//time1[T4]=0;while(time1[T4]<200){}

	//motor[basefrontright]=motor[baserearright]=0;
	//motor[basefrontleft]=motor[baserearleft]=0;
	//motor[handliftl]=motor[handliftr]=0;
	////time1[T4]=0;while(time1[T4]<3000){}
}
