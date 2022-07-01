#include <MCUFRIEND_kbv.h>
#include "TouchScreen.h"
#include <EEPROM.h>

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

MCUFRIEND_kbv tft;
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
  tft.print("In cifrul Atbash   fiecare litera se  inlocuieste cu litera opusa din alfa  bet(A devine Z, B  devine Y, C devine X samd)\nExemplu: \"alfabet\" devine \"zouzyvg\"");
  
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
        break;
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 175 && p.y <= 380)
      {
        MorseWiki();
        break;
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 175 && p.y <= 380)
      {
        CesarWiki();
        break;
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 420 && p.y <= 615)
      {
        HexWiki();
        break;
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 420 && p.y <= 615)
      {
        BinaryWiki();
        break;
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 670 && p.y <= 865)
      {
        VigenereWiki();
        break;
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 670 && p.y <= 865)
      {
        AtbashWiki();
        break;
      }
      
    
    }
  }
}

char sir[300], cheie[300];
int mode = 1, len, len_key;
bool isKey = true, smaller = false, isVig = false;

void CypherMenuWork()
{

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(CYAN);
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
      
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
        break;
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 175 && p.y <= 380)
      {
        CryptDecryptMenuMorse();
        break;
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 175 && p.y <= 380)
      {
        CryptDecryptMenuCesar();
        break;
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 420 && p.y <= 615)
      {
        CryptDecryptMenuHex();
        break;
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 420 && p.y <= 615)
      {
        CryptDecryptMenuBinary();
        break;
      }
      else if(p.x >= 230 && p.x <= 485 && p.y >= 670 && p.y <= 865)
      {
        CryptDecryptMenuVigenere();
        break;
      }
      else if(p.x >= 560 && p.x <= 835 && p.y >= 670 && p.y <= 865)
      {
        CaseAtbash();
        break;
      }
      
    
    }
  }
  return;
}

void CypherMenuPlay()
{

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(CYAN);
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

void ProfileMenu()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillScreen(BLUE);

  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  tft.fillRect(0, 40, 60, 60, GRAY);
  tft.fillRect(25, 50, 10, 40, BLACK);
  tft.fillRect(10, 65, 40, 10, BLACK);

  tft.setCursor(75, 65);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Adauga profil");

  tft.fillRect(0, 120, 60, 60, GRAY);
  tft.fillRect(10, 145, 20, 10, BLACK);
  tft.fillTriangle(30, 135, 30, 165, 50, 150, BLACK);
  tft.setCursor(70, 145);
  tft.print("Incarca profil");

  tft.fillRect(0, 200, 60, 60, GRAY);
  int x1 = 5, y1 = 210, x2 = 50, y2 = 250;
  for(int i = 1; i <= 7; i++)
    tft.drawLine(x1++, y1, x2++, y2, BLACK);
  x1 = 50;
  y1 = 210;
  x2 = 5;
  y2 = 250;
  for(int i = 1; i <= 7; i++)
    tft.drawLine(x1++, y1, x2++, y2, BLACK);
  tft.setCursor(75, 225);
  tft.print("Sterge profil");
}

void getTasteProfileMenu()
{
  while(1)
  {
    TSPoint p = ts.getPoint();
    if(p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if(p.x >= 160 && p.x <= 325)
      {
        if(p.y >= 260 && p.y <= 390)
          Serial.print("add\n");
        else if(p.y >= 445 && p.y <= 575)
          Serial.print("load\n");
        else if(p.y >= 630 && p.y <= 760)
          Serial.print("delete\n");
      }
    }
    delay(300);
  }
  
  
}

void Play()
{
  ProfileMenu();
  getTasteProfileMenu();
}

