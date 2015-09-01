/* Wiedergabeauswertungstabelle für die Funktion Rechner:
 * 0 : Keine Fehler!
 * 1 : Mathematischer- oder Implementierungsfehler
 * 2 : Kritischer Fehler, zurzeit noch nicht (seriös) implementiert
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static float Speicher [3]; 	// Speicher des Rechners
static char S_Code;		//Code für die Verwendete Sprache
int started = 0;

int Rechner();
void Sprachauswahl(int Intro);
void Ergebnisausgabe(float Aus);
void Speicherausgabe();
void Operatorunbekannt();
void Nooverflow();
void Divisionnull();
void Negativewurzel();
void Hilfausgabe();
void changelog();
void Kritisch();

int main()
{
  extern int started;
  
  if (!started){
      printf("Calculator Version 0.3.10!\tFor help type 1 ? 1!\n"\
             "For other languages than English type 1 L 1\n");		//"Intro
      started = 1;							//Sorgt für einmalige Intro-Ausgabe
  }
  if (Rechner() != 2)
    main();
}

int Rechner()
{
  int zi1 = 42, zi2 = 42; 		//zi als Integerausweichzahlen für Modulo!
  float erg = 42, z1 = 42, z2 = 42;  	//Zahlen zum Rechnen ;D
  char o, Fehler = 0, Speicherung = 0;	//o für Operator, Fehler(anzeige), Speicherung um anzuzeigen, dass mit dem Speicher gearbeitet wird

  scanf("%f %s %f", &z1, &o, &z2);   //Eingabe einlesen
  if (z1 > 99999999999 || z2 > 99999999999){
    Nooverflow();
    Fehler = 1;
    return 1;
  }
  else switch(o)
  {
    case '+':
     erg = z1+z2;
     break;
      
    case '-':
     erg = z1-z2;
     break;
    
    case '*':
     erg = z1*z2;
     break;
      
     case '/':
      if (z2 == 0){	//Man sollte nicht durch 0 teilen
        Divisionnull();
        Fehler = 1;
        return 1;
        }
      else
        erg = z1/z2;
      break;
      
    case '^':
      erg = pow(z1,z2);
      break;
      
    case '?':
      Hilfausgabe();
      Fehler = 1; 	//Fehler Wahr setzen, damit keine Ergebnisausgabe kommt!
      return 0;
      break;
    
    case 'M':
      zi2 = --z2;
      Speicher[zi2] += z1;
      Speicherung = 1;	//Wir arbeiten mit dem Speicher und rechnen nicht -> Keine Ergebnisausgabe
      break;
      
    case 'm':
      zi2 = --z2;
      Speicher[zi2] -= z1;
      Speicherung = 1;	//Wir arbeiten mit dem Speicher und rechnen nicht -> Keine Ergebnisausgabe
      break;
    
    case '\\':
     if (z2 == 0){	//Man sollte nicht durch 0 teilen ...
       Divisionnull();
       Fehler = 1;
       return 1;
       }
     else{ 
       zi1 = z1;	//Modulo braucht Integer ... Da haste ...
       zi2 = z2;
       erg = zi1%zi2;
     }
     break;
    
    case 'L':
      Sprachauswahl(1);
      Fehler = 1;	//Fehler Wahr setzen, damit keine Ergebnisausgabe kommt!
      return 0;
      break;
     
    case '#':
      if (z1 < 0){
	Negativewurzel();
	Fehler = 1;
	return 1;
	}
      erg = pow(z1,1/z2);
      break;
      
    case 'C':
      changelog();
      Fehler = 1;	//Fehler Wahr setzen, damit keine Ergebnisausgabe kommt!
      return 0;
      break;
      
    case 'Q':		//Für die lulz ein test auf kritische Fehler!
     printf("A critical error occured!!\nSome \"debugging\" Output:\n%f %f %f\n%d %d\n%f %f %f\n"	//Inline Fehlerausgabe mit Debug-Infos
            "%d %d %d %d\n", erg, z1, z2, zi1, zi2, Speicher[0], Speicher[1], Speicher[2], o, Fehler, Speicherung, S_Code);
     Fehler = 1;
     return 2;
     break;

    default:
     Operatorunbekannt();
     Fehler = 1;
     return 1;
     break;
      }
  if (!Fehler){
    if (!Speicherung)		//Die Ergebnisausgabe soll nur kommen, wenn _nicht_ mit dem speicher gearbeitet wird!
      Ergebnisausgabe(erg);
    Speicherausgabe();
    return 0;
  }
}

//Funktion zur Auswahl in welcher Sprache man denn alles möchte
void Sprachauswahl(int Intro)
{
  if (Intro)
    printf("Type your language code!\nFor all available languages and their complementary codes type ?\n");
  scanf("%s", &S_Code);
  switch(S_Code){
    case '?':
      printf("Available languages and their codes are atm (case sensitive):\nG -> German (Deutsch)\n"\
             "E -> English\nq to quit\nWell, thats it for now …\n");
      Sprachauswahl(0);
      break;
      
    case 'D':
      printf("Sprachausgabe zu Deutsch gewechselt!\n");
      S_Code = 'D';
      break;
      
    case 'E':
      printf("Language switched to English!\n");
      S_Code = 'E';
      break;
      
    case 'q':
      break;
      
    default:
      printf("Unknown Code, you may type q to quit!\n");
      Sprachauswahl(0);
      break;
  }      
}

void Ergebnisausgabe(float Aus)
{
  switch(S_Code){
    case 'D':
      printf("Das Ergebnis ist: %.5f\n", Aus);
      break;
    
    default:
      printf("The result is: %.5f\n", Aus);
      break;
  }
}

void Speicherausgabe()
{
    switch(S_Code){
    case 'D':
      printf("Zwischenspeicher 1: %.5f\tZwischenspeicher 2: %.5f\tZwischenspeicher 3: %.5f\n", Speicher[0], Speicher[1], Speicher[2]);
      break;
    
    default:
      printf("Memory 1: %.5f\tMemory 2: %.5f\tMemory 3: %.5f\n", Speicher[0], Speicher[1], Speicher[2]);
      break;
  }
}

void Operatorunbekannt()
{
  switch(S_Code){
  case 'D':
    printf("IMPOSSIBURU! (Unbekannter Operator oder unerwarteter Fehler)\n");
    break;
  
  default:
    printf("What?! (Unknown Operator, or error)\n");
    break;
  }
}

void Nooverflow()
{
  switch(S_Code){
  case 'D':
    printf("Bitte kein Overflow …\n");
    break;
  
  default:
    printf("Please avoid overflow …\n");
    break;
  }
}

void Divisionnull()
{
  int i;
  
  switch(S_Code){
  case 'D':
    for(i=0; i<=5; i++) 
      printf("WAS HAST DU GETAN?!\n");
    break;
  
  default:
    for(i=0; i<=5; i++) 
      printf("WHAT HAVE YOU DONE?!\n");
    break;
  }
}

void Negativewurzel()
{
  switch(S_Code){
  case 'D':
    printf("Du kannst nicht die Wurzel einer negativen Zahl ziehen\n");
    break;
  
  default:
    printf("You can't get the root of a negative number\n");
    break;
  }
}

void Hilfausgabe()
{
  switch(S_Code){
    case 'D':
      printf("C-Taschenrechner! Programmiert von Kondou!\nFolgende Syntax muss für Erfolg eingehalten werden:\n"\
             "Beliebige Zahl (Punkt statt Komma für Nachkommabereich) Leerzeichen Operator Leerzeichen Beliebige Zahl\n"\
	     "Beispielsweise 5.3 * 2.7\nFolgende Operatoren stehen zur Zeit zur Auswahl:\n+ -> Addition\n"\
	     "- -> Subtraktion\n* -> Multiplikation\n/ -> Division (besser nicht durch 0)\n"\
	     "\\ -> Modulo (Rest einer ganzzahligen Division)\n^ -> Potenzierung\nH -> Diese Hilfe anzeigen\n"\
	     "# -> Radizierung (Basis # Grad)\nM -> Addiere zum Speicher[Zahl 2] (z.B. \"5 M 1\", M[1]=5\n"\
	     "m -> Subtrahiere vom Speicher[Zahl 2] (z.B. \"5 m 2\", M[2]=-5)\nC -> Zeige den Changelog\n");
      break;
    
    default:
      printf("C-Calculator! Programmed by Kondou!\nThe following syntax has to be keeped for success:\n"\
             "Random number (Use a dot instead of a comma for the fractional digits) Space Operator Space Random Number\n"\
             "For example 5.3 * 2.7\nThe followiing operators can be chosen:\n+ -> addition\n"\
	     "- -> subtraction\n* -> multiplication\n/ -> division (better not divide by 0)\n"\
	     "\\ -> Modulus (rest of an integer division)\n^ -> exponentiation\nH -> Show this help\n"\
	     "# -> root extraction (base # degree)\nM -> add to (the) memory[Number 2] (z.B. \"5 M 1\", M[1]=5\n"\
	     "m -> subtract from memory[Number 2] (z.B. \"5 m 2\", M[2]=-5)\nC -> Show the changelog\n");
      break;
  }
}

void changelog()
{
  switch(S_Code){
    case 'D':
      printf("Unterschiede zwischen 0.3.1 -> 0.3.10:\n-Quelltext ist nun Compilerfreundlicher\n-Changelog hinzugefügt\n"\
	     "-Einige interne Änderungen\n-Bugfixes :/\n");
      break;
      
    default:
      printf("Changes between 0.3.1 -> 0.3.10:\n-Source-Code is now more compiler friendly\n-Added Changelog\n"\
	     "-Some intern Changes\n-Bugfixes :/\n");
      break;
  }
}
