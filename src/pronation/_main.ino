/*
 ******************************************************************************
 * 
 * Copyright (c) 2019 Groupe : Berriri Mehdi, Bounab Fayçal, Djema Sofiane, Doglio Arthur
 * All rights reserved.
 * 
 * Ce projet s'inscrit dans le cadre d'un Travail d'Etude et de Recherche de Master 1 Informatique.
 *
 * Notice d'utilisation:
 * 
 * Pour lancer le projet, on doit d'abord connecter les différents fils du bras à la carte Arduino.
 * Ils doivent être connecté en les prenant de bas en haut sur les ports 0 à 5 de la carte.
 * Il faut ensuite séléctionner le type de carte : UNO WIFI REV2.
 * Dans le fichier arduino_secrets.h, il faut écrire le nom de votre réseau ainsi que le mot de passe.
 * Une fois ces étape finies, on téléverse le code dans la carte. 
 * On attend que la carte se connecte à votre réseau.
 * Puis on connecte l'ordinateur au même réseau que la carte et on entre dans le navigateur l'IP du réseau wifi (l'adresse s'affiche sur la console de l'IDE).
 * Enfin, on entre le coup qu'on veut jouer et on appuie sur "Envoyer".
 *
 ******************************************************************************
 */

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 

//******************************************** Les variables globales ********************************************//

Servo servo0 = Servo(0, 90, 580, 200, 2.45, 0, 10);
Servo servo1 = Servo(1, 90, 475, 250, 2.5, 154, 10);
Servo servo2 = Servo(2, 100, 580, 530, 2.5, 5, 10);
Servo servo3 = Servo(3, 90, 390, 250, 2.5, 10, 10); 
Servo servo4 = Servo(4, 90, 570, 290, 100/45, 0, 10);
Servo servo5 = Servo(5, 190, 310, 200, 100/45, 0, 10); 
Plateau plateau = Plateau();
float initX = 19.15; // coordonnée en x de la case A8
float initY = 10.5; // coordonnée en y de la case A8
float initStock = 11; // coordonnée en x de la première pièce adverse que le bras prend
float decalCase = 5.7; // taille d'une case du plateau d'échec sur lequel nous jouons
int duree = 300; // le temps de delais en milliseconde entre le déplacement de chaque Servo lors d'un mouvement

// les tableaux suivant donnent, dans l'ordre, les valeur du pion, de la tour, du cavalier, du fou et de la reine (et roi) en centimètre.
float ouverture[5] = {3.5, 4.5, 4.5, 4.5, 4.5};
float fermeture[5] = {1.5, 1.8, 1.8, 1.5, 1.8};
float hauteur[5] = {3, 4, 2, 3.5, 5};


char ssid[] = SECRET_SSID; // nom du réseau
char pass[] = SECRET_PASS; // mot de passe du réseau

int status = WL_IDLE_STATUS;
WiFiServer server(80);


//******************************************** Le Serveur ********************************************//
void setup() {
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attend de se connecter à un réseau wifi
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid); // affiche le nom du réseau (SSID);

    status = WiFi.begin(ssid, pass);
    delay(20000); // attend 20 secondes pour la connexion
  }
  server.begin(); // start the web server on port 80
  pwm.begin();
  pwm.setPWMFreq(60);
  printWifiStatus(); // affiche le statut

}


void loop() {
  WiFiClient client = server.available();  
  String finishline = ""; 
  if (client) {                    
    Serial.println("new client");        
    String currentLine = "";          
    finishline = "";
    int nbmessage=0;
  while (client.connected()) {         
      if (client.available()) {         
        char c = client.read();         
        Serial.write(c);                
        if (c == '\n' && !nbmessage) {  
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

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
            client.println();
            break;
          } 
          else {
            finishline+=currentLine;
            currentLine = "";
          }
        } 
        else if (c != '\r') { 
          currentLine += c;
        }
      }
    }
    Serial.println(finishline);
    int pos = finishline.indexOf("GET /?ordre=");
    if(pos!=-1){
      String instruction = finishline.substring(pos + 12,pos+17);
      Serial.println(instruction);
     
      jouer(instruction); // joue le coup donné en instruction
      
    }
    else{
      Serial.println(pos);
    }
    // ferme la connexion
    finishline="";
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}



//******************************************** Les méthodes de jeu ********************************************//

// permet d'effectuer un coup d'échec passé en paramètre
void jouer(String instruction){
  int coeff1x, coeff1y, coeff2x, coeff2y, piece;
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
  float deplaceY2 = initY+abs(coeff2x-7)*decalCase;
  if(deplaceY1 > 25){deplaceY1 -= 1;}
  if(deplaceY2 > 25){deplaceY2 -= 1;}
    
  piece = plateau.getEchiquier(coeff1x, coeff1y) - 1; //numero de la piece à prendre
  mouvementBras(initX-abs(coeff1y-7)*decalCase, deplaceY1, hauteur[piece], ouverture[piece], fermeture[piece], 0); //prise de la piece
  mouvementBras(initX-abs(coeff2y-7)*decalCase, deplaceY2, hauteur[piece], ouverture[piece], fermeture[piece], 1); //poser la pièce

  plateau.setEchiquier(coeff2x, coeff2y, plateau.getEchiquier(coeff1x, coeff1y));
  plateau.setEchiquier(coeff1x, coeff1y, 0);
}

// permet de prendre (typeMouvement = 0) ou poser (typeMouvement != 0) une pièce.
void mouvementBras(float x, float y, float z, float ouverturePince, float fermeturePince, int typeMouvement){

   //***************** calcul des angles *****************//
   int* tab = new int[4]; // le tableau où sont enregistré les angles des articulations 0 à 3.
   calculAnglesArticulation(x,y,z,tab);
   Serial.print("angle0 ");
   Serial.println(tab[0]);
   Serial.print("angle1 ");
   Serial.println(tab[1]);
   Serial.print("angle2 ");
   Serial.println(tab[2]);
   Serial.print("angle3 ");
   Serial.println(tab[3]);

    
   //***************** début du mouvement : gestion de la pince *****************//
   servo4.moveValeur(servo4.calculMoveDegre(90));
   if(typeMouvement == 0){
     servo5.moveValeur(cmTValeurServo5(ouverturePince));
     delay(duree);
   }

   //***************** descente du bras *****************//
   servo0.moveValeur(servo0.calculMoveDegre(tab[0]));
   servo3.moveValeur(servo3.calculMoveDegre(tab[3]));
   delay(duree);
   servo2.moveValeur(servo2.calculMoveDegre(tab[2]));
   delay(duree);
   servo1.moveValeur(servo1.calculMoveDegre(tab[1]));
   delay(duree);
  

   //***************** gestion de la pince en bas du mouvement *****************
   if(typeMouvement == 0){
     servo5.moveValeur(cmTValeurServo5(fermeturePince));
   }
   else{
     servo5.moveValeur(cmTValeurServo5(ouverturePince));
   }

   //***************** remonté du bras *****************//
   if(abs(90 - tab[2]) + abs(90 - tab[2]) < 40){
    servo1.moveValeur(servo1.calculMoveDegre( 140 ));
   }
   else{
    servo1.moveValeur(servo1.calculMoveDegre( 110 ));
   }
   delay(duree);
   
   Serial.println("");
}