String morse(char c)
{
  if(c >= 'a' && c <= 'z')
        c -= 32;

    if(c == 'A')
        return ".-";
    if(c == 'B')
        return "-...";
    if(c == 'C')
        return "-.-.";
    if(c == 'D')
        return "-..";
    if(c == 'E')
        return ".";
    if(c == 'F')
        return "..-.";
    if(c == 'G')
        return "--.";
    if(c == 'H')
        return "....";
    if(c == 'I')
        return "..";
    if(c == 'J')
        return ".---";
    if(c == 'K')
        return "-.-";
    if(c == 'L')
        return ".-..";
    if(c == 'M')
        return "--";
    if(c == 'N')
        return "-.";
    if(c == 'O')
        return "---";
    if(c == 'P')
        return ".--.";
    if(c == 'Q')
        return "--.-";
    if(c == 'R')
        return ".-.";
    if(c == 'S')
        return "...";
    if(c == 'T')
        return "-";
    if(c == 'U')
        return "..-";
    if(c == 'V')
        return "...-";
    if(c == 'W')
        return ".--";
    if(c == 'X')
        return "-..-";
    if(c == 'Y')
        return "-.--";
    if(c == 'Z')
        return "--..";
    if(c == '0')
        return "-----";
    if(c == '1')
        return ".----";
    if(c == '2')
        return "..---";
    if(c == '3')
        return "...--";
    if(c == '4')
        return "....-";
    if(c == '5')
        return ".....";
    if(c == '6')
        return "-....";
    if(c == '7')
        return "--...";
    if(c == '8')
        return "---..";
    if(c == '9')
        return "----.";
    if(c == ',')
        return "--..--";
    if(c == '.')
        return ".-.-.-";
    if(c == '?')
        return "..--..";
    if(c == ';')
        return "-.-.-.";
    if(c == ':')
        return "---...";
    if(c == '/')
        return "-..-.";
    if(c == '-')
        return "-....-";
    if(c == '(')
        return "-.--.";
    if(c == ')')
        return "-.--.-";
    if(c == '_')
        return "..--.-";
    if(c == '@')
        return ".--.-.";
    if(c == '!')
        return "-.-.--";
    if(c == '&')
        return ".-...";
    if(c == '=')
        return "-...-";
    if(c == '+')
        return ".-.-.";
    if(c == '$')
        return "...-..-";
    if(c == ' ')
        return "/";
    return "x";
}

void tast_litere()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillRect(0, 170, 239, 150, BLACK);
  tft.drawRect(5, 185, 185, 120, YELLOW);
  tft.setCursor(10, 190);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("QWERTYUIOP");
  tft.setCursor(20, 220);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("ASDFGHJKL");
  tft.setCursor(30, 250);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("ZXCVBNM");
  tft.fillRect(195, 280, 40, 30, GRAY);
  tft.setCursor(200, 285);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.print("OK");
  tft.fillRect(195, 200, 40, 30, GRAY);
  tft.setCursor(200, 205);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.print("<-");
  tft.fillRect(195, 240, 40, 30, GRAY);
  tft.setCursor(200, 245);
  tft.setTextColor(MAGENTA);
  tft.setTextSize(3);
  tft.print("?1");
  tft.setCursor(50, 280);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.print("SPACE");
  tft.drawRect(45, 275, 100, 30, YELLOW);

  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");


  tft.fillRect(195, 171, 45, 25, GREEN);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.setCursor(210, 173);
  tft.print('-');

  tft.setTextSize(2);
  
}

void tast_cif_simb()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillRect(0, 170, 239, 150, BLACK);
  tft.drawRect(5, 185, 185, 120, YELLOW);
  tft.setCursor(10, 190);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("1234567890");
  tft.setCursor(10, 220);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("@.$_&-+()/");
  tft.setCursor(10, 250);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("<*':;!?=%>");
  tft.setCursor(10, 280);
  tft.print(',');
  tft.setCursor(150, 280);
  tft.print('\"');
  tft.fillRect(195, 280, 40, 30, GRAY);
  tft.setCursor(200, 285);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.print("OK");
  tft.fillRect(195, 200, 40, 30, GRAY);
  tft.setCursor(200, 205);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.print("<-");
  tft.fillRect(195, 240, 40, 30, GRAY);
  tft.setCursor(200, 245);
  tft.setTextColor(MAGENTA);
  tft.setTextSize(3);
  tft.print("AB");
  tft.setCursor(52, 280);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.print("SPACE");
  tft.drawRect(45, 275, 100, 30, YELLOW);

  tft.fillRect(195, 171, 45, 25, GREEN);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.setCursor(210, 173);
  tft.print('-');

  tft.setTextSize(2);
}

