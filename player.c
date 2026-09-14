#include "player.h"
#include "models.h"
#include "playlist.h"
#include "library.h"

#include <stdio.h>
#include <stdlib.h>



/*
*********************************************************************

                        HISTORY STACK
            
*********************************************************************
*/

#define HISTORY_MAX 50

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
      NOTE TO SELF
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




/*
*********************************************************************

                        PLAY NEXT QUEUE

*********************************************************************
*/

//implementing a circular queue for Play Next Queue

#define QUEUE_MAX 50

struct playNextQueue{
      int front;
      int rear;
      int count;
      int arr[QUEUE_MAX];
} queue = {
      .front = 0,
      .rear = 0,
      .count = 0  //count keeps count of number of elements in queue to check if it is full
};

int enqueuePlayNext(int id){
      if(queue.count >= QUEUE_MAX){
            return ERR_FULL;
      }
      if(queue.count != 0){
            queue.rear = (queue.rear + 1) % QUEUE_MAX;
      }

      queue.arr[queue.rear] = id;
      queue.count++;

      return OK;
}

int dequeuePlayNext(int* id){

      if(id == NULL){
            return ERR_INVALID;
      }

      if(queue.count <= 0){
            return ERR_EMPTY;
      }

      *id = queue.arr[queue.front];
      queue.front = (queue.front + 1) % QUEUE_MAX;
      queue.count--;

      return OK;
}

int clearPlayNext(){
      queue.front = 0;
      queue.rear = 0;
      queue.count = 0;

      return OK;
}



/*
*********************************************************************

                        PLAYER STATE

*********************************************************************
*/

int currentSongId = -1;
int isPlayingFlag = 0;
char currentPlaylistName[64] = "";
int currentPlaylistIndex = -1;
Playlist *currentPlaylist = NULL;


int playSong(int id){

      Song* song = searchSongById(id);

      if(song == NULL){
            return ERR_NOT_FOUND;
      }

      currentSongId = id;
      isPlayingFlag = 1;

      printf("\nPlaying : %s", song -> title);
      return OK;
}

int pauseSong(){
      isPlayingFlag = 0;

      printf("Song Paused");

      return OK;
}

int resumeSong(){

      if(currentSongId == -1){
            return ERR_INVALID;
      }

      Song* song = searchSongById(currentSongId);

      if(song == NULL){
            return ERR_NOT_FOUND;
      }

      isPlayingFlag = 1;
      printf("\nPlaying : %s", song -> title);

      return OK;
}

int nextSong(){

      //push to Stack
      if(currentSongId != -1){
            pushRecentlyPlayed(currentSongId);
      }

      //Queue has priority

      if (queue.count != 0){
            dequeuePlayNext(&currentSongId);
            return playSong(currentSongId);
      }

      // No queue → use playlist
      currentPlaylistIndex++;

      int nextId = getPlaylistSongAt(currentPlaylist, currentPlaylistIndex);

      if(nextId < 0){
            currentSongId = -1;
            isPlayingFlag = 0;
            currentPlaylistIndex = -1;
            return ERR_EMPTY;
      }

      return playSong(nextId);

}


int setCurrentPlaylist(Playlist *playlist){
    if(playlist == NULL){
        return ERR_INVALID;
    }

    currentPlaylist = playlist;
    currentPlaylistIndex = -1;

    return OK;
}

int previousSong(){
      int prevId;

      int result = popRecentlyPlayed(&prevId);

      if(result != OK){
            return result;
      }

      return playSong(prevId);
}

int getCurrentSong(){
      if(currentSongId == -1){
            return ERR_EMPTY;
      }

      return currentSongId;
}

int isPlaying(){
      return isPlayingFlag;
}