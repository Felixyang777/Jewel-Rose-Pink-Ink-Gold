 #include <Servo.h>

 Servo myservo;  // 创建舵机对象来控制舵机
 // 大多数板子上可以创建12个舵机对象

 int pos = 0;    // pos变量用于存储舵机位置
 int speed = 6; // speed变量用于控制舵机转动的速度，单位ms
 int pin = 10;    // pin变量用于选择控制舵机的引脚 只能使用pwm引脚 
 // Arduino UNO中,pwm引脚是3、5、6、9、10和11

 void setup() 
 {
   myservo.attach(pin);  // 将舵机连接到9号引脚的舵机对象
 }

 void loop() {
   for (pos = 0; pos <= 90; pos += 1) // 从0度逐渐转动到180度 每次正方向转动1度
   { 
     myservo.write(pos);              // 告诉舵机转到变量'pos'所表示的位置
     delay(speed);                       // 等待15毫秒，让舵机到达目标位置
   }
   for (pos = 90; pos >= 0; pos -= 1)// 从0度逐渐转动到180度 每次负方向转动1度
   {
     myservo.write(pos);              
     delay(speed);                     
   }
 }