void afisare_sir()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.setTextColor(RED);
  if(len == 134)
  {
    textbox();
    smaller = true;
  }
    
  if(smaller == true)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  tft.setCursor(5, 45);
  tft.print(sir);
}

void displayChar(char x)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  if(isVig == true && isKey == true && !litera(x))
    error_message();
  else
  {
    sir[len++] = x;
    afisare_sir();
  }
  
      
}

void textbox()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 40, 239, 130, WHITE);
  

}

void MorseEncrypt()
{
  tft.setTextSize(2);
  int l = 0, val_endl = 19;
  String result[100];
  for(int i = 0; i < 100; i++)
      result[i] = "\0";
  textbox();
  for(int i = 0; sir[i] != 0; i++)
  {
    result[i] = morse(sir[i]);
    l += result[i].length();
  }
  tft.setCursor(5, 45);
  if(smaller == true || l >= 134)
  {
    tft.setTextSize(1);
    val_endl = 35;
  }
  int lungRand = 0;
  for(int i = 0; result[i] != 0; i++)
  {
    lungRand += result[i].length();
    if(lungRand <= val_endl)
    {
      tft.print(result[i]);
      if(lungRand < val_endl)
      {
        tft.print(' ');
        lungRand++;
      }
    }
    else
    {
      tft.print('\n');
      lungRand = result[i].length();
      tft.print(result[i]);
      if(lungRand < 19)
      {
        tft.print(' ');
        lungRand++;
      }
    }
  }
  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    } 
    
  }
    
}

void error_message()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, RED);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Caracter neacceptat");

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(107, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("OK");

  while(1)
  {
    TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z); 
      if(p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        textbox();
        afisare_sir();
        break;
      }
    }
  
  }
}

void resetString()
{
  for(int i = 0; i < len; i++)
    sir[i] = 0;
  for(int i = 0; i < len_key; i++)
    cheie[i] = 0;
  len = 0;
  len_key = 0;
  mode = 1;
  isKey = true;
  smaller = false;
  isVig = false;
}

void GetTasteMorseEncrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          Serial.print("OK");
          MorseEncrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          Serial.print("OK");
          sir[len] = 0;
          MorseEncrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
         error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          error_message();
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
     else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
   delay(200);
  }
}

char Morse(String s)
{
  if(s == ".-")
        return 'A';
    if(s == "-...")
        return 'B';
    if(s == "-.-.")
        return 'C';
    if(s == "-..")
        return 'D';
    if(s == ".")
        return 'E';
    if(s == "..-.")
        return 'F';
    if(s == "--.")
        return 'G';
    if(s == "....")
        return 'H';
    if(s == "..")
        return 'I';
    if(s == ".---")
        return 'J';
    if(s == "-.-")
        return 'K';
    if(s == ".-..")
        return 'L';
    if(s == "--")
        return 'M';
    if(s == "-.")
        return 'N';
    if(s == "---")
        return 'O';
    if(s == ".--.")
        return 'P';
    if(s == "--.-")
        return 'Q';
    if(s == ".-.")
        return 'R';
    if(s == "...")
        return 'S';
    if(s == "-")
        return 'T';
    if(s == "..-")
        return 'U';
    if(s == "...-")
        return 'V';
    if(s == ".--")
        return 'W';
    if(s == "-..-")
        return 'X';
    if(s == "-.--")
        return 'Y';
    if(s == "--..")
        return 'Z';
    if(s == "-----")
        return '0';
    if(s == ".----")
        return '1';
    if(s == "..---")
        return '2';
    if(s == "...--")
        return '3';
    if(s == "....-" )
        return '4';
    if(s == ".....")
        return '5';
    if(s == "-....")
        return '6';
    if(s == "--...")
        return '7';
    if(s == "---..")
        return '8';
    if(s == "----.")
        return '9';
    if(s == "--..--")
        return ',';
    if(s == ".-.-.-" )
        return '.';
    if(s == "..--..")
        return '?';
    if(s == "-.-.-.")
        return ';';
    if(s == "---...")
        return ':';
    if(s == "-..-.")
        return '/';
    if(s == "-....-")
        return '-';
    if(s == "-.--.")
        return '(';
    if(s == "-.--.-")
        return ')';
    if(s == "..--.-")
        return '_';
    if(s == ".--.-.")
        return '@';
    if(s == "-.-.--")
        return '!';
    if(s == ".-...")
        return '&';
    if(s == "-...-")
        return '=';
    if(s == ".-.-.")
        return '+';
    if(s == "...-..-")
        return '$';
    if(s == "/")
        return ' ';
    return 0;
}

