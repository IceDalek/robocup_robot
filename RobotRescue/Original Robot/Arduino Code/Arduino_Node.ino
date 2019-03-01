#include <ros.h>
#include <std_msgs/Char.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::Char& toggle_msg){
  switch("Here must be a varaible of msg"){
  case 'H':
  blink(2);   
  break;
  case 'S':
  blink(3);   
  break;
  case 'U':
  blink(4);   
  break;
  }
}

ros::Subscriber<std_msgs::Char> sub("cam", &messageCb);

void blink(int n)
{
  for(int i=0;i<n;i++)
  {
    digitalWrite(13, HIGH-digitalRead(13));
    delay(10);
    digitalWrite(13, HIGH-digitalRead(13));
    delay(10);
  }
}

void setup()
{ 
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}

