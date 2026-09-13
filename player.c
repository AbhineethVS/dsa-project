#include "player.h"
#include "models.h"

#include <stdio.h>
#include <stdlib.h>

#define HISTORY_MAX 50

/*
                    player.c
              /        |        \
             /         |         \     
        Queue         Stack      Player State
          ↓             ↓            ↓
      Play Next      History     Current Song 


*/

int currentSongId = -1;
int isPlayingFlag = 0;
char currentPlaylistName[64] = "";
int currentPlaylistIndex = -1;

struct historyStack{
      int top;
      int arr[HISTORY_MAX];
} history = {
      .top = -1
};

//top points to element on top of stack.


/*

NOTE: Syntax

historyStack_t history = {
      .top = 3,
      .arr = {1,2,3,4}
};

*/


int pushRecentlyPlayed(int id){
      if(history.top == HISTORY_MAX - 1){
            return ERR_FULL;
      }

      history.top++;
      history.arr[history.top] = id;
      
      return OK;
}

int popRecentlyPlayed(int *id){
      /*
      NOTE
      The int being returned by the function is the Status code (like OK, ERR_INVALID, etc.)
      Thus we need to return the song id through the int *id passed to the function
      */

      if(id == NULL){
            return ERR_INVALID;
      }

      if(history.top == -1){
            return ERR_EMPTY;
      }

      *id = history.arr[history.top];
      history.top--;

      return OK;
}