void TastMorseDecrypt()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(5, 185, 235, 135, BLACK);
  tft.drawRect(5, 185, 185, 120, YELLOW);
  
  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  tft.fillRect(195, 280, 40, 30, GRAY);
  tft.setCursor(200, 285);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.print("OK");

  tft.fillRect(195, 200, 40, 30, GRAY);
  tft.setCursor(200, 205);
  tft.setTextColor(RED);
  tft.setTextSize(3);
  tft.print("<-");

  tft.setCursor(50, 280);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.print("SPACE");
  tft.drawRect(45, 275, 100, 30, YELLOW);

  tft.drawRect(5, 185, 60, 90, YELLOW);
  tft.drawRect(65, 185, 60, 90, YELLOW);
  tft.drawRect(125, 185, 65, 90, YELLOW);

  tft.setTextSize(3);
  tft.setTextColor(WHITE);

  tft.setCursor(25, 210);
  tft.print('.');
  tft.setCursor(85, 215);
  tft.print('-');
  tft.setCursor(145, 215);
  tft.print('/');

  tft.fillRect(0, 40, 239, 130, WHITE);
  tft.fillRect(195, 171, 45, 25, GREEN);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.setCursor(210, 173);
  tft.print('-');
  
}

void MorseDecrypt()
{
  char result[50];
  if(strlen(sir) > 600)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  int k = 0;
  char *tok = strtok(sir, " ");
  while(tok)
  {
    String c = String(tok);
    result[k++] = Morse(c);
    tok = strtok(NULL, " ");
  }
  textbox();
  tft.setCursor(5, 45);
  for(int i = 0; i < k; i++)
    tft.print(result[i]);

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
  
}

void GetTasteMorseDecrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
    /**Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); **/
     if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
     {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
     }
     else if(p.y >= 580 && p.y <= 810)
     {
        if(p.x >= 180 && p.x <= 340)
          displayChar('.');
        else if(p.x >= 360 && p.x <= 545)
          displayChar('-');
        else if(p.x >= 550 && p.x <= 750)
          displayChar('/');
     }
     else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
     else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          sir[len] = 0;
          MorseDecrypt();
          break;
       }
     
    }
    if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        TastMorseDecrypt();
        textbox();
        afisare_sir();
     }
    delay(200);
  }
}

int litera(char c)
{
    return c >= 'A' && c <= 'Z';
}

