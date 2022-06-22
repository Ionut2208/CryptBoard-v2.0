#include <Adafruit_TFTLCD.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <stdint.h>
#include "TouchScreen.h"

#define LCD_CS A3
#define LCD_CD A2 
#define LCD_WR A1
#define LCD_RD A0 
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GOLD    0xEA8B02
#define GRAY  0xCCCCFF
#define L_YELLOW 0xCCCC00
#define PURPLE 0xCC0099

#define XP 7
#define YP A2
#define XM A1
#define YM 6

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint p;

void MorseTabelSimb()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);


  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("MORSE");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(0, 35);
  tft.print(" . = .-.-.-\n , = --..--\n ? = ..--..\n \' = .----.\n ! = -.-.--\n / = -..-.\n ( = -.--.\n ) = -.--.-\n & = .-...\n : = ---...\n ; = -.-.-.\n = = -...-\n + = .-.-.\n - = -....-\n _ = ..--.-\n\n \" = .-..-.\n");
  
  tft.fillRect(150, 280, 80, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(155, 285);
  tft.print("MENU");

  tft.fillRect(150, 235, 80, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(155, 240);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if(p.x >= 660 && p.x <= 910 && p.y >= 720 && p.y <= 800)
      {
        MorseTabelCifre();
        break;
      }
      else if(p.x >= 660 && p.x <= 910 && p.y >= 835 && p.y <= 930)
      {
        CypherMenuWiki();
        break;
      } 
       
     }
     delay(200);
  }
}

void MorseTabelCifre()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(YELLOW);
  
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("MORSE");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(0, 35);
  tft.print(" 0 = -----\n 1 = .----\n 2 = ..---\n 3 = ...--\n 4 = ....-\n 5 = .....\n 6 = -....\n 7 = --...\n 8 = ---..\n 9 = ----.");

  tft.fillRect(70, 250, 165, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(75, 255);
  tft.print("SIMBOLURI");

  tft.fillRect(130, 290, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(140, 295);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if(p.x >= 390 && p.x <= 915 && p.y >= 760 && p.y <= 840)
      {
        MorseTabelSimb();
        break;
      }
      else if(p.x >= 585 && p.x <= 910 && p.y >= 860 && p.y <= 930)
      {
        MorseTabelLitere();
        break;
      }
       
     }
     delay(200);
  }
}

void MorseTabelLitere()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("MORSE");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(0, 35);
  tft.print(" A = .-\n B = -...\n C = -.-.\n D = -..\n E = .\n F = ..-.\n G = --.\n H = ....\n I = ..\n J = .---\n K = -.-\n L = .-..\n M = --");
  tft.drawLine(115, 35, 115, 250, BLUE);
  tft.setCursor(120, 35);
  tft.print(" N = -.\n           O = ---\n           P = .--.\n           Q = --.-\n           R = .-.\n           S = ...\n           T = -\n           U = ..-\n           V = ...-\n           W = .--\n           X = -..-\n           Y = -.--\n           Z = --..");

  tft.fillRect(120, 260, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(125, 265);
  tft.print("CIFRE");

  tft.fillRect(0, 260, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(10, 265);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z); 
      if(p.x >= 560 && p.x <= 875 && p.y >= 790 && p.y <= 890)
      {
        MorseTabelCifre();
        break;
      }
      else if(p.x >= 150 && p.x <= 475 && p.y >= 785 && p.y <= 885)
      {
        MorseWiki();
        break;
      }
       
     }
     delay(200);
  }
}

void MorseWiki()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("MORSE");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("Codul Morse este o metoda de a trans- mite informatii fo-losind secvente    standardizate de   \"puncte\"si \"linii\",adica  semnale     lungi si scurte,   pentru caractere   specifice oricarui mesaj.");
  
  tft.fillRect(120, 250, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(125, 255);
  tft.print("TABEL");

  tft.fillRect(0, 250, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(10, 255);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
     /** Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); **/
      if(p.x >= 580 && p.x <= 870 && p.y >= 750 && p.y <= 850)
      {
        MorseTabelLitere();
        break;
      }
      else if(p.x >= 150 && p.x <= 475 && p.y >= 750 && p.y <= 850)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }

 
  
}

