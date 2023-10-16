int ledpin = 13;  //定义数字接口D13接LED
int pin = 2;      //定义数字检测接口D2
int val;          //定义变量
void setup() {
  pinMode(pin，INPUT);  // 红外寻迹连接引脚D2，并设置为输入模式
  pinMode(ledpin，OUTPUT); //设定数字接口13为输出接口
  serial.begin(9600);//设置串门波特率为9600kbps
  }
void loop() {
  val = digitalRead(pin);  //读取数字接口的值
  Serial.printIn(val);//输出输出接门的值
  if (val == 1) //如果pin2检测的值为高电平，点亮LED
  {
  digitalwrite(ledpin，LOw);
  }
  else{//如果为低电平熄灭LED
    digitalwrite(ledpin，HIGH); 
    }}