void CesarEncrypt()
{
  
    for(int i = 0; sir[i] != 0; i++)
    {
        if(litera(sir[i]))
           sir[i] = (sir[i] + 3 - 'A') % 26 + 'A';
    }
    textbox();
    afisare_sir();

    while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void CesarDecrypt()
{
   
    for(int i = 0; sir[i] != 0; i++)
    {
        if(litera(sir[i]))
           sir[i] = (sir[i] - 3 - 'A') % 26 + 'A';
    }
    textbox();
    afisare_sir();

    while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void GetTasteCesarEncrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          CesarEncrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          CesarEncrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
     else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void GetTasteCesarDecrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          CesarDecrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          sir[len] = 0;
          CesarDecrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

int HexValue(char c)
{
  if(c >= '0' && c <= '9')
    return c - '0';
  switch(c)
  {
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
  }
  return -1;
}

void HexEncrypt()
{
  textbox();
  int limit = 7;
  if(strlen(sir) > 45)
  {
    tft.setTextSize(1);
    limit = 14;
  }   
  else
    tft.setTextSize(2);
  tft.setCursor(5, 45);
  int nr = 0;
  for(int i = 0; sir[i] != 0; i++)
  {
    nr++;
    if(nr == limit)
    {
      nr = 1;
      tft.print('\n');
    }
    tft.print(sir[i], HEX);
    tft.print(' ');
  }

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
    
}

void HexDecrypt()
{
  textbox();
  tft.setCursor(5, 45);
  if(strlen(sir) > 350)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  for(int i = 0; sir[i] != 0; i += 3)
  {
    tft.print((char) (HexValue(sir[i]) * 16 + HexValue(sir[i + 1])));
  }

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void GetTasteHexEncrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          HexEncrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          HexEncrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void GetTasteHexDecrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          HexDecrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
         error_message();
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
         error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        error_message();
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
       error_message();
        else if(p.x >= 495 && p.x <= 545)
        error_message();
        else if(p.x >= 550 && p.x <= 600)
       error_message();
        else if(p.x >= 605 && p.x <= 655)
        error_message();
        else if(p.x >= 660 && p.x <= 710)
       error_message();
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        error_message();
        else if(p.x >= 305 && p.x <= 355)
        error_message();
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        error_message();
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
       error_message();
        else if(p.x >= 580 && p.x <= 630)
        error_message();
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          sir[len] = 0;
          HexDecrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
         error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
        error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
        error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
         error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 630 && p.x <= 680)
         {
          error_message();
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
     else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void BinaryEncrypt()
{
  textbox();
  tft.setCursor(5, 45);
  int nr = 0;
  int limit = 3;
  if(strlen(sir) > 16)
  {
    tft.setTextSize(1);
    limit = 5;
  }
  for(int i = 0; sir[i] != 0; i++)
  {
    nr++;
    if(nr == limit)
    {
      nr = 1;
      tft.print('\n');
    }
    if(sir[i] == 0 || sir[i] == 1)
      tft.print("0000000");
    else if(sir[i] == 2 || sir[i] == 3)
      tft.print("000000");
    else if(sir[i] >= 4 && sir[i] <= 7)
      tft.print("00000");
    else if(sir[i] >= 8 && sir[i] <= 15)
      tft.print("0000");
    else if(sir[i] >= 16 && sir[i] <= 31)
      tft.print("000");
    else if(sir[i] >= 32 && sir[i] <= 63)
      tft.print("00");
    else if(sir[i] >= 64 && sir[i] <= 127)
      tft.print("0");
    tft.print(sir[i], BIN);
    tft.print(' ');
  }

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
    
}

void BinaryDecrypt()
{
  textbox();
  tft.setCursor(5, 45);
  if(strlen(sir) > 1500)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  
  for(int i = 0; sir[i] != 0; i += 9)
  {
    tft.print((char)(128 * (sir[i] - '0') + 64 * (sir[i + 1] - '0') + 32 * (sir[i + 2] - '0') + 16 * (sir[i + 3] - '0') + 8 * (sir[i + 4] - '0') + 4 * (sir[i + 5] - '0') + 2 * (sir[i + 6] - '0') + (sir[i +7] - '0')));
  }
  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void GetTasteBinaryEncrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          sir[len] = 0;
          BinaryEncrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          sir[len] = 0;
          BinaryEncrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
     else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void GetTasteBinaryDecrypt()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          BinaryDecrypt();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
         error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
         error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        error_message();
        else if(p.x >= 275 && p.x <= 325)
        error_message();
        else if(p.x >= 330 && p.x <= 380)
        error_message();
        else if(p.x >= 385 && p.x <= 435)
        error_message();
        else if(p.x >= 440 && p.x <= 490)
       error_message();
        else if(p.x >= 495 && p.x <= 545)
        error_message();
        else if(p.x >= 550 && p.x <= 600)
       error_message();
        else if(p.x >= 605 && p.x <= 655)
        error_message();
        else if(p.x >= 660 && p.x <= 710)
       error_message();
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        error_message();
        else if(p.x >= 305 && p.x <= 355)
        error_message();
        else if(p.x >= 360 && p.x <= 410)
        error_message();
        else if(p.x >= 415 && p.x <= 465)
        error_message();
        else if(p.x >= 470 && p.x <= 520)
        error_message();
        else if(p.x >= 525 && p.x <= 575)
       error_message();
        else if(p.x >= 580 && p.x <= 630)
        error_message();
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
        sir[len] = 0;
          BinaryDecrypt();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
         error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
         error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
        error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 245 && p.x <= 295)
        error_message();
         else if(p.x >= 300 && p.x <= 350)
         error_message();
         else if(p.x >= 355 && p.x <= 405)
         error_message();
         else if(p.x >= 410 && p.x <= 460)
         error_message();
         else if(p.x >= 465 && p.x <= 515)
         error_message();
         else if(p.x >= 520 && p.x <= 570)
         error_message();
         else if(p.x >= 575 && p.x <= 625)
         error_message();
         else if(p.x >= 630 && p.x <= 680)
         error_message();
         else if(p.x >= 685 && p.x <= 735)
         error_message();
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          error_message();
         else if(p.x >= 630 && p.x <= 680)
         {
          error_message();
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void VigenereEncrypt()
{
  textbox();
  tft.setCursor(5, 45);
  int k = 0;
  for(int i = 0; sir[i] != 0; i++)
  {
    if(cheie[k] == 0)
      k = 0;
    if(litera(sir[i]))
    {
      sir[i] = (sir[i] + (cheie[k] - 'A') - 'A') % 26 + 'A';
      k++;
    }
    
  }
  afisare_sir();

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void Atbash()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  textbox();
  tft.setCursor(5, 45);

  for(int i = 0; sir[i] != 0; i++)
    if(litera(sir[i]))
      sir[i] = 26 - (sir[i] - 'A' + 1) + 'A';
  afisare_sir();

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void VigenereDecrypt()
{
  
  textbox();
  tft.setCursor(5, 45);
  int k = 0;
  for(int i = 0; sir[i] != 0; i++)
  {
    if(cheie[k] == 0)
      k = 0;
    if(litera(sir[i]))
    {
      int p = sir[i] - 'A';
      int n = cheie[k] - 'A';
      if(p - n < 0)
      {
        char c = sir[i];
        while(n)
        {
          Serial.print((char) c);
          Serial.print(' ');
          Serial.print(n);
          Serial.print('\n');
          
          c--;
          n--;
          if(c == 64)
            c = 90;
        }
        sir[i] = c;
      }
      else
        sir[i] = sir[i] - n;
      k++;
    }
    
  }
  afisare_sir();

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    }
    
  }
}

void GetTasteAtbash()
{
  resetString();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          Serial.print("OK");
          sir[len] = 0;
          Atbash();
          break;
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          Serial.print("OK");
          sir[len] = 0;
          Atbash();
          break;
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void enter_key()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, RED);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Introduceti cheia");

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(107, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("OK");

  while(1)
  {
    TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z); 
      if(p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        textbox();
        afisare_sir();
        break;
      }
    }
  
  }
}

void enter_text()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, RED);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Introduceti textul");

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(107, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("OK");

  while(1)
  {
    TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z); 
      if(p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        textbox();
        afisare_sir();
        break;
      }
    }
  
  }
}


