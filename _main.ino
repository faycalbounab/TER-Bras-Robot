/*
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi module (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your board is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)
 * LED attached to pin 9

 created 25 Nov 2012
 by Tom Igoe
 */
 
#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 




Plateau plateau = Plateau();
float initX = 19.15;
float initY = 10.5;
float initStock = 11;
float decalCase = 5.7;
int duree = 300;

// pion, tour, cavalier, fou, reine 
float ouverture[5] = {3.5,4.5,4.5,4.5,4.5};
float fermeture[5] = {1.5, 2.2, 1.8, 2, 2.4};
float hauteur[5] = {3,5,3,3.5,5};



char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)


int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(30000);
  }
  server.begin(); 
  pwm.begin();
  pwm.setPWMFreq(60);// start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  String finishline = ""; 
  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client 
    finishline = "";
    int nbmessage=0;
  while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n' && !nbmessage) {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.println("<!doctype html>");
            client.println("<html><head>");
            client.println("<script type='text/javascript'>");
            client.println("lettres=['A','B','C','D','E','F','G','H'];");
            client.println("style=['gainsboro','#3F2204'];");
            client.println("var prec;");
            client.println("var precstyle;");
            client.println("var precstyleb;");
            client.println("function constr(){");
            client.println("for(i=0;i<lettres.length;i++)");
            client.println("{");
            client.println("for(j=0;j<8;j++)");
            client.println("{  var code='';");
            client.println("code+='<span onclick=\\\'test(this);\\\'';");
            client.println("code+='style=\\\'cursor:pointer;text-align:center;vertical-align:middle;';");
            client.println("code+='background-color:'+style[(j+i)%2]+';color:'+style[(j+i+1)%2]+';';");
            client.println("code+='margin-left:'+(10+50*i)+'px;margin-top:'+(10+50*j)+'px;position:absolute;padding:10px;width:20px;height:20px\\\'>';");
            client.println("code+=lettres[i]+''+(8-j)+'</span>';");
            client.println("document.getElementById('id').innerHTML+=code;");
            client.println("}");
            client.println("}}");
            client.println("function test(elm)");
            client.println("{");
            client.println("if(prec!=null)");
            client.println("{prec.style.color=precstyle;");
            client.println("prec.style.backgroundColor=precstyleb;");
            client.println("document.getElementById('formu').innerHTML+='-';");
            client.println("}");
            client.println("precstyle=elm.style.color;");
            client.println("precstyleb=elm.style.backgroundColor;");
            client.println("elm.style.color='maroon';");
            client.println("elm.style.backgroundColor='gold';");
            client.println("document.getElementById('formu').innerHTML+=elm.innerHTML;");
            client.println("prec=elm;");
            client.println("}");
            client.println("function effacer()");
            client.println("{");
            client.println("document.getElementById('formu').innerHTML='';");
            client.println("if(prec!=null){");
            client.println("prec.style.color=precstyle;");
            client.println("prec.style.backgroundColor=precstyleb;");
            client.println("prec=null;");
            client.println("}}");
            client.println("</script>");
            client.println("</head><body onload='constr();'>");
            client.println("<div id='id'>");
            client.println("<span onclick='test(this);' style='cursor:pointer;text-align:center;vertical-align:middle;background-color:DarkKhaki;margin-left:10px;margin-top:410px;position:absolute;padding:10px;width:370px;height:20px'>P</span>");
            client.println("</div>");
            client.println("<form style='position:absolute;margin-left:410px;margin-top:10px;'>");
            client.println("<textarea style='width:385px;height:385px' name='ordre' id='formu'></textarea>");
            client.println("<div>");
            client.println("<button type='submit' style='cursor:pointer;width:190px;height:40px;margin-top:5px;'>Envoyer</button>");
            client.println("</div></form>");
            client.println("<button onclick='effacer()' style='position:absolute;cursor:pointer;width:190px;height:40px;margin-top:410px;margin-left:612px;'>Effacer</button>");
            client.println("");
            client.println("</body>");
            client.println("</html>");
      
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
      finishline+=currentLine;
      currentLine = "";
      
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        
      }
    
      }
      //a changer
    Serial.println("ui");
    Serial.println(finishline);
    int pos = finishline.indexOf("GET /?ordre=");
    if(pos!=-1){
      String instruction = finishline.substring(pos + 12,pos+17);
      Serial.println(instruction);
      int x,y,z,piece;
  int coeff1x, coeff1y, coeff2x, coeff2y;

      coeff1y = 72 - instruction.charAt(0);
  coeff1x = instruction.charAt(1) - 49;
  coeff2y = 72 - instruction.charAt(3);
  coeff2x = instruction.charAt(4) - 49;


  if(plateau.getEchiquier(coeff2x, coeff2y) != 0){  
    piece = plateau.getEchiquier(coeff2x, coeff2y) - 1; //numero de la piece à prendre
    float deplaceY = initY+abs(coeff2x-7)*decalCase;
    if(deplaceY > 25){deplaceY -= 1;}
    mouvementBras(initX-abs(coeff2y-7)*decalCase, initY+abs(coeff2x-7)*decalCase, hauteur[piece], ouverture[piece], fermeture[piece], 0); // prendre la piece qui gene
    mouvementBras(initStock + plateau.getN() * decalCase, 2, hauteur[piece]+0.5, ouverture[piece], fermeture[piece], 1); // la déposer dans le stock
    
    plateau.setN(plateau.getN() + 1);
  }
 
  float deplaceY1 = initY+abs(coeff1x-7)*decalCase;
  if(deplaceY1 > 25){deplaceY1 -= 1;}
  float deplaceY2 = initY+abs(coeff2x-7)*decalCase;
  if(deplaceY2 > 25){deplaceY2 -= 1;}
    
  piece = plateau.getEchiquier(coeff1x, coeff1y) - 1; //numero de la piece à prendre
  mouvementBras(initX-abs(coeff1y-7)*decalCase, deplaceY1, hauteur[piece], ouverture[piece], fermeture[piece], 0); //prise de la piece
  mouvementBras(initX-abs(coeff2y-7)*decalCase, deplaceY2, hauteur[piece], ouverture[piece], fermeture[piece], 1); //poser la pièce

  plateau.setEchiquier(coeff2x, coeff2y, plateau.getEchiquier(coeff1x, coeff1y));
  plateau.setEchiquier(coeff1x, coeff1y, 0);
      
    }
    else{
      Serial.println(pos);
    }
    // close the connection:
    finishline="";
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void mouvementBras(float x, float y, float z, float ouverturePince, float fermeturePince, int typeMouvement){

  Serial.print("X ");
   Serial.println(x);

   Serial.print("Y ");
   Serial.println(y);

   Serial.print("Z ");
   Serial.println(z);

   //CALCULE DES ANGLES
   int* tab = new int[5];
   tab = calculeAngleVariateur42(x,y,z);
   Serial.print("angle0 ");
   Serial.println(tab[0]);
   Serial.print("angle1 ");
   Serial.println(tab[1]);
   Serial.print("angle2 ");
   Serial.println(tab[2]);
   Serial.print("angle3 ");
   Serial.println(tab[3]);

    
   //DEBUT DU MOUVEMENT : GESTION DE LA PINCE
   servo4.moveValeur(servo4.calculeMoveDegre(90));
   if(typeMouvement == 0){
     servo5.moveValeur(cmTValeurServo5(ouverturePince));
     delay(duree);
   }

   //DESCENTE
   servo0.moveValeur(servo0.calculeMoveDegre(tab[0]));
   //delay(duree);
   servo3.moveValeur(servo3.calculeMoveDegre(tab[3]));
   delay(duree);
   servo2.moveValeur(servo2.calculeMoveDegre(tab[2]));
   delay(duree);
   servo1.moveValeur(servo1.calculeMoveDegre(tab[1]));
   delay(duree);
  

   //PINCE EN BAS DU MOUVEMENT
   if(typeMouvement == 0){
     servo5.moveValeur(cmTValeurServo5(fermeturePince));
   }
   else{
     servo5.moveValeur(cmTValeurServo5(ouverturePince));
   }

   //REMONTE
   servo1.moveValeur(servo1.calculeMoveDegre( 110 ));
   delay(duree);
   Serial.println("");

   
}
