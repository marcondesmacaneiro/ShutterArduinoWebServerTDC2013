/*
  Web Shotter Server
 
 A simple web server that control a shotter.
 
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 20 Mar 2013
 by Marcondes Maçaneir
 */

#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
IPAddress ip(192,168,2, 177);

int ligaLed; 
String rd; 

// HTTP port
EthernetServer server(80);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }


  //start the Ethernet server:
  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  pinMode(2,OUTPUT); 
  pinMode(3,OUTPUT); 
  pinMode(4,OUTPUT); 
  pinMode(5,OUTPUT); 
   
  ligaMotor = 0;
   
  rd = "rd=0"; 
}


void loop() {
  
  EthernetClient client = server.available();
  
  if (client) {
    Serial.println("new client");
  
    boolean currentLineIsBlank = true;
    String get;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        get.concat(c);

        if (c == '\n' && currentLineIsBlank) {
          //standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
                    // add a meta refresh tag, 5 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          client.println("<body>");
          
          if (get.substring(6,10) == "rd=1") {
            ligaMotor = 1;
            rd = "rd=1";
            Serial.write("rd=1");
          } else {
            if(get.substring(6,10) == "rd=2") {
              ligaMotor = 2;
              rd = "rd=2";
              Serial.write("rd=2");
             } else {
               if(get.substring(6,10) == "rd=3") {
                 ligaMotor = 3;
                 rd = "rd=3";
                 Serial.write("rd=3");
                } else {
                  if(get.substring(6,10) == "rd=4") {
                    ligaMotor = 4;
                    rd = "rd=4";
                    Serial.write("rd=4"); 
                   }
                }
             }
          }
              
          client.print("<form method='get'>");
              if (rd == "rd=1") {
                client.print("<input type='radio' value='1' checked name='rd' > Abrir Lamina<br>");
                client.print("<input type='radio' value='2' name='rd' > Fechar Lamina<br>"); 
                client.print("<input type='radio' value='3' name='rd' > Fecha Persiana<br>"); 
                client.print("<input type='radio' value='4' name='rd' > Abre Persiana<br>"); 
              } else {
                if (rd == "rd=2") {
                  client.print("<input type='radio' value='1' name='rd' > Abrir Lamina<br>");
                  client.print("<input type='radio' value='2' checked name='rd' > Fechar Lamina<br>"); 
                  client.print("<input type='radio' value='3' name='rd' > Fecha Persiana<br>"); 
                  client.print("<input type='radio' value='4' name='rd' > Abre Persiana<br>"); 
                } else {
                  if (rd == "rd=3") {
                    client.print("<input type='radio' value='1' name='rd' > Abrir Lamina<br>");
                    client.print("<input type='radio' value='2' name='rd' > Fechar Lamina<br>"); 
                    client.print("<input type='radio' value='3' checked name='rd' > Fecha Persiana<br>"); 
                    client.print("<input type='radio' value='4' name='rd' > Abre Persiana<br>"); 
                  } else {
                    if (rd == "rd=4") {
                      client.print("<input type='radio' value='1' name='rd' > Abrir Lamina<br>");
                      client.print("<input type='radio' value='2' name='rd' > Fechar Lamina<br>"); 
                      client.print("<input type='radio' value='3' name='rd' > Fecha Persiana<br>"); 
                      client.print("<input type='radio' value='4' checked name='rd' > Abre Persiana<br>"); 
                    } else {
                      client.print("<input type='radio' value='1' name='rd' > Abrir Lamina<br>");
                      client.print("<input type='radio' value='2' name='rd' > Fechar Lamina<br>"); 
                      client.print("<input type='radio' value='3' name='rd' > Fecha Persiana<br>"); 
                      client.print("<input type='radio' value='4' name='rd' > Abre Persiana<br>");  
                     }
                  }

               }
             }
             client.print("<input type=submit value='Submit'></form>");          
             client.println("</body>");
             client.println("</html>");
             break;
          }
          if (c == '\n') {
            currentLineIsBlank = true;
          } else if (c != '\r') {
            currentLineIsBlank = false;
          }
          if(ligaMotor == 1){
            digitalWrite(5, LOW);
            digitalWrite(4, LOW);
            digitalWrite(3, LOW);
            digitalWrite(2, HIGH);
          } else {
            if (ligaMotor == 2){
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
             } else{
               if (ligaMotor == 3){ 
                 digitalWrite(5, LOW);
                 digitalWrite(2, LOW);
                 digitalWrite(3, LOW);
                 digitalWrite(4, HIGH);
                } else {
                  if (ligaMotor == 4){ 
                    digitalWrite(4, LOW);
                    digitalWrite(2, LOW);
                    digitalWrite(3, LOW);
                    digitalWrite(5, HIGH);
                  }
               }
            }
         }
       }
    }

    delay(1);
    
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