void GetTasteVigenereEncrypt()
{
  
  resetString();
  isVig = true;
  enter_key();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          if(isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            cheie[len_key] = 0;
            for(int i = 0; i < len; i++)
              sir[i] = 0;
            len = 0;
            isKey = false;
            enter_text();
            textbox();
          }
          else
          {
            sir[len] = 0;
            VigenereEncrypt();
            break;
          }
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          if(isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            for(int i = 0; i < len; i++)
              sir[i] = 0;
            len = 0;
            isKey = false;
            enter_text();
            textbox();
          }
          else
          {
            sir[len] = 0;
            VigenereEncrypt();
            break;
          }
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
     else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}

void GetTasteVigenereDecrypt()
{
  resetString();
  isVig = true;
  enter_key();
  while(1)
  {
    
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
   Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z); 
    
     if(mode == 1)
     {
          if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
          {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
          }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          if(isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            cheie[len_key] = 0;
            for(int i = 0; i < len; i++)
              sir[i] = 0;
            len = 0;
            isKey = false;
            enter_text();
            textbox();
          }
          else
          {
            sir[len] = 0;
            VigenereDecrypt();
            break;
          }
       }
        
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 2;
        
        tast_cif_simb();
        
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('Q');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('W');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('E');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('R');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('T');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('Y');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('U');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('I');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('O');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('P');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
        if(p.x >= 220 && p.x <= 270)
        displayChar('A');
        else if(p.x >= 275 && p.x <= 325)
        displayChar('S');
        else if(p.x >= 330 && p.x <= 380)
        displayChar('D');
        else if(p.x >= 385 && p.x <= 435)
        displayChar('F');
        else if(p.x >= 440 && p.x <= 490)
        displayChar('G');
        else if(p.x >= 495 && p.x <= 545)
        displayChar('H');
        else if(p.x >= 550 && p.x <= 600)
        displayChar('J');
        else if(p.x >= 605 && p.x <= 655)
        displayChar('K');
        else if(p.x >= 660 && p.x <= 710)
        displayChar('L');
       }
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 250 && p.x <= 300)
        displayChar('Z');
        else if(p.x >= 305 && p.x <= 355)
        displayChar('X');
        else if(p.x >= 360 && p.x <= 410)
        displayChar('C');
        else if(p.x >= 415 && p.x <= 465)
        displayChar('V');
        else if(p.x >= 470 && p.x <= 520)
        displayChar('B');
        else if(p.x >= 525 && p.x <= 575)
        displayChar('N');
        else if(p.x >= 580 && p.x <= 630)
        displayChar('M');
       }
       
     }
     else
     {
        if(p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
            textbox();
            len--;
            sir[len] = 0;
            afisare_sir();
        }
       else if(p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
       {
          if(isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            for(int i = 0; i < len; i++)
              sir[i] = 0;
            len = 0;
            isKey = false;
            enter_text();
            textbox();
          }
          else
          {
            VigenereDecrypt();
            break;
          }
       }
       else if(p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
       {
        mode = 1;
        tast_litere();
       }
       else if(p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
       else if(p.y >= 600 && p.y <= 660)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('1');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('2');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('3');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('4');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('5');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('6');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('7');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('8');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('9');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('0');
         
       }
       else if(p.y >= 670 && p.y <= 730)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar('@');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('.');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('$');
         else if(p.x >= 355 && p.x <= 405)
         displayChar('_');
         else if(p.x >= 410 && p.x <= 460)
         displayChar('&');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('-');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('+');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('(');
         else if(p.x >= 630 && p.x <= 680)
         displayChar(')');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('/');
        
       }  
       else if(p.y >= 740 && p.y <= 800)
       {
        if(p.x >= 190 && p.x <= 240)
          displayChar('<');
         else if(p.x >= 245 && p.x <= 295)
         displayChar('*');
         else if(p.x >= 300 && p.x <= 350)
         displayChar('\'');
         else if(p.x >= 355 && p.x <= 405)
         displayChar(':');
         else if(p.x >= 410 && p.x <= 460)
         displayChar(';');
         else if(p.x >= 465 && p.x <= 515)
         displayChar('!');
         else if(p.x >= 520 && p.x <= 570)
         displayChar('?');
         else if(p.x >= 575 && p.x <= 625)
         displayChar('=');
         else if(p.x >= 630 && p.x <= 680)
         displayChar('%');
         else if(p.x >= 685 && p.x <= 735)
         displayChar('>');
       }
       else if(p.y >= 810 && p.y <= 870)
       {
         if(p.x >= 190 && p.x <= 240)
          displayChar(',');
         else if(p.x >= 630 && p.x <= 680)
         {
          displayChar('\"');
         }
       }
       
     }
     if(p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
         {
          CypherMenuWork();
          break;
         }
    else if(p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
     {
        smaller = true;
        if(mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir();
     }
    }
    delay(200);
  }
}



void CaseMorseEncrypt()
{
   pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
   tast_litere();
   textbox();
   GetTasteMorseEncrypt();
}

void CaseMorseDecrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  TastMorseDecrypt();
  textbox();
  GetTasteMorseDecrypt();
}

void CaseCesarEncrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteCesarEncrypt();
}

void CaseCesarDecrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteCesarDecrypt();
}

void CaseHexEncrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteHexEncrypt();
}

void CaseHexDecrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteHexDecrypt();
}

void CaseBinaryEncrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteBinaryEncrypt();
}

void CaseBinaryDecrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteBinaryDecrypt();
}

void CaseVigenereEncrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteVigenereEncrypt();
}

void CaseVigenereDecrypt()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteVigenereDecrypt();
}

void CaseAtbash()
{
  pinMode(A1, OUTPUT);
   pinMode(A2, OUTPUT);
   tft.fillScreen(BLACK);
  tast_litere();
  textbox();
  GetTasteAtbash();
}

void CryptDecryptMenuMorse()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 0, 239, 160, CYAN);
  tft.fillRect(0, 160, 239, 160, MAGENTA);
  tft.setCursor(60, 60);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.print("Encrypt");
  tft.setCursor(60, 220);
  tft.print("Decrypt");

  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(173, 296);
  tft.print("BACK");

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseMorseEncrypt();
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        CaseMorseDecrypt();
      }
    }
  }
}

void CryptDecryptMenuCesar()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 0, 239, 160, CYAN);
  tft.fillRect(0, 160, 239, 160, MAGENTA);
  tft.setCursor(60, 60);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.print("Encrypt");
  tft.setCursor(60, 220);
  tft.print("Decrypt");

  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(173, 296);
  tft.print("BACK");

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseCesarEncrypt();
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        CaseCesarDecrypt();
      }
    }
  }
}

