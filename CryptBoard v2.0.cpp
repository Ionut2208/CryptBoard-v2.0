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

String text;
bool first = true;
int score, XP_crnt, slot;
char MorseChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?;:/-()_@!&=+$ ";
char sir[300], cheie[300];
int mode = 1, len, len_key;
bool isKey = true, smaller = false, isVig = false;

void(* resetFunc) (void) = 0;

void resetare()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, RED);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Este necesara      repornirea pentru  salvarea/stergerea profilului");

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(107, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("OK");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        pinMode(A1, OUTPUT);
        pinMode(A2, OUTPUT);
        tft.fillRect(0, 40, 239, 130, RED);
        tft.setCursor(5, 45);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("Repornire in ");
        for (int i = 5; i >= 1; i--)
        {
          tft.setCursor(170, 45);
          tft.print(i);
          delay(1000);
          tft.fillRect(165, 40, 20, 20, RED);
          
        }
        resetFunc();
        break;
      }
    }

  }

}

struct profil
{
  char username[10], parola[15];
  int HighScoreMorse = 0, HighScoreCesar = 0, HighScoreHex = 0, HighScoreBinary = 0, HighScoreVigenere = 0, HighScoreAtbash = 0;
  int Level = 1, XPLevel = 0;
  int username_len = 0, password_len = 0;

} user[4]; ///3 slot-uri + 1 profil pentru verificare parola

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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 660 && p.x <= 910 && p.y >= 720 && p.y <= 800)
      {
        MorseTabelCifre();
        break;
      }
      else if (p.x >= 660 && p.x <= 910 && p.y >= 835 && p.y <= 930)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 390 && p.x <= 915 && p.y >= 760 && p.y <= 840)
      {
        MorseTabelSimb();
        break;
      }
      else if (p.x >= 585 && p.x <= 910 && p.y >= 860 && p.y <= 930)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 560 && p.x <= 875 && p.y >= 790 && p.y <= 890)
      {
        MorseTabelCifre();
        break;
      }
      else if (p.x >= 150 && p.x <= 475 && p.y >= 785 && p.y <= 885)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      /** Serial.print(p.x);
        Serial.print(' ');
        Serial.print(p.y);
        Serial.print('\n'); **/
      if (p.x >= 580 && p.x <= 870 && p.y >= 750 && p.y <= 850)
      {
        MorseTabelLitere();
        break;
      }
      else if (p.x >= 150 && p.x <= 475 && p.y >= 750 && p.y <= 850)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      /** Serial.print(p.x);
        Serial.print(' ');
        Serial.print(p.y);
        Serial.print('\n'); **/
      if (p.x >= 580 && p.x <= 870 && p.y >= 750 && p.y <= 850)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 460 && p.y >= 845 && p.y <= 945)
      {
        HexWiki();
        break;
      }
      else if (p.x >= 530 && p.x <= 865 && p.y >= 845 && p.y <= 945)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 465 && p.x <= 890 && p.y >= 750 && p.y <= 850)
      {
        HexExample();
        break;
      }
      else if (p.x >= 145 && p.x <= 430 && p.y >= 750 && p.y <= 850)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 460 && p.y >= 845 && p.y <= 945)
      {
        BinaryWiki();
        break;
      }
      else if (p.x >= 530 && p.x <= 865 && p.y >= 845 && p.y <= 945)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 465 && p.x <= 890 && p.y >= 750 && p.y <= 850)
      {
        BinaryExample();
        break;
      }
      else if (p.x >= 145 && p.x <= 430 && p.y >= 750 && p.y <= 850)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 460 && p.y >= 845 && p.y <= 945)
      {
        VigenereWiki();
        break;
      }
      else if (p.x >= 530 && p.x <= 865 && p.y >= 845 && p.y <= 945)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 465 && p.x <= 890 && p.y >= 840 && p.y <= 920)
      {
        VigenereExample();
        break;
      }
      else if (p.x >= 145 && p.x <= 430 && p.y >= 840 && p.y <= 920)
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
  while (!ok)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold) {
      /** Serial.print(p.x);
        Serial.print(' ');
        Serial.print(p.y);
        Serial.print('\n'); **/
      if (p.x >= 580 && p.x <= 870 && p.y >= 750 && p.y <= 850)
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

  while (1)
  {

    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      printCoord();
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 175 && p.y <= 380)
      {
        MorseWiki();
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 175 && p.y <= 380)
      {
        CesarWiki();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 420 && p.y <= 615)
      {
        HexWiki();
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 420 && p.y <= 615)
      {
        BinaryWiki();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 670 && p.y <= 865)
      {
        VigenereWiki();
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 670 && p.y <= 865)
      {
        AtbashWiki();
        break;
      }


    }
  }
}


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

  while (1)
  {

    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {

      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 175 && p.y <= 380)
      {
        CryptDecryptMenuMorse();
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 175 && p.y <= 380)
      {
        CryptDecryptMenuCesar();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 420 && p.y <= 615)
      {
        CryptDecryptMenuHex();
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 420 && p.y <= 615)
      {
        CryptDecryptMenuBinary();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 670 && p.y <= 865)
      {
        CryptDecryptMenuVigenere();
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 670 && p.y <= 865)
      {
        CaseAtbash();
        break;
      }


    }
  }
  return;
}

void CypherMenuPlay(int slot)
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

  first = true;
  XP_crnt = 0;
  score = 0;

  while (1)
  {

    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {

      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        MainMenu();
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 175 && p.y <= 380)
      {
        CryptDecryptMenuMorsePlay(slot);
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 175 && p.y <= 380)
      {
        CryptDecryptMenuCesarPlay(slot);
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 420 && p.y <= 615)
      {
        CryptDecryptMenuHexPlay(slot);
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 420 && p.y <= 615)
      {
        CryptDecryptMenuBinaryPlay(slot);
        break;
      }
      else if (p.x >= 230 && p.x <= 485 && p.y >= 670 && p.y <= 865)
      {
        CryptDecryptMenuVigenerePlay(slot);
        break;
      }
      else if (p.x >= 560 && p.x <= 835 && p.y >= 670 && p.y <= 865)
      {
        PlayAtbash(slot);
        break;
      }


    }
  }
}

void CryptDecryptMenuMorsePlay(int slot)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        PlayMorseEncrypt(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        PlayMorseDecrypt(slot);
        break;
      }
    }
  }
}

String morse_rep[60];

void get_morse_rep()
{
  int l = strlen(MorseChars);
  for (int i = 0; i < l; i++)
    morse_rep[i] = morse(MorseChars[i]);
}

void generateEasyMorseDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int poz = random(0, 26);
    s.concat(morse_rep[poz]);
    s.concat(" ");
  }
  text = s;
}

void generateMediumMorseDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int poz = random(0, 36);
    s.concat(morse_rep[poz]);
    s.concat(" ");
  }
  text = s;
}

void generateHardMorseDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(0, 53);
    s.concat(morse_rep[poz]);
    s.concat(" ");
  }
  text = s;
}

void PlayMorseDecrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  get_morse_rep();
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyMorseDecrypt();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyMorseDecrypt();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumMorseDecrypt();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardMorseDecrypt();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayMorseDecrypt(slot);
}

void GetTastePlayMorseDecrypt(int slot)
{
  resetString();
  String corect = MorseDecrypt(text);
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckMorseDecrypt() == corect.length())
          {
            TextVerificareMorseDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareMorseDecrypt(false, corect.length() - CheckMorseDecrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckMorseDecrypt() == corect.length())
          {
            TextVerificareMorseDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareMorseDecrypt(false, corect.length() - CheckMorseDecrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}

void TextVerificareMorseDecrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = MorseDecrypt(text).length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.print('\n');
    tft.print(MorseDecrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverMorse(slot);
        }
        else
        {
          PlayMorseDecrypt(slot);
          break;
        }
      }
    }

  }

}

String MorseDecrypt(String s)
{
  char text_char[text.length() + 10];
  text.toCharArray(text_char, text.length() + 10);
  String answer;
  for (int i = 0; i < answer.length(); i++)
    answer[i] = '\0';
  char *p = strtok(text_char, " ");
  while (p)
  {
    String c = String(p);
    answer.concat(Morse(c));
    p = strtok(NULL, " ");
  }
  return answer;
}

int CheckMorseDecrypt()
{
  int nr = 0;
  String correct_answer = MorseDecrypt(text);
  int l = correct_answer.length();
  for (int i = 0; i < l; i++)
    if (correct_answer[i] == sir[i])
      nr++;
  return nr;
}

void CryptDecryptMenuCesarPlay(int slot)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        PlayCesarEncrypt(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        PlayCesarDecrypt(slot);
        break;
      }
    }
  }
}

void generateEasyCesar()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int poz = random(0, 26);
    s.concat((char)('A' + poz));
  }
  text = s;
}

void generateMediumCesar()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int poz = random(0, 26);
    s.concat((char)('A' + poz));
  }
  text = s;
}

void generateHardCesar()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(0, 26);
    s.concat((char)('A' + poz));
  }
  text = s;
}

void PlayCesarEncrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyCesar();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyCesar();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumCesar();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardCesar();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayCesarEncrypt(slot);
}

void GetTastePlayCesarEncrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckCesarEncrypt() == text.length())
          {
            TextVerificareCesarEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareCesarEncrypt(false, text.length() - CheckCesarEncrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckCesarEncrypt() == text.length())
          {
            TextVerificareCesarEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareCesarEncrypt(false, text.length() - CheckCesarEncrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}

String CesarEncrypt(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  int l = s.length();
  for (int i = 0; i < l; i++)
    res.concat((char)((s[i] + 3 - 'A') % 26 + 'A'));
  return res;
}

int CheckCesarEncrypt()
{
  int nr = 0;
  String corect = CesarEncrypt(text);
  for (int i = 0; i < corect.length(); i++)
    if (corect[i] == sir[i])
      nr++;
  return nr;
}

void TextVerificareCesarEncrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.print('\n');
    tft.print(CesarEncrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverCesar(slot);
        }
        else
        {
          PlayCesarEncrypt(slot);
          break;
        }
      }
    }

  }
}

void GameOverCesar(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(RED);
  tft.setCursor(70, 0);
  tft.print("GAME      OVER");
  tft.setTextSize(2);
  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);
  tft.print("Numarul maxim de   caractere gresite  acceptate a fost   depasit!");
  tft.print("\n\n\nXP: +");
  tft.print(XP_crnt);
  tft.print("\nScor: ");
  tft.print(score);

  tft.fillRect(75, 250, 90, 35, RED);
  tft.setCursor(100, 257);
  tft.setTextSize(3);
  tft.print("OK");



  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);
  if (score > var.HighScoreCesar)
  {
    var.HighScoreCesar = score;
    EEPROM.put(loc, var);
    tft.setCursor(10, 220);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("(High Score nou)");
  }
  EEPROM.get(loc, var);
  int lvl = var.Level, xp_lvl = var.XPLevel;
  if (XP_crnt < 50 + (lvl - 1) * 5)
  {
    var.XPLevel += XP_crnt;
    if (var.XPLevel >= 50 + (lvl - 1) * 5)
    {
      var.XPLevel -= 50 + (lvl - 1) * 5;
      var.Level++;
      tft.setCursor(120, 183);
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print("Level up!");
    }
    EEPROM.put(loc, var);
  }
  else
  {
    while (XP_crnt >= 50 + (lvl - 1) * 5)
    {
      XP_crnt -= 50 + (lvl - 1) * 5;
      lvl++;
    } ///cat timp poate creste levelul
    var.XPLevel += XP_crnt;
    var.Level = lvl;
    tft.setCursor(120, 183);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("Level up!");
    EEPROM.put(loc, var);
  }
  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 385 && p.x <= 670 && p.y >= 760 && p.x <= 855)
      {
        EcranProfil(slot);
        break;
      }
    }

  }
}


void PlayCesarDecrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyCesar();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyCesar();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumCesar();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardCesar();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayCesarDecrypt(slot);
}

void GetTastePlayCesarDecrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckCesarDecrypt() == text.length())
          {
            TextVerificareCesarDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareCesarDecrypt(false, text.length() - CheckCesarDecrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckCesarDecrypt() == text.length())
          {
            TextVerificareCesarDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareCesarDecrypt(false, text.length() - CheckCesarDecrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}

String CesarDecrypt(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  int l = s.length();
  for (int i = 0; i < l; i++)
  {
    if (s[i] >= 'D' && s[i] <= 'Z')
      res.concat((char)((s[i] - 3 - 'A') % 26 + 'A'));
    else
    {
      switch (s[i])
      {
        case 'C': res.concat('Z');
          break;
        case 'B': res.concat('Y');
          break;
        case 'A': res.concat('X');
      }
    }
  }

  return res;
}

int CheckCesarDecrypt()
{
  int nr = 0;
  String corect = CesarDecrypt(text);
  for (int i = 0; i < corect.length(); i++)
    if (corect[i] == sir[i])
      nr++;
  return nr;
}

void TextVerificareCesarDecrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.print('\n');
    tft.print(CesarDecrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverCesar(slot);
        }
        else
        {
          PlayCesarDecrypt(slot);
          break;
        }
      }
    }

  }
}

void CryptDecryptMenuHexPlay(int slot)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        PlayHexEncrypt(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        PlayHexDecrypt(slot);
        break;
      }
    }
  }
}

void generateEasyHexEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int lit_mari = random(65, 91);
    int lit_mici = random(97, 123);
    int alegere = random(1, 3);
    if (alegere == 1)
      s.concat((char) lit_mari);
    else
      s.concat((char) lit_mici);
  }
  text = s;
}

void generateMediumHexEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int lit_mari = random(65, 91);
    int lit_mici = random(97, 123);
    int cifre = random(48, 58);
    int alegere = random(1, 4);
    if (alegere == 1)
      s.concat((char) lit_mari);
    else if (alegere == 2)
      s.concat((char) lit_mici);
    else
      s.concat((char) cifre);
  }
  text = s;
}

void generateHardHexEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(32, 127);
    s.concat((char) poz);
  }
  text = s;
}

void PlayHexEncrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyHexEncrypt();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyHexEncrypt();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumHexEncrypt();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardHexEncrypt();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayHexEncrypt(slot);
}

void GetTastePlayHexEncrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckHexEncrypt() == text.length())
          {
            TextVerificareHexEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareHexEncrypt(false, text.length() - CheckHexEncrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckHexEncrypt() == text.length())
          {
            TextVerificareHexEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareHexEncrypt(false, text.length() - CheckHexEncrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}

String hex_rep(int x)
{
  char rep[3];
  int k = 1;
  for (int i = 0; i < 3; i++)
    rep[i] = '\0';
  while (x)
  {
    int c = x % 16;
    if (c >= 0 && c <= 9)
      rep[k--] = (char) (c + '0');
    else
    {
      switch (c)
      {
        case 10: rep[k--] = 'A';
          break;
        case 11: rep[k--] = 'B';
          break;
        case 12: rep[k--] = 'C';
          break;
        case 13: rep[k--] = 'D';
          break;
        case 14: rep[k--] = 'E';
          break;
        case 15: rep[k--] = 'F';
      }
    }
    x /= 16;
  }
  return String(rep);
}

String HexEncrypt(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  for (int i = 0; i < s.length(); i++)
  {
    res.concat(hex_rep(s[i]));
    res.concat(" ");
  }

  Serial.print(res);
  return res;
}

int CheckHexEncrypt()
{
  String correct_answer = HexEncrypt(text);
  char correct_answer_char[correct_answer.length() + 10];
  correct_answer.toCharArray(correct_answer_char, correct_answer.length() + 10);
  char correct_char[10][10];
  char answer_char[10][10];
  int k = 0, l = 0;
  Serial.print('\n');
  Serial.print(correct_answer_char);
  Serial.print('\n');
  char *p = strtok(correct_answer_char, " ");
  while (p)
  {
    strcpy(correct_char[k++], p);
    p = strtok(NULL, " ");
  }
  p = strtok(sir, " ");
  while (p)
  {
    strcpy(answer_char[l++], p);
    p = strtok(NULL, " ");
  }
  int nr = 0;
  for (int i = 0; i < k; i++)
  {
    if (strcmp(correct_char[i], answer_char[i]) == 0)
      nr++;

  }

  return nr;
}

void TextVerificareHexEncrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.print('\n');
    tft.print(HexEncrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverHex(slot);
        }
        else
        {
          PlayHexEncrypt(slot);
          break;
        }
      }
    }

  }
}

void GameOverHex(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(RED);
  tft.setCursor(70, 0);
  tft.print("GAME      OVER");
  tft.setTextSize(2);
  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);
  tft.print("Numarul maxim de   caractere gresite  acceptate a fost   depasit!");
  tft.print("\n\n\nXP: +");
  tft.print(XP_crnt);
  tft.print("\nScor: ");
  tft.print(score);

  tft.fillRect(75, 250, 90, 35, RED);
  tft.setCursor(100, 257);
  tft.setTextSize(3);
  tft.print("OK");



  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);
  if (score > var.HighScoreHex)
  {
    var.HighScoreHex = score;
    EEPROM.put(loc, var);
    tft.setCursor(10, 220);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("(High Score nou)");
  }
  EEPROM.get(loc, var);
  int lvl = var.Level, xp_lvl = var.XPLevel;
  if (XP_crnt < 50 + (lvl - 1) * 5)
  {
    var.XPLevel += XP_crnt;
    if (var.XPLevel >= 50 + (lvl - 1) * 5)
    {
      var.XPLevel -= 50 + (lvl - 1) * 5;
      var.Level++;
      tft.setCursor(120, 183);
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print("Level up!");
    }
    EEPROM.put(loc, var);
  }
  else
  {
    while (XP_crnt >= 50 + (lvl - 1) * 5)
    {
      XP_crnt -= 50 + (lvl - 1) * 5;
      lvl++;
    } ///cat timp poate creste levelul
    var.XPLevel += XP_crnt;
    var.Level = lvl;
    tft.setCursor(120, 183);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("Level up!");
    EEPROM.put(loc, var);
  }
  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 385 && p.x <= 670 && p.y >= 760 && p.x <= 855)
      {
        EcranProfil(slot);
        break;
      }
    }

  }
}

void generateEasyHexDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int lit_mari = random(65, 91);
    s.concat(hex_rep(lit_mari));
    s.concat(" ");
  }
  text = s;
}

void generateMediumHexDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int lit_mari = random(65, 91);
    int cifre = random(48, 58);
    int alegere = random(1, 3);
    if (alegere == 1)
    {
      s.concat(hex_rep(lit_mari));
      s.concat(" ");
    }
    else
    {
      s.concat(hex_rep(cifre));
      s.concat(" ");
    }
  }
  text = s;
}

char simb[] = "@.$_&-+()/<*':;!?=%>,\"";

void generateHardHexDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int lit_mari = random(65, 91);
    int cifre = random(48, 58);
    int simbol = random(0, 22);
    int alegere = random(1, 4);
    if (alegere == 1)
    {
      s.concat(hex_rep(lit_mari));
      s.concat(" ");
    }
    else if (alegere == 2)
    {
      s.concat(hex_rep(cifre));
      s.concat(" ");
    }
    else
    {
      s.concat(hex_rep(simb[simbol]));
      s.concat(" ");
    }
    if (i == 5)
      s.concat(" ");
  }
  text = s;
}

void PlayHexDecrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyHexDecrypt();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyHexDecrypt();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumHexDecrypt();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardHexDecrypt();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayHexDecrypt(slot);
}

void GetTastePlayHexDecrypt(int slot)
{
  String corect = HexDecrypt(text);
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckHexDecrypt() == corect.length())
          {
            TextVerificareHexDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareHexDecrypt(false, corect.length() - CheckHexDecrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckHexDecrypt() == corect.length())
          {
            TextVerificareHexDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareHexDecrypt(false, corect.length() - CheckHexDecrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}

int hex_val(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  switch (c)
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

String HexDecrypt(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  char text_char[35];
  text.toCharArray(text_char, 35);
  char *p = strtok(text_char, " ");
  while (p)
  {
    int val = hex_val(p[0]) * 16 + hex_val(p[1]);
    res.concat((char) val);
    p = strtok(NULL, " ");
  }
  return res;
}

int CheckHexDecrypt()
{
  int nr = 0;
  String corect = HexDecrypt(text);
  for (int i = 0; i < corect.length(); i++)
    if (sir[i] == corect[i])
      nr++;
  return nr;
}

void TextVerificareHexDecrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = HexDecrypt(text).length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.print('\n');
    tft.print(HexDecrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverHex(slot);
        }
        else
        {
          PlayHexDecrypt(slot);
          break;
        }
      }
    }

  }
}


void CryptDecryptMenuBinaryPlay(int slot)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        PlayBinaryEncrypt(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        PlayBinaryDecrypt(slot);
        break;
      }
    }
  }
}

void generateEasyBinaryEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int lit_mari = random(65, 91);
    int lit_mici = random(97, 123);
    int alegere = random(1, 3);
    if (alegere == 1)
      s.concat((char) lit_mari);
    else
      s.concat((char) lit_mici);
  }
  text = s;
}

void generateMediumBinaryEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int lit_mari = random(65, 91);
    int lit_mici = random(97, 123);
    int cifre = random(48, 58);
    int alegere = random(1, 4);
    if (alegere == 1)
      s.concat((char) lit_mari);
    else if (alegere == 2)
      s.concat((char) lit_mici);
    else
      s.concat((char) cifre);
  }
  text = s;
}

void generateHardBinaryEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(32, 127);
    s.concat((char) poz);
  }
  text = s;
}

void PlayBinaryEncrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyBinaryEncrypt();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyBinaryEncrypt();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumBinaryEncrypt();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardBinaryEncrypt();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayBinaryEncrypt(slot);
}

void GetTastePlayBinaryEncrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckBinaryEncrypt() == text.length())
          {
            TextVerificareBinaryEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareBinaryEncrypt(false, text.length() - CheckBinaryEncrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckBinaryEncrypt() == text.length())
          {
            TextVerificareBinaryEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareBinaryEncrypt(false, text.length() - CheckBinaryEncrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}



String BinaryEncrypt(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  for (int i = 0; i < s.length(); i++)
  {
    String rep = String(s[i], BIN);
    if (s[i] >= 32 && s[i] < 64)
      res.concat("00");
    else if (s[i] >= 64 && s[i] < 128)
      res.concat("0");
    res.concat(rep);
    res.concat(" ");
  }
  return res;
}

int CheckBinaryEncrypt()
{
  String correct_answer = BinaryEncrypt(text);
  char correct_answer_char[correct_answer.length() + 10];
  correct_answer.toCharArray(correct_answer_char, correct_answer.length() + 10);
  char correct_char[10][10];
  char answer_char[10][10];
  int k = 0, l = 0;
  Serial.print('\n');
  Serial.print(correct_answer_char);
  Serial.print('\n');
  char *p = strtok(correct_answer_char, " ");
  while (p)
  {
    strcpy(correct_char[k++], p);
    p = strtok(NULL, " ");
  }
  p = strtok(sir, " ");
  while (p)
  {
    strcpy(answer_char[l++], p);
    p = strtok(NULL, " ");
  }
  int nr = 0;
  for (int i = 0; i < k; i++)
  {
    if (strcmp(correct_char[i], answer_char[i]) == 0)
      nr++;

  }

  return nr;
}

void TextVerificareBinaryEncrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    tft.print('\n');
    tft.print(BinaryEncrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverBinary(slot);
        }
        else
        {
          PlayBinaryEncrypt(slot);
          break;
        }
      }
    }

  }
}

void GameOverBinary(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(RED);
  tft.setCursor(70, 0);
  tft.print("GAME      OVER");
  tft.setTextSize(2);
  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);
  tft.print("Numarul maxim de   caractere gresite  acceptate a fost   depasit!");
  tft.print("\n\n\nXP: +");
  tft.print(XP_crnt);
  tft.print("\nScor: ");
  tft.print(score);

  tft.fillRect(75, 250, 90, 35, RED);
  tft.setCursor(100, 257);
  tft.setTextSize(3);
  tft.print("OK");



  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);
  if (score > var.HighScoreBinary)
  {
    var.HighScoreBinary = score;
    EEPROM.put(loc, var);
    tft.setCursor(10, 220);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("(High Score nou)");
  }
  EEPROM.get(loc, var);
  int lvl = var.Level, xp_lvl = var.XPLevel;
  if (XP_crnt < 50 + (lvl - 1) * 5)
  {
    var.XPLevel += XP_crnt;
    if (var.XPLevel >= 50 + (lvl - 1) * 5)
    {
      var.XPLevel -= 50 + (lvl - 1) * 5;
      var.Level++;
      tft.setCursor(120, 183);
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print("Level up!");
    }
    EEPROM.put(loc, var);
  }
  else
  {
    while (XP_crnt >= 50 + (lvl - 1) * 5)
    {
      XP_crnt -= 50 + (lvl - 1) * 5;
      lvl++;
    } ///cat timp poate creste levelul
    var.XPLevel += XP_crnt;
    var.Level = lvl;
    tft.setCursor(120, 183);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("Level up!");
    EEPROM.put(loc, var);
  }
  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 385 && p.x <= 670 && p.y >= 760 && p.x <= 855)
      {
        EcranProfil(slot);
        break;
      }
    }

  }
}

void generateEasyBinaryDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int lit_mari = random(65, 91);
    s.concat("0");
    s.concat(String(lit_mari, BIN));
    s.concat(" ");
  }
  text = s;
}

void generateMediumBinaryDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int lit_mari = random(65, 91);
    int cifre = random(48, 58);
    int alegere = random(1, 3);
    if (alegere == 1)
    {
      s.concat("0");
      s.concat(String(lit_mari, BIN));
      s.concat(" ");
    }
    else
    {
      s.concat("00");
      s.concat(String(cifre, BIN));
      s.concat(" ");
    }
  }
  text = s;
}


void generateHardBinaryDecrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int lit_mari = random(65, 91);
    int cifre = random(48, 58);
    int simbol = random(0, 22);
    int alegere = random(1, 4);
    if (alegere == 1)
    {
      s.concat("0");
      s.concat(String(lit_mari, BIN));
      s.concat(" ");
    }
    else if (alegere == 2)
    {
      s.concat("00");
      s.concat(String(cifre, BIN));
      s.concat(" ");
    }
    else
    {
      if (simb[simbol] >= 32 && simb[simbol] < 64)
        s.concat("00");
      else if (simb[simbol] >= 64 && simb[simbol] < 128)
        s.concat("0");
      s.concat(String(simb[simbol], BIN));
      s.concat(" ");
    }
    if (i == 2)
      s.concat(" ");
  }
  text = s;
}

void PlayBinaryDecrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyBinaryDecrypt();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyBinaryDecrypt();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumBinaryDecrypt();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardBinaryDecrypt();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayBinaryDecrypt(slot);
}

void GetTastePlayBinaryDecrypt(int slot)
{
  String corect = BinaryDecrypt(text);
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckBinaryDecrypt() == corect.length())
          {
            TextVerificareBinaryDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareBinaryDecrypt(false, corect.length() - CheckBinaryDecrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckBinaryDecrypt() == corect.length())
          {
            TextVerificareBinaryDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareBinaryDecrypt(false, corect.length() - CheckBinaryDecrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}

int bin_val(char c)
{
  if (c == '0')
    return 0;
  return 1;
}

String BinaryDecrypt(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  char text_char[95];
  text.toCharArray(text_char, 95);
  char *p = strtok(text_char, " ");
  while (p)
  {
    int val = bin_val(p[0]) * 128 + bin_val(p[1]) * 64 + bin_val(p[2]) * 32 + bin_val(p[3]) * 16 + bin_val(p[4]) * 8 + bin_val(p[5]) * 4 + bin_val(p[6]) * 2 + bin_val(p[7]) * 1;
    res.concat((char) val);
    p = strtok(NULL, " ");
  }
  return res;
}

int CheckBinaryDecrypt()
{
  int nr = 0;
  String corect = BinaryDecrypt(text);
  for (int i = 0; i < corect.length(); i++)
    if (sir[i] == corect[i])
      nr++;
  return nr;
}

void TextVerificareBinaryDecrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = BinaryDecrypt(text).length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.print('\n');
    tft.print(BinaryDecrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverBinary(slot);
        }
        else
        {
          PlayBinaryDecrypt(slot);
          break;
        }
      }
    }

  }
}

void CryptDecryptMenuVigenerePlay(int slot)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        PlayVigenereEncrypt(slot);
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
      {
        PlayVigenereDecrypt(slot);
        break;
      }
    }
  }
}

String key;

void generateEasyVigenere()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int poz = random(0, 26);
    s.concat((char) ('A' + poz));
  }
  String t;
  for (int i = 0; i < t.length(); i++)
    t[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int poz = random(0, 26);
    t.concat((char) ('A' + poz));
  }
  text = s;
  key = t;
}

void generateMediumVigenere()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int poz = random(0, 26);
    s.concat((char) ('A' + poz));
  }
  String t;
  for (int i = 0; i < t.length(); i++)
    t[i] = '\0';
  int lungime = random(1, 6);
  for (int i = 0; i < lungime; i++)
  {
    int poz = random(0, 26);
    t.concat((char) ('A' + poz));
  }
  text = s;
  key = t;
}

void generateHardVigenere()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(0, 26);
    s.concat((char) ('A' + poz));
  }
  String t;
  for (int i = 0; i < t.length(); i++)
    t[i] = '\0';
  int lungime = random(5, 11);
  for (int i = 0; i < lungime; i++)
  {
    int poz = random(0, 26);
    t.concat((char) ('A' + poz));
  }
  text = s;
  key = t;
}

void enter_stringVig()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.setCursor(5, 60);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Text: ");
  tft.print(text);
  tft.print('\n');
  tft.print("Cheie: ");
  tft.print(key);
}

void PlayVigenereEncrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyVigenere();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyVigenere();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumVigenere();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardVigenere();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_stringVig();
  GetTastePlayVigenereEncrypt(slot);
}

void GetTastePlayVigenereEncrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_stringVig();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckVigenereEncrypt() == text.length())
          {
            TextVerificareVigenereEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareVigenereEncrypt(false, text.length() - CheckVigenereEncrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_stringVig();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckVigenereEncrypt() == text.length())
          {
            TextVerificareVigenereEncrypt(true, 0, slot);

          }
          else
          {
            TextVerificareVigenereEncrypt(false, text.length() - CheckVigenereEncrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}



String VigenereEncrypt(String s, String key)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  int k = 0;
  for (int i = 0; i < s.length(); i++)
  {
    if (key[k] == 0)
      k = 0;
    res.concat((char)((s[i] + (key[k] - 'A') - 'A') % 26 + 'A'));
    k++;
  }
  return res;
}

int CheckVigenereEncrypt()
{
  int nr = 0;
  String corect = VigenereEncrypt(text, key);
  for (int i = 0; i < corect.length(); i++)
    if (sir[i] == corect[i])
      nr++;

  return nr;
}

void TextVerificareVigenereEncrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    tft.print('\n');
    tft.print(VigenereEncrypt(text, key));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverVigenere(slot);
        }
        else
        {
          PlayVigenereEncrypt(slot);
          break;
        }
      }
    }

  }
}

void GameOverVigenere(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(RED);
  tft.setCursor(70, 0);
  tft.print("GAME      OVER");
  tft.setTextSize(2);
  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);
  tft.print("Numarul maxim de   caractere gresite  acceptate a fost   depasit!");
  tft.print("\n\n\nXP: +");
  tft.print(XP_crnt);
  tft.print("\nScor: ");
  tft.print(score);

  tft.fillRect(75, 250, 90, 35, RED);
  tft.setCursor(100, 257);
  tft.setTextSize(3);
  tft.print("OK");



  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);
  if (score > var.HighScoreVigenere)
  {
    var.HighScoreVigenere = score;
    EEPROM.put(loc, var);
    tft.setCursor(10, 220);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("(High Score nou)");
  }
  EEPROM.get(loc, var);
  int lvl = var.Level, xp_lvl = var.XPLevel;
  if (XP_crnt < 50 + (lvl - 1) * 5)
  {
    var.XPLevel += XP_crnt;
    if (var.XPLevel >= 50 + (lvl - 1) * 5)
    {
      var.XPLevel -= 50 + (lvl - 1) * 5;
      var.Level++;
      tft.setCursor(120, 183);
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print("Level up!");
    }
    EEPROM.put(loc, var);
  }
  else
  {
    while (XP_crnt >= 50 + (lvl - 1) * 5)
    {
      XP_crnt -= 50 + (lvl - 1) * 5;
      lvl++;
    } ///cat timp poate creste levelul
    var.XPLevel += XP_crnt;
    var.Level = lvl;
    tft.setCursor(120, 183);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("Level up!");
    EEPROM.put(loc, var);
  }
  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 385 && p.x <= 670 && p.y >= 760 && p.x <= 855)
      {
        EcranProfil(slot);
        break;
      }
    }

  }
}

void PlayVigenereDecrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyVigenere();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyVigenere();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumVigenere();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardVigenere();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_stringVig();
  GetTastePlayVigenereDecrypt(slot);
}

void GetTastePlayVigenereDecrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_stringVig();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckVigenereDecrypt() == text.length())
          {
            TextVerificareVigenereDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareVigenereDecrypt(false, text.length() - CheckVigenereDecrypt(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_stringVig();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckVigenereDecrypt() == text.length())
          {
            TextVerificareVigenereDecrypt(true, 0, slot);

          }
          else
          {
            TextVerificareVigenereDecrypt(false, text.length() - CheckVigenereDecrypt(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}



String VigenereDecrypt(String s, String key)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  int k = 0;
  for (int i = 0; i < s.length(); i++)
  {
    if (key[k] == 0)
      k = 0;
    int p = s[i] - 'A';
    int n = key[k] - 'A';
    if (p - n < 0)
    {
      char c = s[i];
      while (n)
      {
        c--;
        n--;
        if (c == 64)
          c = 90;
      }
      res.concat(c);
    }
    else
      res.concat((char) (s[i] - n));
    k++;
  }
  return res;
}

int CheckVigenereDecrypt()
{
  int nr = 0;
  String corect = VigenereDecrypt(text, key);
  for (int i = 0; i < corect.length(); i++)
    if (sir[i] == corect[i])
      nr++;

  return nr;
}

void TextVerificareVigenereDecrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    tft.print('\n');
    tft.print(VigenereDecrypt(text, key));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverVigenere(slot);
        }
        else
        {
          PlayVigenereDecrypt(slot);
          break;
        }
      }
    }

  }
}

void generateEasyAtbash()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int poz = random(0, 26);
    s.concat((char) ('A' + poz));
  }
  text = s;
}

void generateMediumAtbash()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int poz = random(0, 26);
    s.concat((char) ('A' + poz));
  }
  text = s;
}

void generateHardAtbash()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(0, 26);
    s.concat((char) ('A' + poz));
  }
  text = s;
}


void PlayAtbash(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  tast_litere();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyAtbash();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyAtbash();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumAtbash();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardAtbash();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }

  displayScore(score);
  enter_string();
  GetTastePlayAtbash(slot);
}

