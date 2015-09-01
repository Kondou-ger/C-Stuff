/* 
 * Returntable for the function Hangman:
 * 0 : 
 * 1 : 
 * 2 : 
 */

#include <stdio.h>
//#include <math.h>   Necessary?
//#include <stdlib.h> Necessary?
//#include <unistd.h> sleep (derp)

int GameOver = 0;
static int letterswrong, started;
static char lettersleft[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int Hangman();
inline void lettersout();
void Hangdraw(int Number);

int main()
{
  extern int GameOver;
  
  if (!started){
    printf("\nHangman Version 0.0.18! Coded by Kondou!");		//"Intro
    started = 1;
  }
  Hangman();
  if (!GameOver)
    main();
}

//Main Function for the game
//Maybe include in main?
int Hangman()
{
  extern int GameOver;
  char Input;
  
  Hangdraw(letterswrong);
  lettersout();
  printf("_\n\n");
  scanf("%s", &Input);
  switch (Input){
    case 'u':
      printf("You win! The word is 'u'\n");
      GameOver = 1;     
      break;
      
    default:
      letterswrong++;
      printf("\n\n");
      break;
  }
      
  if (letterswrong==10){
    GameOver = 1;
    printf("You lose! The word was 'u'!\n");
  }
} 

//putting out, which letters are still not said
inline void lettersout()
{
  int i;
  
  for (i=0; i<26; i++){
    printf("%o ", lettersleft[i]);
  }
  printf("\n");
}
  

//Draw the Hangman, Number as Counter how much letters went wrong
void Hangdraw(int Number)
{
  switch (Number){
    case 0:
      printf("\n\n\n\n\n\n\n"); //6 Lines for the Hangmandrawing, and a newline for formatting
      break;
      
    case 1:
      printf("\n\n\n\n\n ____\n"); //Bottom of the Hangmandrawing
      break;
      
    case 2:
      printf("|\n|\n|\n|\n|\n|____\n");
      break;
      
    case 3:
      printf("____\n|\n|\n|\n|\n|_____\n");
      break;
      
    case 4:
      printf("____\n|  |\n|\n|\n|\n|_____\n");
      break;
      
    case 5:
      printf("____\n|  |\n| |_|\n|\n|\n|_____\n"); 
      break;
      
    case 6:
      printf("____\n|  |\n| |_|\n|  |\n|  |\n|_____\n");
      break;
   
    case 7:
      printf("____\n|  |\n| |_|\n| \\|\n|  |\n|_____\n");
      break;
      
    case 8:
      printf("____\n|  |\n| |_|\n| \\|/\n|  |\n|_____\n");
      break;
      
    case 9:
      printf("____\n|  |\n| |_|\n| \\|/\n|  |\n|_/___\n");
      break;
      
    case 10:
      printf("____\n|  |\n| |_|\n| \\|/\n|  |\n|_/_\\_\n");
      break;      
      
    default:
      printf("An unexpexted error occured!\n");
      break;
  }
}