void CesarWiki()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("CESAR");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("Cifrul Cesar este ometoda cunoscuta decriptare a unui    text, fiecare lite-ra fiind inlocuita cu o litera aflata la un numar fix de pozitii in alfabet.\n\nExemplu: daca numa-rul de pozitii este3, \"copil\" devine  \"frslo\"");
  
  tft.fillRect(120, 250, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(130, 255);
  tft.print("BACK");

  

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
     /** Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); **/
      if(p.x >= 580 && p.x <= 870 && p.y >= 750 && p.y <= 850)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }

}

void HexExample()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("HEX");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("Obs: Resturile im- partirii mai mari  de 10 se reprezintacu litere incepand de la A\n\n\'L' are codul ASCII76\n76/16=4(rest 12)\n4/16=0(rest 4)\n12 se rep. cu B,   iar resturile se   iau invers\n=>\'J\' = 4B in HEX");

  tft.fillRect(120, 285, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(130, 290);
  tft.print("MENU");

  tft.fillRect(0, 285, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(10, 290);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); 
      if(p.x >= 145 && p.x <= 460 && p.y >= 845 && p.y <= 945)
      {
        HexWiki();
        break;
      }
      else if(p.x >= 530 && p.x <= 865 && p.y >= 845 && p.y <= 945)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }
}
void HexWiki()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(80, 5);
  tft.print("HEX");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("Orice caracter estereprezentat in me- moria computerelor prin intermediul   codurilor ASCII.\nReprezentarea unui caracter in HEX es-te valoarea in baza16 a codului ASCII corespunzator.");
  
  tft.fillRect(100, 250, 130, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(100, 255);
  tft.print("EXEMPLU");

  tft.fillRect(0, 250, 90, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(0, 255);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); 
      if(p.x >= 465 && p.x <= 890 && p.y >= 750 && p.y <= 850)
      {
        HexExample();
        break;
      }
      else if(p.x >= 145 && p.x <= 430 && p.y >= 750 && p.y <= 850)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }
}

void BinaryExample()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(60, 5);
  tft.print("BINARY");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("\'T\' are codul ASCII84\n84/2=42(rest 0)\n42/2=21(rest 0)\n21/2=10(rest 1)\n10/2=5(rest 0)\n5/2=2(rest 1)\n2/2=1(rest 0)\n1/2=0(rest 1)\n=>\'T\' = 1010100 in BINARY");

  tft.fillRect(120, 285, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(130, 290);
  tft.print("MENU");

  tft.fillRect(0, 285, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(10, 290);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); 
      if(p.x >= 145 && p.x <= 460 && p.y >= 845 && p.y <= 945)
      {
        BinaryWiki();
        break;
      }
      else if(p.x >= 530 && p.x <= 865 && p.y >= 845 && p.y <= 945)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }
}

void BinaryWiki()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(60, 5);
  tft.print("BINARY");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(0, 35);
  tft.print("Orice caracter estereprezentat in me- moria computerelor prin intermediul   codurilor ASCII.\nReprezentarea unui caracter in BINARY este valoarea in   baza 2 a codului   ASCII corespunzator");
  
  tft.fillRect(100, 250, 130, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(100, 255);
  tft.print("EXEMPLU");

  tft.fillRect(0, 250, 90, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(0, 255);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); 
      if(p.x >= 465 && p.x <= 890 && p.y >= 750 && p.y <= 850)
      {
        BinaryExample();
        break;
      }
      else if(p.x >= 145 && p.x <= 430 && p.y >= 750 && p.y <= 850)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }
}

void VigenereExample()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(50, 5);
  tft.print("VIGENERE");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("Text: InfoEducatie\nCheie: galaciuc\nRez.: OnqoGloegtte\n\nExplicatie:\nPozitia din alfabeta lui G e 7 si a   lui I e 9, deci 9 +7 - 1(se ia in     considerare litera curenta) = 15.     A 15-a litera din  alfabet este O.");

  tft.fillRect(120, 285, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(130, 290);
  tft.print("MENU");

  tft.fillRect(0, 285, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(10, 290);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); 
      if(p.x >= 145 && p.x <= 460 && p.y >= 845 && p.y <= 945)
      {
        VigenereWiki();
        break;
      }
      else if(p.x >= 530 && p.x <= 865 && p.y >= 845 && p.y <= 945)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }
}