void GetTastePlayAtbash(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckAtbash() == text.length())
          {
            TextVerificareAtbash(true, 0, slot);

          }
          else
          {
            TextVerificareAtbash(false, text.length() - CheckAtbash(), slot);
          }
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('W');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('E');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('R');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('T');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('U');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('I');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('O');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayCharPlay('A');
          else if (p.x >= 275 && p.x <= 325)
            displayCharPlay('S');
          else if (p.x >= 330 && p.x <= 380)
            displayCharPlay('D');
          else if (p.x >= 385 && p.x <= 435)
            displayCharPlay('F');
          else if (p.x >= 440 && p.x <= 490)
            displayCharPlay('G');
          else if (p.x >= 495 && p.x <= 545)
            displayCharPlay('H');
          else if (p.x >= 550 && p.x <= 600)
            displayCharPlay('J');
          else if (p.x >= 605 && p.x <= 655)
            displayCharPlay('K');
          else if (p.x >= 660 && p.x <= 710)
            displayCharPlay('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayCharPlay('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayCharPlay('X');
          else if (p.x >= 360 && p.x <= 410)
            displayCharPlay('C');
          else if (p.x >= 415 && p.x <= 465)
            displayCharPlay('V');
          else if (p.x >= 470 && p.x <= 520)
            displayCharPlay('B');
          else if (p.x >= 525 && p.x <= 575)
            displayCharPlay('N');
          else if (p.x >= 580 && p.x <= 630)
            displayCharPlay('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPlay();
          enter_string();
          len--;
          sir[len] = 0;
          afisare_sir(2);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          if (CheckAtbash() == text.length())
          {
            TextVerificareAtbash(true, 0, slot);

          }
          else
          {
            TextVerificareAtbash(false, text.length() - CheckAtbash(), slot);
          }
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayCharPlay(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('1');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('2');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('3');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('4');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('5');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('6');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('7');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('8');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('9');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('@');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('.');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('$');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay('_');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay('&');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('-');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('+');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('(');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay(')');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay('<');
          else if (p.x >= 245 && p.x <= 295)
            displayCharPlay('*');
          else if (p.x >= 300 && p.x <= 350)
            displayCharPlay('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayCharPlay(':');
          else if (p.x >= 410 && p.x <= 460)
            displayCharPlay(';');
          else if (p.x >= 465 && p.x <= 515)
            displayCharPlay('!');
          else if (p.x >= 520 && p.x <= 570)
            displayCharPlay('?');
          else if (p.x >= 575 && p.x <= 625)
            displayCharPlay('=');
          else if (p.x >= 630 && p.x <= 680)
            displayCharPlay('%');
          else if (p.x >= 685 && p.x <= 735)
            displayCharPlay('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayCharPlay(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayCharPlay('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textboxPlay();
        enter_string();
        afisare_sir(2);
      }
    }
    delay(200);
  }
}



String Atbash(String s)
{
  String res;
  for (int i = 0; i < res.length(); i++)
    res[i] = '\0';
  int k = 0;
  for (int i = 0; i < s.length(); i++)
  {
    res.concat((char)(26 - (s[i] - 'A' + 1) + 'A'));
  }
  return res;
}

int CheckAtbash()
{
  int nr = 0;
  String corect = Atbash(text);
  for (int i = 0; i < corect.length(); i++)
    if (sir[i] == corect[i])
      nr++;

  return nr;
}

void TextVerificareAtbash(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    tft.print('\n');
    tft.print(Atbash(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverAtbash(slot);
        }
        else
        {
          PlayAtbash(slot);
          break;
        }
      }
    }

  }
}

void GameOverAtbash(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(RED);
  tft.setCursor(70, 0);
  tft.print("GAME      OVER");
  tft.setTextSize(2);
  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);
  tft.print("Numarul maxim de   caractere gresite  acceptate a fost   depasit!");
  tft.print("\n\n\nXP: +");
  tft.print(XP_crnt);
  tft.print("\nScor: ");
  tft.print(score);

  tft.fillRect(75, 250, 90, 35, RED);
  tft.setCursor(100, 257);
  tft.setTextSize(3);
  tft.print("OK");



  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);
  if (score > var.HighScoreAtbash)
  {
    var.HighScoreAtbash = score;
    EEPROM.put(loc, var);
    tft.setCursor(10, 220);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("(High Score nou)");
  }
  EEPROM.get(loc, var);
  int lvl = var.Level, xp_lvl = var.XPLevel;
  if (XP_crnt < 50 + (lvl - 1) * 5)
  {
    var.XPLevel += XP_crnt;
    if (var.XPLevel >= 50 + (lvl - 1) * 5)
    {
      var.XPLevel -= 50 + (lvl - 1) * 5;
      var.Level++;
      tft.setCursor(120, 183);
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print("Level up!");
    }
    EEPROM.put(loc, var);
  }
  else
  {
    while (XP_crnt >= 50 + (lvl - 1) * 5)
    {
      XP_crnt -= 50 + (lvl - 1) * 5;
      lvl++;
    } ///cat timp poate creste levelul
    var.XPLevel += XP_crnt;
    var.Level = lvl;
    tft.setCursor(120, 183);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("Level up!");
    EEPROM.put(loc, var);
  }
  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 385 && p.x <= 670 && p.y >= 760 && p.x <= 855)
      {
        EcranProfil(slot);
        break;
      }
    }

  }
}

void TastLitereProfil()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillRect(0, 170, 239, 150, BLUE);
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
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("SPACE");
  tft.drawRect(45, 275, 100, 30, YELLOW);

  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  tft.setTextSize(2);

}

void TastCifProfil()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillRect(0, 170, 239, 150, BLUE);
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
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("SPACE");
  tft.drawRect(45, 275, 100, 30, YELLOW);

  tft.setTextSize(2);
}

void textboxPlay()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 100, 239, 70, WHITE);
  tft.fillRect(0, 55, 239, 40, BLUE);


}

void textboxUser()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 50, 240, 30, WHITE);
}

void textboxPass()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 135, 240, 30, WHITE);
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
  for (int i = 1; i <= 7; i++)
    tft.drawLine(x1++, y1, x2++, y2, BLACK);
  x1 = 50;
  y1 = 210;
  x2 = 5;
  y2 = 250;
  for (int i = 1; i <= 7; i++)
    tft.drawLine(x1++, y1, x2++, y2, BLACK);
  tft.setCursor(75, 225);
  tft.print("Sterge profil");

  getTastePlay();
}


void afisareSirProfil(int slot, bool isPassword)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);

  if (isPassword)
  {
    tft.setCursor(5, 143);
    for (int i = 0; i < user[slot - 1].password_len - 1; i++)
      tft.print('*');
    tft.print(user[slot - 1].parola[user[slot - 1].password_len - 1]);
    delay(500);
    textboxPass();
    tft.setCursor(5, 143);
    for (int i = 0; i < user[slot - 1].password_len; i++)
      tft.print('*');

  }
  else
  {
    tft.setCursor(5, 57);
    for (int i = 0; i < user[slot - 1].username_len; i++)
      tft.print(user[slot - 1].username[i]);
  }
}

void displayUserAndPass(int slot, char c, bool isPassword)
{
  if (isPassword)
    user[slot - 1].parola[user[slot - 1].password_len++] = c;
  else
    user[slot - 1].username[user[slot - 1].username_len++] = c;
  afisareSirProfil(slot, isPassword);
}

void CreateProfile(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);



  tft.fillScreen(BLUE);
  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");
  tft.setCursor(0, 30);
  tft.setTextSize(2);
  tft.print("Username");
  tft.fillRect(0, 50, 240, 30, WHITE);
  tft.setCursor(0, 115);
  tft.print("Parola");
  tft.fillRect(0, 135, 240, 30, WHITE);
  TastLitereProfil();
  GetTasteNewProfile(slot);


}

void MeniuAdaugaProfil()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(BLUE);

  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  tft.drawRect(0, 40, 240, 80, YELLOW);
  tft.drawRect(0, 130, 240, 80, YELLOW);
  tft.drawRect(0, 220, 240, 80, YELLOW);

  if (EEPROM.read(0) == 0)
  {
    tft.setCursor(60, 70);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    EEPROM.get(4, var);
    tft.setCursor(60, 70);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
    Serial.print(var.username);
  }

  if (EEPROM.read(1) == 0)
  {
    tft.setCursor(60, 160);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    int location = 4;
    location += sizeof(var);
    EEPROM.get(location, var);
    tft.setCursor(60, 160);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
  }

  if (EEPROM.read(2) == 0)
  {
    tft.setCursor(60, 250);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    int location = 4;
    location += 2 * sizeof(var);
    EEPROM.get(location, var);
    tft.setCursor(60, 250);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
  }
  GetTasteMeniuAdd();
}


void MeniuIncarcaProfil()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(BLUE);

  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  tft.drawRect(0, 40, 240, 80, YELLOW);
  tft.drawRect(0, 130, 240, 80, YELLOW);
  tft.drawRect(0, 220, 240, 80, YELLOW);

  if (EEPROM.read(0) == 0)
  {
    tft.setCursor(60, 70);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    EEPROM.get(4, var);
    tft.setCursor(60, 70);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
    Serial.print(var.username);
  }

  if (EEPROM.read(1) == 0)
  {
    tft.setCursor(60, 160);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    int location = 4;
    location += sizeof(var);
    EEPROM.get(location, var);
    tft.setCursor(60, 160);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
  }

  if (EEPROM.read(2) == 0)
  {
    tft.setCursor(60, 250);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    int location = 4;
    location += 2 * sizeof(var);
    EEPROM.get(location, var);
    tft.setCursor(60, 250);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
  }
  GetTasteMeniuLoad();
}

void MeniuStergeProfil()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(BLUE);

  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  tft.drawRect(0, 40, 240, 80, YELLOW);
  tft.drawRect(0, 130, 240, 80, YELLOW);
  tft.drawRect(0, 220, 240, 80, YELLOW);

  if (EEPROM.read(0) == 0)
  {
    tft.setCursor(60, 70);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    EEPROM.get(4, var);
    tft.setCursor(60, 70);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
    Serial.print(var.username);
  }

  if (EEPROM.read(1) == 0)
  {
    tft.setCursor(60, 160);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    int location = 4;
    location += sizeof(var);
    EEPROM.get(location, var);
    tft.setCursor(60, 160);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
  }

  if (EEPROM.read(2) == 0)
  {
    tft.setCursor(60, 250);
    tft.print("(slot gol)");
  }
  else
  {

    profil var;
    int location = 4;
    location += 2 * sizeof(var);
    EEPROM.get(location, var);
    tft.setCursor(60, 250);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print(var.username);
  }
  GetTasteMeniuDelete();
}


void getTastePlay()
{
  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        MainMenu();
        break;
      }
      else if (p.x >= 160 && p.x <= 325)
      {
        if (p.y >= 260 && p.y <= 390)
        {
          MeniuAdaugaProfil();
          break;
        }
        else if (p.y >= 445 && p.y <= 575)
        {
          MeniuIncarcaProfil();
          break;
        }
        else if (p.y >= 630 && p.y <= 760)
        {
          MeniuStergeProfil();
          break;
        }
      }
    }
    delay(300);
  }


}

void chenar(bool isPassword)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  if (!isPassword)
  {
    tft.fillRect(0, 25, 100, 25, BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(WHITE);
    tft.print("Username");
  }
  else
  {
    tft.fillRect(0, 110, 100, 25, BLACK);
    tft.setCursor(0, 115);
    tft.setTextColor(WHITE);
    tft.print("Parola");
    tft.fillRect(0, 25, 100, 25, BLUE);
    tft.setCursor(0, 30);
    tft.setTextColor(WHITE);
    tft.print("Username");
  }
}

void GetTasteMeniuAdd()
{

  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        ProfileMenu();
        break;
      }
      else if (p.x >= 160 && p.x <= 925)
      {
        if (p.y >= 250 && p.y <= 440)
        {
          if (EEPROM.read(0) == 1)
          {
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);

            tft.fillRect(0, 100, 239, 100, YELLOW);
            tft.setTextSize(2);
            tft.setTextColor(BLACK);
            tft.setCursor(5, 110);
            tft.print("Profilul aflat pe  slot va fi sters.  Continuati?");
            tft.fillRect(20, 165, 60, 30, BLACK);
            tft.fillRect(160, 165, 60, 30, BLACK);
            tft.setCursor(35, 173);
            tft.setTextColor(WHITE);
            tft.print("DA");
            tft.setCursor(175, 173);
            tft.print("NU");
            while (1)
            {
              TSPoint p = ts.getPoint();
              if (p.z > ts.pressureThreshhold)
              {
                Serial.print(p.x);
                Serial.print(' ');
                Serial.print(p.y);
                Serial.print('\n');
                if (p.y >= 555 && p.y <= 630)
                {
                  if (p.x >= 215 && p.x <= 390)
                  {
                    for (int i = 0; i < user[0].username_len; i++)
                      user[0].username[i] = 0;
                    for (int i = 0; i < user[0].password_len; i++)
                      user[0].parola[i] = 0;
                    user[0].username_len = 0;
                    user[0].password_len = 0;
                    CreateProfile(1);
                    break;
                  }
                  else if (p.x >= 660 && p.x <= 845)
                  {
                    MeniuAdaugaProfil();
                    break;
                  }
                }

              }
            }
          }
          else
          {
            CreateProfile(1);
            break;
          }
        }
        else if (p.y >= 470 && p.y <= 660)
        {
          if (EEPROM.read(1) == 1)
          {
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);

            tft.fillRect(0, 100, 239, 100, YELLOW);
            tft.setTextSize(2);
            tft.setTextColor(BLACK);
            tft.setCursor(5, 110);
            tft.print("Slot-ul nu este gol, iar profilul aflat pe slot va fi sters. Continuati?");
            tft.fillRect(20, 165, 60, 30, BLACK);
            tft.fillRect(160, 165, 60, 30, BLACK);
            tft.setCursor(35, 173);
            tft.setTextColor(WHITE);
            tft.print("DA");
            tft.setCursor(175, 173);
            tft.print("NU");
            while (1)
            {
              TSPoint p = ts.getPoint();
              if (p.z > ts.pressureThreshhold)
              {
                Serial.print(p.x);
                Serial.print(' ');
                Serial.print(p.y);
                Serial.print('\n');
                if (p.y >= 555 && p.y <= 630)
                {
                  if (p.x >= 215 && p.x <= 390)
                  {
                    CreateProfile(2);
                    break;
                  }
                  else if (p.x >= 660 && p.x <= 845)
                  {
                    MeniuAdaugaProfil();
                    break;
                  }
                }

              }
            }
          }
          else
          {
            CreateProfile(2);
            break;
          }
        }
        else if (p.y >= 690 && p.y <= 880)
        {
          if (EEPROM.read(2) == 1)
          {
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);

            tft.fillRect(0, 100, 239, 100, YELLOW);
            tft.setTextSize(2);
            tft.setTextColor(BLACK);
            tft.setCursor(5, 110);
            tft.print("Slot-ul nu este gol, iar profilul aflat pe slot va fi sters. Continuati?");
            tft.fillRect(20, 165, 60, 30, BLACK);
            tft.fillRect(160, 165, 60, 30, BLACK);
            tft.setCursor(35, 173);
            tft.setTextColor(WHITE);
            tft.print("DA");
            tft.setCursor(175, 173);
            tft.print("NU");
            while (1)
            {
              TSPoint p = ts.getPoint();
              if (p.z > ts.pressureThreshhold)
              {
                Serial.print(p.x);
                Serial.print(' ');
                Serial.print(p.y);
                Serial.print('\n');
                if (p.y >= 555 && p.y <= 630)
                {
                  if (p.x >= 215 && p.x <= 390)
                  {
                    CreateProfile(3);
                    break;
                  }
                  else if (p.x >= 660 && p.x <= 845)
                  {
                    MeniuAdaugaProfil();
                    break;
                  }
                }

              }
            }
          }
          else
          {
            CreateProfile(3);
            break;
          }
        }
      }
    }
    delay(300);
  }
}

