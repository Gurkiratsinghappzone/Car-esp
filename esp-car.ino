
  
  #define IN_1  15          // L298N in1 motors Rightx          GPIO15(D8)
  #define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
  #define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
  #define IN_4  0           // L298N in4 motors Left            GPIO0(D3)
  const int led=4; // led on (D2)
  int bzr = 5; // buzzer on(D1)
  int red=14; // red light on d5
  int led_state =LOW;
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h> 
  #include <ESP8266WebServer.h>
  
  String command;            
  int speedCar = 1023;        
  int speed_Coeff = 3;
  
  const char* ssid = "Nodemcu_Car"; // put WIFI SSID for creating AP     
  const char* pass = "myespcar"; // put WIFI password for creating AP
  ESP8266WebServer server(80);
  
  void setup() {

  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
 pinMode(bzr, OUTPUT); 
  pinMode(led, OUTPUT); 
    pinMode(red, OUTPUT); 
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
     
    digitalWrite(red,0);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
     
  }

void goBack(){
   
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
     
    digitalWrite(red,0);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      
  }

void goRight(){ 
     
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
     
    digitalWrite(red,0);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    
  }

void goLeft(){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
          digitalWrite(red,0);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
   
  }

void goAheadRight(){
    
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
        digitalWrite(red,0);
   }

void goAheadLeft(){
     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
         digitalWrite(red,0);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
}

void goBackRight(){ 
      
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
         digitalWrite(red,0);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
    
  }

void goBackLeft(){ 
     
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
     

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
     digitalWrite(red,0);
  }

void stopRobot(){  
  digitalWrite(red,1);
   
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
    

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
     
 }

void loop() {
   
   
    server.handleClient();
    
    
      command = server.arg("State");
      
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
     
      else if (command == "S") stopRobot();
      else if (command== "W") {
        digitalWrite(led,HIGH);
      }
      else if (command== "V"){
        digitalWrite(bzr,!led_state);
        led_state = !led_state;
      }
      else if(command=="5"){digitalWrite(led,1);
      }
      else if(command=="0"){digitalWrite(led,0);}
    digitalWrite(bzr,LOW);
     
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