void CryptDecryptMenuHex()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 0, 239, 160, CYAN);
  tft.fillRect(0, 160, 239, 160, MAGENTA);
  tft.setCursor(60, 60);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.print("Encrypt");
  tft.setCursor(60, 220);
  tft.print("Decrypt");

  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(173, 296);
  tft.print("BACK");

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseHexEncrypt();
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        CaseHexDecrypt();
      }
    }
  }
}

void CryptDecryptMenuBinary()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 0, 239, 160, CYAN);
  tft.fillRect(0, 160, 239, 160, MAGENTA);
  tft.setCursor(60, 60);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.print("Encrypt");
  tft.setCursor(60, 220);
  tft.print("Decrypt");

  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(173, 296);
  tft.print("BACK");

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseBinaryEncrypt();
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        CaseBinaryDecrypt();
      }
    }
  }
}

void CryptDecryptMenuVigenere()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  tft.fillRect(0, 0, 239, 160, CYAN);
  tft.fillRect(0, 160, 239, 160, MAGENTA);
  tft.setCursor(60, 60);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.print("Encrypt");
  tft.setCursor(60, 220);
  tft.print("Decrypt");

  tft.fillRect(170, 295, 60, 20, GREEN);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(173, 296);
  tft.print("BACK");

  while(1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) 
    {
      if(p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseVigenereEncrypt();
      }
      else if(p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        CaseVigenereDecrypt();
      }
    }
  }
}

void Work()
{
  CypherMenuWork();
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
  tft.setRotation(4);
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
        break;
      }
      else if(p.x >= 390 && p.x <= 700 && p.y >= 430 && p.y <= 650)
      {
        Work();
        break;
      }
      else if(p.x >= 390 && p.x <= 700 && p.y >= 690 && p.y <= 920)
      {
        Wiki();
        break;
      }
      
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
  tft.begin(0xE300);
  tft.fillScreen(BLACK);
  tft.setRotation(4);
  Serial.begin(9600);
  Intro();
}

void loop() {
   

}