void getPassword(int slot, int mod) ///mod = 1 - load, mod = 2 - sterge
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  if (EEPROM.read(slot - 1) == 0)
    mesaj_slot_gol_load(slot);
  else
  {

    tft.fillScreen(BLUE);
    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");
    tft.setCursor(0, 30);
    tft.setTextSize(2);
    tft.print("Username");
    tft.fillRect(0, 50, 240, 30, WHITE);
    tft.setCursor(0, 115);
    tft.print("Parola");
    tft.fillRect(0, 135, 240, 30, WHITE);

    tft.setCursor(5, 57);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    profil var;
    int loc = 4;
    if (slot == 2)
      loc += sizeof(var);
    else if (slot == 3)
      loc += 2 * sizeof(var);

    tft.print(EEPROM.get(loc, var.username));

    TastLitereProfil();
    GetTasteIntroducereParola(slot, mod);
  }

}

void StatsMenu(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(CYAN);
  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);

  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.setCursor(70, 5);
  tft.print("STATS");
  tft.setTextSize(2);
  tft.setCursor(0, 60);
  tft.print("Morse: ");
  tft.print(var.HighScoreMorse);
  tft.print("\nCesar: ");
  tft.print(var.HighScoreCesar);
  tft.print("\nHEX: ");
  tft.print(var.HighScoreHex);
  tft.print("\nBinary: ");
  tft.print(var.HighScoreBinary);
  tft.print("\nVigenere: ");
  tft.print(var.HighScoreVigenere);
  tft.print("\nAtbash: ");
  tft.print(var.HighScoreAtbash);

  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        EcranProfil(slot);
        break;
      }
    }
  }

}

void EcranProfil(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillScreen(YELLOW);
  tft.fillRect(0, 0, 60, 20, RED);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 5);
  tft.print("BACK");

  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);

  tft.fillRect(0, 35, 239, 60, BLUE);
  tft.fillRect(50, 130, 130, 60, RED);
  tft.fillRect(50, 220, 130, 60, RED);

  tft.setCursor(0, 40);
  tft.setTextColor(RED);
  tft.print("Profil: ");
  tft.print(var.username);
  tft.print("\nLevel: ");
  tft.print(var.Level);
  tft.print("\nXP:");
  tft.print(var.XPLevel);
  tft.print('/');
  tft.print(50 + (var.Level - 1) * 5);

  tft.setCursor(76, 148);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.print("PLAY");
  tft.setCursor(68, 238);
  tft.print("STATS");

  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        ProfileMenu();
        break;
      }
      else if (p.y >= 460 && p.y <= 610 && p.x >= 310 && p.x <= 720)
      {
        CypherMenuPlay(slot);
        break;
      }
      else if (p.y >= 685 && p.y <= 835 && p.x >= 310 && p.x <= 720)
      {
        StatsMenu(slot);
        break;
      }
    }
  }
}

void ParolaGresita(int slot, int mod)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 100, 239, 100, YELLOW);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(5, 110);
  tft.print("Parola introdusa este gresita!");
  tft.fillRect(85, 165, 60, 30, BLACK);
  tft.setCursor(100, 173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("OK");

  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.y >= 555 && p.y <= 630 && p.x >= 425 && p.y <= 610)
      {
        getPassword(slot, mod);
        break;
      }
    }
  }
}