void VigenereWiki()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(50, 5);
  tft.print("VIGENERE");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("Acest tip de crip- tare se bazeaza pe o cheie de criptarece este parcursa dela inceput pana la final pana la crip-tarea intregului   text, fiecare lite-ra fiind deplasata cu x pozitii din   alfabet, unde x    este pozitia din   alfabet a caracte- rului curent din   cheie.");


  tft.fillRect(100, 280, 130, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(100, 285);
  tft.print("EXEMPLU");

  tft.fillRect(0, 280, 90, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(0, 285);
  tft.print("BACK");

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); 
      if(p.x >= 465 && p.x <= 890 && p.y >= 840 && p.y <= 920)
      {
        VigenereExample();
        break;
      }
      else if(p.x >= 145 && p.x <= 430 && p.y >= 840 && p.y <= 920)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }

}

void AtbashWiki()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.setCursor(60, 5);
  tft.print("ATBASH");

  tft.setTextColor(BLUE);
  tft.setTextSize(2);
  tft.setCursor(5, 35);
  tft.print("In cifrul Atbash fiecare litera se inlocuieste cu litera opusa din alfabet(A devine Z, B devine Y, C devine X samd)\nExemplu: \"alfabet\" devine \"zouzyvg\"");
  
  tft.fillRect(120, 250, 100, 35, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(130, 255);
  tft.print("BACK");

  

  int ok = 0;
  while(!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
     /** Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n'); **/
      if(p.x >= 580 && p.x <= 870 && p.y >= 750 && p.y <= 850)
      {
        CypherMenuWiki();
        break;
      }
       
     }
     delay(200);
  }
}

void printCoord()
{
  Serial.print(p.x);
  Serial.print(' ');
  Serial.print(p.y);
  Serial.print('\n');
}

struct profil
{
  char Username[50];
  int HighScoreMorse, HighScoreCesar, HighScoreHex, HighScoreBinary, HighScoreVigenere, HighScoreAtbash;
  int Level;
  int FavoriteCypher;
  
}user[3];

void CypherMenuWiki()
{

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(CYAN);
  tft.setRotation(2);
  tft.fillRect(30, 10, 80, 80, RED);
  tft.fillRect(130, 10, 80, 80, RED);
  tft.fillRect(30, 110, 80, 80, RED);
  tft.fillRect(130, 110, 80, 80, RED);
  tft.fillRect(30, 210, 80, 80, RED);
  tft.fillRect(130, 210, 80, 80, RED);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.setCursor(40, 40);
  tft.print("MORSE");
  tft.setCursor(140, 40);
  tft.print("CESAR");
  tft.setCursor(50, 140);
  tft.print("HEX");
  tft.setCursor(137, 140);
  tft.print("BINARY");
  tft.setTextSize(2);
  tft.setCursor(50, 230);
  tft.print("VIGE\n    NERE");
  tft.setCursor(135, 240);
  tft.print("ATBASH");
  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setCursor(173, 296);
  tft.print("BACK");

  while(1)
  {
    
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      printCoord();
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
      }
     /** else if(p.x >= 230 && p.x <= 485 && p.y >= 175 && p.y <= 380)
      {
        MorseWiki();
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 175 && p.y <= 380)
      {
        CesarWiki();
      } **/
      else if(p.x >= 230 && p.x <= 485 && p.y >= 420 && p.y <= 615)
      {
        HexWiki();
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 420 && p.y <= 615)
      {
        BinaryWiki();
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 670 && p.y <= 865)
      {
        VigenereWiki();
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 670 && p.y <= 865)
      {
        AtbashWiki();
      }
      
    
    }
  }
}

