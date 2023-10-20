//////////// 
/*TCRT5000*/
////////////
int InfraredRangingPin = 7;                                    //定义数字检测接口
int val;                                                       //定义变量

///////////////
/*fingerprint*/
///////////////
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(2, 3);                                 // RX,TX(UNO)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;


/////////
/*servo*/
/////////
#include <Servo.h>  
Servo myservo;                                                 // 创建舵机对象
int  ServoPin = 10                                             // 定义数字检测接口
int pos = 0;                                                   // 舵机位置
int speed = 6;                                                 // 舵机速度

void setup() {
	myservo.attach(ServoPin);                                  // 将舵机连接到10号引脚的舵机对象
	pinMode(InfraredRangingPin, INPUT);                        // 红外寻迹连接引脚D2，并设置为输入模式
	Serial.begin(9600);                                        // 串口波特率为9600kbps
	while (!Serial);
	delay(100);

	Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

	finger.begin(57600);

	if (finger.verifyPassword()) {
		Serial.println("Found fingerprint sensor! :)");
	}
	else {
		Serial.println("Did not find fingerprint sensor :(");
		while (1) { delay(1); }
	}
}




void loop() {
	val = digitalRead(pin);                                    //读取数字接口的值
	// Serial.println(val);                                    //输出输出接口的值
	getFingerprintIDez();

	if (val != 1 && pos > 45) {                               //如果为低电平则开转

		for (pos = 90; pos >= 0; pos -= 1)                    // 从90度逐渐转动到0度 每次负方向转动1度
		{
			myservo.write(pos);
			delay(speed);
		}

	}
}
int getFingerprintIDez() {
	uint8_t p = finger.getImage();
	if (p != FINGERPRINT_OK) return -1;

	p = finger.image2Tz();
	if (p != FINGERPRINT_OK) return -1;

	p = finger.fingerFastSearch();
	if (p != FINGERPRINT_OK) return -1;

	for (pos = 0; pos <= 90; pos += 1)                        // 从0度逐渐转动到90度 每次正方向转动1度
	{
		myservo.write(pos);                                   // 告诉舵机转到变量'pos'所表示的位置
		delay(speed);                                         // 等待1
	}
	Serial.print("Found ID #");
	Serial.print(finger.fingerID);
	Serial.print(" with confidence of ");
	Serial.println(finger.confidence);
	while (val != 1)
	{
		delay(5);
		val = digitalRead(pin);
	}

	return finger.fingerID;
}