void GetTasteIntroducereParola(int slot, int mod)
{
  int mode = 1;
  for (int i = 0; i < user[3].password_len; i++)
    user[3].parola[i] = 0;
  user[3].password_len = 0;
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  bool isPassword = true;
  chenar(isPassword);
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPass();
          user[3].password_len--;
          user[3].parola[user[3].password_len] = 0;
          pinMode(A1, OUTPUT);
          pinMode(A2, OUTPUT);
          tft.setCursor(5, 143);
          for (int i = 0; i < user[3].password_len; i++)
            tft.print('*');
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          profil var;
          int loc = 4;
          if (slot == 2)
            loc += sizeof(var);
          else if (slot == 3)
            loc += 2 * sizeof(var);
          EEPROM.get(loc, var);

          if (strcmp(user[3].parola, var.parola) == 0)
          {
            if (mod == 1)
              EcranProfil(slot);
            else
              DeleteProfile(slot);
            break;
          }
          else
          {
            ParolaGresita(slot, mod);
            break;
          }
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          TastCifProfil();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayUserAndPass(4, ' ', isPassword);
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(4, 'Q', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(4, 'W', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(4, 'E', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(4, 'R', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(4, 'T', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(4, 'Y', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(4, 'U', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(4, 'I', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(4, 'O', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(4, 'P', isPassword);

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayUserAndPass(4, 'A', isPassword);
          else if (p.x >= 275 && p.x <= 325)
            displayUserAndPass(4, 'S', isPassword);
          else if (p.x >= 330 && p.x <= 380)
            displayUserAndPass(4, 'D', isPassword);
          else if (p.x >= 385 && p.x <= 435)
            displayUserAndPass(4, 'F', isPassword);
          else if (p.x >= 440 && p.x <= 490)
            displayUserAndPass(4, 'G', isPassword);
          else if (p.x >= 495 && p.x <= 545)
            displayUserAndPass(4, 'H', isPassword);
          else if (p.x >= 550 && p.x <= 600)
            displayUserAndPass(4, 'J', isPassword);
          else if (p.x >= 605 && p.x <= 655)
            displayUserAndPass(4, 'K', isPassword);
          else if (p.x >= 660 && p.x <= 710)
            displayUserAndPass(4, 'L', isPassword);
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayUserAndPass(4, 'Z', isPassword);
          else if (p.x >= 305 && p.x <= 355)
            displayUserAndPass(4, 'X', isPassword);
          else if (p.x >= 360 && p.x <= 410)
            displayUserAndPass(4, 'C', isPassword);
          else if (p.x >= 415 && p.x <= 465)
            displayUserAndPass(4, 'V', isPassword);
          else if (p.x >= 470 && p.x <= 520)
            displayUserAndPass(4, 'B', isPassword);
          else if (p.x >= 525 && p.x <= 575)
            displayUserAndPass(4, 'N', isPassword);
          else if (p.x >= 580 && p.x <= 630)
            displayUserAndPass(4, 'M', isPassword);
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textboxPass();
          user[3].password_len--;
          user[3].parola[user[3].password_len] = 0;
          pinMode(A1, OUTPUT);
          pinMode(A2, OUTPUT);
          tft.setCursor(5, 143);
          for (int i = 0; i < user[3].password_len; i++)
            tft.print('*');
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          profil var;
          int loc = 4;
          if (slot == 2)
            loc += sizeof(var);
          else if (slot == 3)
            loc += 2 * sizeof(var);
          EEPROM.get(loc, var);
          if (strcmp(user[3].parola, var.parola) == 0)
          {
            if (mod == 1)
              EcranProfil(slot);
            else
              DeleteProfile(slot);
            break;
          }
          else
          {
            ParolaGresita(slot, mod);
            break;
          }
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          TastLitereProfil();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayUserAndPass(4, ' ', isPassword);
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(4, '1', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(4, '2', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(4, '3', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(4, '4', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(4, '5', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(4, '6', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(4, '7', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(4, '8', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(4, '9', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(4, '0', isPassword);

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(4, '@', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(4, '.', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(4, '$', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(4, '_', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(4, '&', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(4, '-', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(4, '+', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(4, '(', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(4, ')', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(4, '/', isPassword);

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(4, '<', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(4, '*', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(4, '\'', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(4, ':', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(4, ';', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(4, '!', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(4, '?', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(4, '=', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(4, '%', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(4, '>', isPassword);
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(4, ',', isPassword);
          else if (p.x >= 630 && p.x <= 680)
          {
            displayUserAndPass(4, '\"', isPassword);
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        MeniuAdaugaProfil();
        break;
      }
    }
    delay(200);
  }
}

void GetTasteMeniuLoad()
{
  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        ProfileMenu();
        break;
      }
      else if (p.x >= 160 && p.x <= 925)
      {
        if (p.y >= 250 && p.y <= 440)
        {
          getPassword(1, 1);
          break;
        }
        else if (p.y >= 470 && p.y <= 660)
        {
          getPassword(2, 1);
          break;
        }
        else if (p.y >= 690 && p.y <= 880)
        {
          getPassword(3, 1);
          break;
        }
      }
    }
    delay(300);
  }
}

void mesaj_slot_gol_load(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 100, 239, 100, YELLOW);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(5, 110);
  tft.print("Slot-ul selectat   este gol!");
  tft.fillRect(85, 165, 60, 30, BLACK);
  tft.setCursor(100, 173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("OK");

  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.y >= 555 && p.y <= 630 && p.x >= 425 && p.y <= 610)
      {
        MeniuIncarcaProfil();
        break;
      }
    }
  }
}

void mesaj_stergere(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 100, 239, 100, YELLOW);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(5, 110);
  if (EEPROM.read(slot - 1) == 0)
  {
    tft.print("Slot-ul selectat   este gol!");
    tft.fillRect(85, 165, 60, 30, BLACK);
    tft.setCursor(100, 173);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("OK");

    while (1)
    {
      TSPoint p = ts.getPoint();
      if (p.z > ts.pressureThreshhold)
      {
        Serial.print(p.x);
        Serial.print(' ');
        Serial.print(p.y);
        Serial.print('\n');
        if (p.y >= 555 && p.y <= 630 && p.x >= 425 && p.y <= 610)
        {
          MeniuStergeProfil();
          break;
        }
      }
    }
  }
  else
  {
    tft.print("Doriti sa stergeti profilul");
    profil var;
    if (slot == 1)
    {
      EEPROM.get(4, var);
      tft.print('\n');
      tft.setTextColor(RED);
      tft.print("      ");
      tft.print(var.username);
      tft.setTextColor(BLACK);
      tft.print("?");
    }
    else if (slot == 2)
    {
      int loc = 4;
      loc += sizeof(var);
      EEPROM.get(loc, var);
      tft.print('\n');
      tft.setTextColor(RED);
      tft.print("      ");
      tft.print(var.username);
      tft.setTextColor(BLACK);
      tft.print("?");
    }
    else if (slot == 3)
    {
      int loc = 4;
      loc += 2 * sizeof(var);
      EEPROM.get(loc, var);
      tft.print('\n');
      tft.setTextColor(RED);
      tft.print("      ");
      tft.print(var.username);
      tft.setTextColor(BLACK);
      tft.print("?");
    }
    tft.fillRect(20, 165, 60, 30, BLACK);
    tft.fillRect(160, 165, 60, 30, BLACK);
    tft.setCursor(35, 173);
    tft.setTextColor(WHITE);
    tft.print("DA");
    tft.setCursor(175, 173);
    tft.print("NU");
    while (1)
    {
      TSPoint p = ts.getPoint();
      if (p.z > ts.pressureThreshhold)
      {
        Serial.print(p.x);
        Serial.print(' ');
        Serial.print(p.y);
        Serial.print('\n');
        if (p.y >= 555 && p.y <= 630)
        {
          if (p.x >= 215 && p.x <= 390)
          {
            getPassword(slot, 2);
            break;
          }
          else if (p.x >= 660 && p.x <= 845)
          {
            MeniuStergeProfil();
            break;
          }
        }

      }
    }
  }
}

void DeleteProfile(int slot)
{
  int marime = sizeof(user[0]), loc = 4;
  if (slot == 1)
  {
    EEPROM.update(0, 0);
  }
  else if (slot == 2)
  {
    EEPROM.update(1, 0);
    loc += marime;
  }
  else if (slot == 3)
  {
    EEPROM.update(2, 0);
    loc += 2 * marime;
  }
  for (int i = loc; i < EEPROM.length() && marime; i++, marime--)
    EEPROM.update(i, 0);
  resetare();
}


void GetTasteMeniuDelete()
{
  while (1)
  {
    TSPoint p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        ProfileMenu();
        break;
      }
      else if (p.x >= 160 && p.x <= 925)
      {
        if (p.y >= 250 && p.y <= 440)
        {
          mesaj_stergere(1);
          break;
        }
        else if (p.y >= 470 && p.y <= 660)
        {
          mesaj_stergere(2);
          break;
        }
        else if (p.y >= 690 && p.y <= 880)
        {
          mesaj_stergere(3);
          break;
        }
      }
    }
    delay(300);
  }
}

void GetTasteNewProfile(int slot)
{
  int mode = 1;
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  bool isPassword = false;
  chenar(isPassword);
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {

          if (isPassword)
          {
            textboxPass();
            user[slot - 1].password_len--;
            user[slot - 1].parola[user[slot - 1].password_len] = 0;
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);
            tft.setCursor(5, 143);
            for (int i = 0; i < user[slot - 1].password_len; i++)
              tft.print('*');
          }
          else
          {
            textboxUser();
            user[slot - 1].username_len--;
            user[slot - 1].username[user[slot - 1].username_len] = 0;
            afisareSirProfil(slot, isPassword);
          }
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          if (!isPassword)
          {
            isPassword = true;
            chenar(isPassword);

          }
          else
          {
            if (slot == 1)
            {
              EEPROM.put(4, user[0]);
              EEPROM.update(0, 1);
            }
            else if (slot == 2)
            {
              int loc = 4;
              loc += sizeof(user[0]);
              EEPROM.put(loc, user[1]);
              EEPROM.update(1, 1);
            }
            else if (slot == 3)
            {
              int loc = 4;
              loc += sizeof(user[0]);
              loc += sizeof(user[1]);
              EEPROM.put(loc, user[2]);
              EEPROM.update(2, 1);
            }
            resetare();
            break;
          }
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          TastCifProfil();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayUserAndPass(slot, ' ', isPassword);
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(slot, 'Q', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(slot, 'W', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(slot, 'E', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(slot, 'R', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(slot, 'T', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(slot, 'Y', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(slot, 'U', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(slot, 'I', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(slot, 'O', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(slot, 'P', isPassword);

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayUserAndPass(slot, 'A', isPassword);
          else if (p.x >= 275 && p.x <= 325)
            displayUserAndPass(slot, 'S', isPassword);
          else if (p.x >= 330 && p.x <= 380)
            displayUserAndPass(slot, 'D', isPassword);
          else if (p.x >= 385 && p.x <= 435)
            displayUserAndPass(slot, 'F', isPassword);
          else if (p.x >= 440 && p.x <= 490)
            displayUserAndPass(slot, 'G', isPassword);
          else if (p.x >= 495 && p.x <= 545)
            displayUserAndPass(slot, 'H', isPassword);
          else if (p.x >= 550 && p.x <= 600)
            displayUserAndPass(slot, 'J', isPassword);
          else if (p.x >= 605 && p.x <= 655)
            displayUserAndPass(slot, 'K', isPassword);
          else if (p.x >= 660 && p.x <= 710)
            displayUserAndPass(slot, 'L', isPassword);
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayUserAndPass(slot, 'Z', isPassword);
          else if (p.x >= 305 && p.x <= 355)
            displayUserAndPass(slot, 'X', isPassword);
          else if (p.x >= 360 && p.x <= 410)
            displayUserAndPass(slot, 'C', isPassword);
          else if (p.x >= 415 && p.x <= 465)
            displayUserAndPass(slot, 'V', isPassword);
          else if (p.x >= 470 && p.x <= 520)
            displayUserAndPass(slot, 'B', isPassword);
          else if (p.x >= 525 && p.x <= 575)
            displayUserAndPass(slot, 'N', isPassword);
          else if (p.x >= 580 && p.x <= 630)
            displayUserAndPass(slot, 'M', isPassword);
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          if (isPassword)
          {
            textboxPass();
            user[slot - 1].password_len--;
            user[slot - 1].parola[user[slot - 1].password_len] = 0;
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);
            tft.setCursor(5, 143);
            for (int i = 0; i < user[slot - 1].password_len; i++)
              tft.print('*');
          }
          else
          {
            textboxUser();
            user[slot - 1].username_len--;
            user[slot - 1].username[user[slot - 1].username_len] = 0;
            afisareSirProfil(slot, isPassword);
          }
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          if (!isPassword)
          {
            isPassword = true;
          }
          else
          {
            if (slot == 1)
            {
              EEPROM.put(4, user[0]);
              EEPROM.update(0, 1);
            }
            else if (slot == 2)
            {
              int loc = 4;
              loc += sizeof(user[0]);
              EEPROM.put(loc, user[1]);
              EEPROM.update(1, 1);
            }
            else if (slot == 3)
            {
              int loc = 4;
              loc += sizeof(user[0]);
              loc += sizeof(user[1]);
              EEPROM.put(loc, user[2]);
              EEPROM.update(2, 1);
            }
            resetare();
            break;
          }
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          TastLitereProfil();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayUserAndPass(slot, ' ', isPassword);
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(slot, '1', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(slot, '2', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(slot, '3', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(slot, '4', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(slot, '5', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(slot, '6', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(slot, '7', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(slot, '8', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(slot, '9', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(slot, '0', isPassword);

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(slot, '@', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(slot, '.', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(slot, '$', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(slot, '_', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(slot, '&', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(slot, '-', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(slot, '+', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(slot, '(', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(slot, ')', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(slot, '/', isPassword);

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(slot, '<', isPassword);
          else if (p.x >= 245 && p.x <= 295)
            displayUserAndPass(slot, '*', isPassword);
          else if (p.x >= 300 && p.x <= 350)
            displayUserAndPass(slot, '\'', isPassword);
          else if (p.x >= 355 && p.x <= 405)
            displayUserAndPass(slot, ':', isPassword);
          else if (p.x >= 410 && p.x <= 460)
            displayUserAndPass(slot, ';', isPassword);
          else if (p.x >= 465 && p.x <= 515)
            displayUserAndPass(slot, '!', isPassword);
          else if (p.x >= 520 && p.x <= 570)
            displayUserAndPass(slot, '?', isPassword);
          else if (p.x >= 575 && p.x <= 625)
            displayUserAndPass(slot, '=', isPassword);
          else if (p.x >= 630 && p.x <= 680)
            displayUserAndPass(slot, '%', isPassword);
          else if (p.x >= 685 && p.x <= 735)
            displayUserAndPass(slot, '>', isPassword);
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayUserAndPass(slot, ',', isPassword);
          else if (p.x >= 630 && p.x <= 680)
          {
            displayUserAndPass(slot, '\"', isPassword);
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        MeniuAdaugaProfil();
        break;
      }
    }
    delay(200);
  }
}

void Play()
{
  ProfileMenu();

}

String morse(char c)
{
  if (c >= 'a' && c <= 'z')
    c -= 32;

  if (c == 'A')
    return ".-";
  if (c == 'B')
    return "-...";
  if (c == 'C')
    return "-.-.";
  if (c == 'D')
    return "-..";
  if (c == 'E')
    return ".";
  if (c == 'F')
    return "..-.";
  if (c == 'G')
    return "--.";
  if (c == 'H')
    return "....";
  if (c == 'I')
    return "..";
  if (c == 'J')
    return ".---";
  if (c == 'K')
    return "-.-";
  if (c == 'L')
    return ".-..";
  if (c == 'M')
    return "--";
  if (c == 'N')
    return "-.";
  if (c == 'O')
    return "---";
  if (c == 'P')
    return ".--.";
  if (c == 'Q')
    return "--.-";
  if (c == 'R')
    return ".-.";
  if (c == 'S')
    return "...";
  if (c == 'T')
    return "-";
  if (c == 'U')
    return "..-";
  if (c == 'V')
    return "...-";
  if (c == 'W')
    return ".--";
  if (c == 'X')
    return "-..-";
  if (c == 'Y')
    return "-.--";
  if (c == 'Z')
    return "--..";
  if (c == '0')
    return "-----";
  if (c == '1')
    return ".----";
  if (c == '2')
    return "..---";
  if (c == '3')
    return "...--";
  if (c == '4')
    return "....-";
  if (c == '5')
    return ".....";
  if (c == '6')
    return "-....";
  if (c == '7')
    return "--...";
  if (c == '8')
    return "---..";
  if (c == '9')
    return "----.";
  if (c == ',')
    return "--..--";
  if (c == '.')
    return ".-.-.-";
  if (c == '?')
    return "..--..";
  if (c == ';')
    return "-.-.-.";
  if (c == ':')
    return "---...";
  if (c == '/')
    return "-..-.";
  if (c == '-')
    return "-....-";
  if (c == '(')
    return "-.--.";
  if (c == ')')
    return "-.--.-";
  if (c == '_')
    return "..--.-";
  if (c == '@')
    return ".--.-.";
  if (c == '!')
    return "-.-.--";
  if (c == '&')
    return ".-...";
  if (c == '=')
    return "-...-";
  if (c == '+')
    return ".-.-.";
  if (c == '$')
    return "...-..-";
  if (c == ' ')
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

void afisare_sir(int mode)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.setTextColor(RED);
  if (len == 134)
  {
    textbox();
    smaller = true;
  }

  if (smaller == true)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  if (mode == 1) //work
    tft.setCursor(5, 45);
  else
    tft.setCursor(5, 105);
  tft.print(sir);
}

void displayChar(char x)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  if (isVig == true && isKey == true && !litera(x))
    error_message();
  else
  {
    sir[len++] = x;
    afisare_sir(1);
  }


}

void displayCharPlay(char x)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  if (isVig == true && isKey == true && !litera(x))
    error_message();
  else
  {
    sir[len++] = x;
    afisare_sir(2);
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
  for (int i = 0; i < 100; i++)
    result[i] = "\0";
  textbox();
  for (int i = 0; sir[i] != 0; i++)
  {
    result[i] = morse(sir[i]);
    l += result[i].length();
  }
  tft.setCursor(5, 45);
  if (smaller == true || l >= 134)
  {
    tft.setTextSize(1);
    val_endl = 35;
  }
  int lungRand = 0;
  for (int i = 0; result[i] != 0; i++)
  {
    lungRand += result[i].length();
    if (lungRand <= val_endl)
    {
      tft.print(result[i]);
      if (lungRand < val_endl)
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
      if (lungRand < 19)
      {
        tft.print(' ');
        lungRand++;
      }
    }
  }
  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
    }

  }

}


String MorseEncrypt(String s)
{
  String result;
  for (int i = 0; i < result.length(); i++)
    result[i] = '\0';
  int l = s.length();
  for (int i = 0; i < l - 1; i++)
  {
    result.concat(morse(s[i]));
    result.concat(" ");
  }
  result.concat(morse(s[l - 1]));
  return result;
}

int CheckMorseEncrypt()
{
  String correct_answer = MorseEncrypt(text);
  char correct_answer_char[correct_answer.length() + 10];
  correct_answer.toCharArray(correct_answer_char, correct_answer.length() + 10);
  char correct_char[10][10];
  char answer_char[10][10];
  int k = 0, l = 0;
  Serial.print('\n');
  Serial.print(correct_answer_char);
  Serial.print('\n');
  char *p = strtok(correct_answer_char, " ");
  while (p)
  {
    strcpy(correct_char[k++], p);
    p = strtok(NULL, " ");
  }
  p = strtok(sir, " ");
  while (p)
  {
    strcpy(answer_char[l++], p);
    p = strtok(NULL, " ");
  }
  int nr = 0;
  for (int i = 0; i < k; i++)
  {
    Serial.print(correct_char[i]);
    Serial.print(' ');
    Serial.print(answer_char[i]);
    Serial.print('\n');
    if (strcmp(correct_char[i], answer_char[i]) == 0)
      nr++;

  }

  Serial.print(nr);
  return nr;

}

int generate_difficulty()
{
  randomSeed(analogRead(A7));
  return random(1, 4);
}


void PlayMorseEncrypt(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  for (int i = 0; i < text.length(); i++)
    text[i] = 0;
  tft.fillScreen(BLACK);
  resetString();
  textboxPlay();
  TastMorseEncryptPlay();
  int dif = generate_difficulty();
  Serial.print(dif);
  Serial.print('\n');
  if (first == true)
  {
    first = false;
    display_difficulty("EASY");
    generateEasyMorseEncrypt();
  }
  else
  {
    if (dif == 1)
    {
      display_difficulty("EASY");
      generateEasyMorseEncrypt();
    }
    else if (dif == 2)
    {
      display_difficulty("MEDIUM");
      generateMediumMorseEncrypt();
    }
    else if (dif == 3)
    {
      display_difficulty("HARD");
      generateHardMorseEncrypt();
    }
  }
  for (int i = 0; i < text.length(); i++)
  {
    Serial.print(i);
    Serial.print(' ');
    Serial.print(text[i]);
    Serial.print('\n');
  }
  displayScore(score);
  enter_string();

  GetTastePlayMorseEncrypt(slot);
}

void TastMorseEncryptPlay()
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


  tft.fillRect(195, 171, 45, 25, GREEN);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.setCursor(210, 173);
  tft.print('-');
}


void generateEasyMorseEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 3; i++)
  {
    int poz = random(0, 26);
    s.concat(MorseChars[poz]);
  }
  text = s;
}

void generateMediumMorseEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 5; i++)
  {
    int poz = random(0, 36);
    s.concat(MorseChars[poz]);

  }
  text = s;
}

void generateHardMorseEncrypt()
{
  randomSeed(analogRead(A7));
  String s;
  for (int i = 0; i < s.length(); i++)
    s[i] = '\0';
  for (int i = 0; i < 10; i++)
  {
    int poz = random(0, 53);
    s.concat(MorseChars[poz]);
  }
  text = s;
}

void GetTastePlayMorseEncrypt(int slot)
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      /**Serial.print("X = "); Serial.print(p.x);
        Serial.print("\tY = "); Serial.print(p.y);
        Serial.print("\tPressure = "); Serial.println(p.z); **/
      if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
      {
        textboxPlay();
        enter_string();
        len--;
        sir[len] = 0;
        afisare_sir(2);
      }
      else if (p.y >= 580 && p.y <= 810)
      {
        if (p.x >= 180 && p.x <= 340)
          displayCharPlay('.');
        else if (p.x >= 360 && p.x <= 545)
          displayCharPlay('-');
        else if (p.x >= 550 && p.x <= 750)
          displayCharPlay('/');
      }
      else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayCharPlay(' ');
      else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
      {
        Serial.print("OK");
        sir[len] = 0;
        if (CheckMorseEncrypt() == text.length())
        {
          TextVerificareMorseEncrypt(true, 0, slot);

        }
        else
        {
          TextVerificareMorseEncrypt(false, text.length() - CheckMorseEncrypt(), slot);
        }
        break;
      }

    }
    if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
    {
      CypherMenuPlay(slot);
      break;
    }
    else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
    {
      smaller = true;
      TastMorseEncryptPlay();
      textboxPlay();
      enter_string();
      afisare_sir(2);
    }
    delay(200);
  }
}

void TextVerificareMorseEncrypt(bool corect, int gresite, int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.fillRect(0, 40, 239, 130, CYAN);
  tft.setCursor(5, 45);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  int dif = text.length();
  if (corect == 1)
  {
    tft.print("CORECT!");
    tft.print('\n');
    if (dif == 3)
    {
      tft.print("+5 XP\n");
      XP_crnt += 5;
    }
    else if (dif == 5)
    {
      tft.print("+10 XP\n");
      XP_crnt += 10;
    }
    else if (dif == 10)
    {
      tft.print("+20 XP\n");
      XP_crnt += 20;
    }
    tft.print("Scor: +");
    tft.print(dif * 10);
    score += dif * 10;
  }
  else
  {
    tft.print("GRESIT!\n");
    tft.print("Raspuns corect: ");
    if (dif == 10)
      tft.setTextSize(1);
    tft.print(MorseEncrypt(text));
    tft.setTextSize(2);
    tft.print("\nXP: +");
    tft.print(dif - gresite);
    XP_crnt += dif - gresite;
    tft.print("\nScor: ");
    int scor = 10 * (dif - gresite) - 5 * gresite;
    if (scor > 0)
      tft.print("+");
    tft.print(scor);
    score += scor;
  }

  tft.fillRect(85, 135, 70, 30, GRAY);
  tft.setCursor(95, 143);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);
  tft.print("NEXT");

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        if (gresite > dif / 2)
        {
          GameOverMorse(slot);
        }
        else
        {
          PlayMorseEncrypt(slot);
          break;
        }
      }
    }

  }

}

void GameOverMorse(int slot)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.fillScreen(BLACK);
  tft.setTextSize(4);
  tft.setTextColor(RED);
  tft.setCursor(70, 0);
  tft.print("GAME      OVER");
  tft.setTextSize(2);
  tft.setCursor(0, 90);
  tft.setTextColor(WHITE);
  tft.print("Numarul maxim de   caractere gresite  acceptate a fost   depasit!");
  tft.print("\n\n\nXP: +");
  tft.print(XP_crnt);
  tft.print("\nScor: ");
  tft.print(score);

  tft.fillRect(75, 250, 90, 35, RED);
  tft.setCursor(100, 257);
  tft.setTextSize(3);
  tft.print("OK");



  profil var;
  int loc = 4;
  if (slot == 2)
    loc += sizeof(var);
  else if (slot == 3)
    loc += 2 * sizeof(var);
  EEPROM.get(loc, var);
  if (score > var.HighScoreMorse)
  {
    var.HighScoreMorse = score;
    EEPROM.put(loc, var);
    tft.setCursor(10, 220);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("(High Score nou)");
  }
  EEPROM.get(loc, var);
  int lvl = var.Level, xp_lvl = var.XPLevel;
  if (XP_crnt < 50 + (lvl - 1) * 5)
  {
    var.XPLevel += XP_crnt;
    if (var.XPLevel >= 50 + (lvl - 1) * 5)
    {
      var.XPLevel -= 50 + (lvl - 1) * 5;
      var.Level++;
      tft.setCursor(120, 183);
      tft.setTextSize(2);
      tft.setTextColor(RED);
      tft.print("Level up!");
    }
    EEPROM.put(loc, var);
  }
  else
  {
    while (XP_crnt >= 50 + (lvl - 1) * 5)
    {
      XP_crnt -= 50 + (lvl - 1) * 5;
      lvl++;
    } ///cat timp poate creste levelul
    var.XPLevel += XP_crnt;
    var.Level = lvl;
    tft.setCursor(120, 183);
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.print("Level up!");
    EEPROM.put(loc, var);
  }
  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 385 && p.x <= 670 && p.y >= 760 && p.x <= 855)
      {
        EcranProfil(slot);
        break;
      }
    }

  }
}


void display_difficulty(String s)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.setCursor(180, 5);
  tft.setTextSize(2);
  if (s == "EASY")
    tft.setTextColor(GREEN);
  else if (s == "MEDIUM")
  {
    tft.setTextColor(GOLD);
    tft.setCursor(150, 5);
  }
  else if (s == "HARD")
    tft.setTextColor(RED);
  tft.print(s);
}

void enter_string()
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  tft.setCursor(5, 60);
  if (text.length() > 40)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print(text);
}

void displayScore(int score)
{
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  tft.setTextSize(2);
  tft.setCursor(5, 30);
  tft.setTextColor(YELLOW);
  tft.print("Score: ");
  tft.print(score);
}

void ecran_level()
{
  textboxPlay();
  tast_litere();
  display_difficulty("MEDIUM");
  displayScore(100);
  enter_string();
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

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        textbox();
        afisare_sir(1);
        break;
      }
    }

  }
}

void resetString()
{
  for (int i = 0; i < len; i++)
    sir[i] = 0;
  for (int i = 0; i < len_key; i++)
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          MorseEncrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          MorseEncrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            error_message();
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
      }
    }
    delay(200);
  }
}

char Morse(String s)
{
  if (s == ".-")
    return 'A';
  if (s == "-...")
    return 'B';
  if (s == "-.-.")
    return 'C';
  if (s == "-..")
    return 'D';
  if (s == ".")
    return 'E';
  if (s == "..-.")
    return 'F';
  if (s == "--.")
    return 'G';
  if (s == "....")
    return 'H';
  if (s == "..")
    return 'I';
  if (s == ".---")
    return 'J';
  if (s == "-.-")
    return 'K';
  if (s == ".-..")
    return 'L';
  if (s == "--")
    return 'M';
  if (s == "-.")
    return 'N';
  if (s == "---")
    return 'O';
  if (s == ".--.")
    return 'P';
  if (s == "--.-")
    return 'Q';
  if (s == ".-.")
    return 'R';
  if (s == "...")
    return 'S';
  if (s == "-")
    return 'T';
  if (s == "..-")
    return 'U';
  if (s == "...-")
    return 'V';
  if (s == ".--")
    return 'W';
  if (s == "-..-")
    return 'X';
  if (s == "-.--")
    return 'Y';
  if (s == "--..")
    return 'Z';
  if (s == "-----")
    return '0';
  if (s == ".----")
    return '1';
  if (s == "..---")
    return '2';
  if (s == "...--")
    return '3';
  if (s == "....-" )
    return '4';
  if (s == ".....")
    return '5';
  if (s == "-....")
    return '6';
  if (s == "--...")
    return '7';
  if (s == "---..")
    return '8';
  if (s == "----.")
    return '9';
  if (s == "--..--")
    return ',';
  if (s == ".-.-.-" )
    return '.';
  if (s == "..--..")
    return '?';
  if (s == "-.-.-.")
    return ';';
  if (s == "---...")
    return ':';
  if (s == "-..-.")
    return '/';
  if (s == "-....-")
    return '-';
  if (s == "-.--.")
    return '(';
  if (s == "-.--.-")
    return ')';
  if (s == "..--.-")
    return '_';
  if (s == ".--.-.")
    return '@';
  if (s == "-.-.--")
    return '!';
  if (s == ".-...")
    return '&';
  if (s == "-...-")
    return '=';
  if (s == ".-.-.")
    return '+';
  if (s == "...-..-")
    return '$';
  if (s == "/")
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
  if (strlen(sir) > 600)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  int k = 0;
  char *tok = strtok(sir, " ");
  while (tok)
  {
    String c = String(tok);
    result[k++] = Morse(c);
    tok = strtok(NULL, " ");
  }
  textbox();
  tft.setCursor(5, 45);
  for (int i = 0; i < k; i++)
    tft.print(result[i]);

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      /**Serial.print("X = "); Serial.print(p.x);
        Serial.print("\tY = "); Serial.print(p.y);
        Serial.print("\tPressure = "); Serial.println(p.z); **/
      if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
      {
        textbox();
        len--;
        sir[len] = 0;
        afisare_sir(1);
      }
      else if (p.y >= 580 && p.y <= 810)
      {
        if (p.x >= 180 && p.x <= 340)
          displayChar('.');
        else if (p.x >= 360 && p.x <= 545)
          displayChar('-');
        else if (p.x >= 550 && p.x <= 750)
          displayChar('/');
      }
      else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
        displayChar(' ');
      else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
      {
        sir[len] = 0;
        MorseDecrypt();
        break;
      }

    }
    if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
    {
      CypherMenuWork();
      break;
    }
    else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
    {
      smaller = true;
      TastMorseDecrypt();
      textbox();
      afisare_sir(1);
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

  for (int i = 0; sir[i] != 0; i++)
  {
    if (litera(sir[i]))
      sir[i] = (sir[i] + 3 - 'A') % 26 + 'A';
  }
  textbox();
  afisare_sir(1);

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
    }

  }
}

void CesarDecrypt()
{

  for (int i = 0; sir[i] != 0; i++)
  {
    if (litera(sir[i]))
    {
      if (sir[i] >= 'D' && sir[i] <= 'Z')
        sir[i] = (sir[i] - 3 - 'A') % 26 + 'A';
      else
      {
        switch (sir[i])
        {
          case 'C': sir[i] = 'Z';
            break;
          case 'B': sir[i] = 'Y';
            break;
          case 'A': sir[i] = 'X';
        }
      }
    }

  }
  textbox();
  afisare_sir(1);

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          CesarEncrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          CesarEncrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
      }
    }
    delay(200);
  }
}

void GetTasteCesarDecrypt()
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          CesarDecrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          CesarDecrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
      }
    }
    delay(200);
  }
}

int HexValue(char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  switch (c)
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
  if (strlen(sir) > 45)
  {
    tft.setTextSize(1);
    limit = 14;
  }
  else
    tft.setTextSize(2);
  tft.setCursor(5, 45);
  int nr = 0;
  for (int i = 0; sir[i] != 0; i++)
  {
    nr++;
    if (nr == limit)
    {
      nr = 1;
      tft.print('\n');
    }
    tft.print(sir[i], HEX);
    tft.print(' ');
  }

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  if (strlen(sir) > 350)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);
  for (int i = 0; sir[i] != 0; i += 3)
  {
    tft.print((char) (HexValue(sir[i]) * 16 + HexValue(sir[i + 1])));
  }

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          HexEncrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          HexEncrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
      }
    }
    delay(200);
  }
}

void GetTasteHexDecrypt()
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          HexDecrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            error_message();
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            error_message();
          else if (p.x >= 495 && p.x <= 545)
            error_message();
          else if (p.x >= 550 && p.x <= 600)
            error_message();
          else if (p.x >= 605 && p.x <= 655)
            error_message();
          else if (p.x >= 660 && p.x <= 710)
            error_message();
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            error_message();
          else if (p.x >= 305 && p.x <= 355)
            error_message();
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            error_message();
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            error_message();
          else if (p.x >= 580 && p.x <= 630)
            error_message();
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          HexDecrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
          {
            error_message();
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
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
  if (strlen(sir) > 16)
  {
    tft.setTextSize(1);
    limit = 5;
  }
  for (int i = 0; sir[i] != 0; i++)
  {
    nr++;
    if (nr == limit)
    {
      nr = 1;
      tft.print('\n');
    }
    if (sir[i] == 0 || sir[i] == 1)
      tft.print("0000000");
    else if (sir[i] == 2 || sir[i] == 3)
      tft.print("000000");
    else if (sir[i] >= 4 && sir[i] <= 7)
      tft.print("00000");
    else if (sir[i] >= 8 && sir[i] <= 15)
      tft.print("0000");
    else if (sir[i] >= 16 && sir[i] <= 31)
      tft.print("000");
    else if (sir[i] >= 32 && sir[i] <= 63)
      tft.print("00");
    else if (sir[i] >= 64 && sir[i] <= 127)
      tft.print("0");
    tft.print(sir[i], BIN);
    tft.print(' ');
  }

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  if (strlen(sir) > 1500)
    tft.setTextSize(1);
  else
    tft.setTextSize(2);

  for (int i = 0; sir[i] != 0; i += 9)
  {
    tft.print((char)(128 * (sir[i] - '0') + 64 * (sir[i + 1] - '0') + 32 * (sir[i + 2] - '0') + 16 * (sir[i + 3] - '0') + 8 * (sir[i + 4] - '0') + 4 * (sir[i + 5] - '0') + 2 * (sir[i + 6] - '0') + (sir[i + 7] - '0')));
  }
  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          BinaryEncrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          BinaryEncrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
      }
    }
    delay(200);
  }
}

void GetTasteBinaryDecrypt()
{
  resetString();
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          BinaryDecrypt();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            error_message();
          else if (p.x >= 275 && p.x <= 325)
            error_message();
          else if (p.x >= 330 && p.x <= 380)
            error_message();
          else if (p.x >= 385 && p.x <= 435)
            error_message();
          else if (p.x >= 440 && p.x <= 490)
            error_message();
          else if (p.x >= 495 && p.x <= 545)
            error_message();
          else if (p.x >= 550 && p.x <= 600)
            error_message();
          else if (p.x >= 605 && p.x <= 655)
            error_message();
          else if (p.x >= 660 && p.x <= 710)
            error_message();
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            error_message();
          else if (p.x >= 305 && p.x <= 355)
            error_message();
          else if (p.x >= 360 && p.x <= 410)
            error_message();
          else if (p.x >= 415 && p.x <= 465)
            error_message();
          else if (p.x >= 470 && p.x <= 520)
            error_message();
          else if (p.x >= 525 && p.x <= 575)
            error_message();
          else if (p.x >= 580 && p.x <= 630)
            error_message();
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          sir[len] = 0;
          BinaryDecrypt();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 245 && p.x <= 295)
            error_message();
          else if (p.x >= 300 && p.x <= 350)
            error_message();
          else if (p.x >= 355 && p.x <= 405)
            error_message();
          else if (p.x >= 410 && p.x <= 460)
            error_message();
          else if (p.x >= 465 && p.x <= 515)
            error_message();
          else if (p.x >= 520 && p.x <= 570)
            error_message();
          else if (p.x >= 575 && p.x <= 625)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
            error_message();
          else if (p.x >= 685 && p.x <= 735)
            error_message();
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            error_message();
          else if (p.x >= 630 && p.x <= 680)
          {
            error_message();
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
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
  for (int i = 0; sir[i] != 0; i++)
  {
    if (cheie[k] == 0)
      k = 0;
    if (litera(sir[i]))
    {
      sir[i] = (sir[i] + (cheie[k] - 'A') - 'A') % 26 + 'A';
      k++;
    }

  }
  afisare_sir(1);

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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

  for (int i = 0; sir[i] != 0; i++)
    if (litera(sir[i]))
      sir[i] = 26 - (sir[i] - 'A' + 1) + 'A';
  afisare_sir(1);

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  for (int i = 0; sir[i] != 0; i++)
  {
    if (cheie[k] == 0)
      k = 0;
    if (litera(sir[i]))
    {
      int p = sir[i] - 'A';
      int n = cheie[k] - 'A';
      if (p - n < 0)
      {
        char c = sir[i];
        while (n)
        {
          Serial.print((char) c);
          Serial.print(' ');
          Serial.print(n);
          Serial.print('\n');

          c--;
          n--;
          if (c == 64)
            c = 90;
        }
        sir[i] = c;
      }
      else
        sir[i] = sir[i] - n;
      k++;
    }

  }
  afisare_sir(1);

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          Atbash();
          break;
        }

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          Serial.print("OK");
          sir[len] = 0;
          Atbash();
          break;
        }
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
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

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        textbox();
        afisare_sir(1);
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

  while (1)
  {
    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);
      if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
      {
        textbox();
        afisare_sir(1);
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          if (isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            cheie[len_key] = 0;
            for (int i = 0; i < len; i++)
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

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          if (isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            for (int i = 0; i < len; i++)
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
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
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
  while (1)
  {

    TSPoint p = ts.getPoint();

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);

      if (mode == 1)
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          if (isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            cheie[len_key] = 0;
            for (int i = 0; i < len; i++)
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

        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 2;

          tast_cif_simb();

        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('Q');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('W');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('E');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('R');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('T');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('Y');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('U');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('I');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('O');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('P');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 220 && p.x <= 270)
            displayChar('A');
          else if (p.x >= 275 && p.x <= 325)
            displayChar('S');
          else if (p.x >= 330 && p.x <= 380)
            displayChar('D');
          else if (p.x >= 385 && p.x <= 435)
            displayChar('F');
          else if (p.x >= 440 && p.x <= 490)
            displayChar('G');
          else if (p.x >= 495 && p.x <= 545)
            displayChar('H');
          else if (p.x >= 550 && p.x <= 600)
            displayChar('J');
          else if (p.x >= 605 && p.x <= 655)
            displayChar('K');
          else if (p.x >= 660 && p.x <= 710)
            displayChar('L');
        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 250 && p.x <= 300)
            displayChar('Z');
          else if (p.x >= 305 && p.x <= 355)
            displayChar('X');
          else if (p.x >= 360 && p.x <= 410)
            displayChar('C');
          else if (p.x >= 415 && p.x <= 465)
            displayChar('V');
          else if (p.x >= 470 && p.x <= 520)
            displayChar('B');
          else if (p.x >= 525 && p.x <= 575)
            displayChar('N');
          else if (p.x >= 580 && p.x <= 630)
            displayChar('M');
        }

      }
      else
      {
        if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
        {
          textbox();
          len--;
          sir[len] = 0;
          afisare_sir(1);
        }
        else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
        {
          if (isKey)
          {
            strcpy(cheie, sir);
            len_key = len;
            for (int i = 0; i < len; i++)
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
        else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
        {
          mode = 1;
          tast_litere();
        }
        else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
          displayChar(' ');
        else if (p.y >= 600 && p.y <= 660)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('1');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('2');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('3');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('4');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('5');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('6');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('7');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('8');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('9');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('0');

        }
        else if (p.y >= 670 && p.y <= 730)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('@');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('.');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('$');
          else if (p.x >= 355 && p.x <= 405)
            displayChar('_');
          else if (p.x >= 410 && p.x <= 460)
            displayChar('&');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('-');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('+');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('(');
          else if (p.x >= 630 && p.x <= 680)
            displayChar(')');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('/');

        }
        else if (p.y >= 740 && p.y <= 800)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar('<');
          else if (p.x >= 245 && p.x <= 295)
            displayChar('*');
          else if (p.x >= 300 && p.x <= 350)
            displayChar('\'');
          else if (p.x >= 355 && p.x <= 405)
            displayChar(':');
          else if (p.x >= 410 && p.x <= 460)
            displayChar(';');
          else if (p.x >= 465 && p.x <= 515)
            displayChar('!');
          else if (p.x >= 520 && p.x <= 570)
            displayChar('?');
          else if (p.x >= 575 && p.x <= 625)
            displayChar('=');
          else if (p.x >= 630 && p.x <= 680)
            displayChar('%');
          else if (p.x >= 685 && p.x <= 735)
            displayChar('>');
        }
        else if (p.y >= 810 && p.y <= 870)
        {
          if (p.x >= 190 && p.x <= 240)
            displayChar(',');
          else if (p.x >= 630 && p.x <= 680)
          {
            displayChar('\"');
          }
        }

      }
      if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 780 && p.x <= 915 && p.y >= 595 && p.y <= 645)
      {
        smaller = true;
        if (mode == 1)
          tast_litere();
        else
          tast_cif_simb();
        textbox();
        afisare_sir(1);
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseMorseEncrypt();
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseCesarEncrypt();
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseHexEncrypt();
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseBinaryEncrypt();
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      if (p.x >= 720 && p.x <= 895 && p.y >= 870 && p.y <= 915)
      {
        CypherMenuWork();
        break;
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 200 && p.y <= 560)
      {
        CaseVigenereEncrypt();
      }
      else if (p.x >= 200 && p.x <= 910 && p.y >= 565 && p.y <= 930)
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

  while (1)
  {
    p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)
    {
      Serial.print(p.x);
      Serial.print(' ');
      Serial.print(p.y);
      Serial.print('\n');
      if (p.x >= 390 && p.x <= 700 && p.y >= 160 && p.y <= 380)
      {
        Play();
        break;
      }
      else if (p.x >= 390 && p.x <= 700 && p.y >= 430 && p.y <= 650)
      {
        Work();
        break;
      }
      else if (p.x >= 390 && p.x <= 700 && p.y >= 690 && p.y <= 920)
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
  while (1)
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