void CypherMenuWork()
{

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(CYAN);
  tft.setRotation(2);
  tft.fillRect(30, 10, 80, 80, RED);
  tft.fillRect(130, 10, 80, 80, RED);
  tft.fillRect(30, 110, 80, 80, RED);
  tft.fillRect(130, 110, 80, 80, RED);
  tft.fillRect(30, 210, 80, 80, RED);
  tft.fillRect(130, 210, 80, 80, RED);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.setCursor(40, 40);
  tft.print("MORSE");
  tft.setCursor(140, 40);
  tft.print("CESAR");
  tft.setCursor(50, 140);
  tft.print("HEX");
  tft.setCursor(137, 140);
  tft.print("BINARY");
  tft.setTextSize(2);
  tft.setCursor(50, 230);
  tft.print("VIGE\n    NERE");
  tft.setCursor(135, 240);
  tft.print("ATBASH");
  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setCursor(173, 296);
  tft.print("BACK");
}

void CypherMenuPlay()
{

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(CYAN);
  tft.setRotation(2);
  tft.fillRect(30, 10, 80, 80, RED);
  tft.fillRect(130, 10, 80, 80, RED);
  tft.fillRect(30, 110, 80, 80, RED);
  tft.fillRect(130, 110, 80, 80, RED);
  tft.fillRect(30, 210, 80, 80, RED);
  tft.fillRect(130, 210, 80, 80, RED);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.setCursor(40, 40);
  tft.print("MORSE");
  tft.setCursor(140, 40);
  tft.print("CESAR");
  tft.setCursor(50, 140);
  tft.print("HEX");
  tft.setCursor(137, 140);
  tft.print("BINARY");
  tft.setTextSize(2);
  tft.setCursor(50, 230);
  tft.print("VIGE\n    NERE");
  tft.setCursor(135, 240);
  tft.print("ATBASH");
  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setCursor(173, 296);
  tft.print("BACK");
}

void Play()
{
  CypherMenuPlay();
  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      printCoord();
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
      }
      break;
    }
  }
}

void Work()
{
  CypherMenuWork();
  while(1)
  {
    printCoord();
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
      }
      break;
    }
  }
}

void Wiki()
{
  CypherMenuWiki();
}

void MainMenu()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(RED);
  tft.setRotation(2);
  tft.fillCircle(120, 50, 45, BLUE);
  tft.setCursor(97, 45);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print("PLAY");
  tft.fillCircle(120, 160, 45, BLUE);
  tft.setCursor(97, 155);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print("WORK");
  tft.fillCircle(120, 270, 45, BLUE);
  tft.setCursor(97, 265);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.print("WIKI");

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if(p.x >= 390 && p.x <= 700 && p.y >= 160 && p.y <= 380)
      {
        Play();
      }
      else if(p.x >= 390 && p.x <= 700 && p.y >= 430 && p.y <= 650)
      {
        Work();
      }
      else if(p.x >= 390 && p.x <= 700 && p.y >= 690 && p.y <= 920)
      {
        Wiki();
      }
      break;
    }
  }
}

void Intro()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 0, 239, 300, RED);
  tft.setCursor(0, 301);
  tft.setTextColor(L_YELLOW);
  tft.setTextSize(1);
  tft.print("CryptBoard v2.0, 2022");
  tft.setCursor(0, 310);
  tft.setTextColor(L_YELLOW);
  tft.setTextSize(1);
  tft.print("Designed and created by Ionut Bene");
  tft.setCursor(40, 20);
  tft.setTextColor(BLUE);
  tft.setTextSize(4);
  tft.print("WELCOME");
  delay(1200);
  tft.setCursor(100, 70);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.print("TO");
  delay(1200);
  tft.setCursor(30, 120);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.print("Crypt");
  delay(1500);
  tft.setCursor(120, 120);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.print("Board");
  delay(3000);
  tft.setCursor(0, 265);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Press anywhere to  continue...");
  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      MainMenu();
      break;
    }
  }
}

void setup() {
  tft.reset();
  tft.begin(0x8357);
  tft.fillScreen(BLACK);
  tft.setRotation(2);
  Serial.begin(9600);
  Intro();
}

void loop() {
   

}