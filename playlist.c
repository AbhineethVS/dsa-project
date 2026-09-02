#include <playlist.h>

#include<stdlib.h>

typedef struct Song{
    int id;
    struct Song* nextSong;
} Song;

Song* createPlaylist(){
    Song* head = NULL;
    return head;
}

void addSongToPlaylist(int id, Song** head){
    Song* newSong = (Song*)malloc(sizeof(Song));

    newSong -> id = id;
    newSong -> nextSong = NULL;

    if(*head == NULL){
        *head = newSong;
    }
    else{
        Song* temp = *head;
        while(temp -> nextSong != NULL){
            temp = temp -> nextSong;
        }
        temp -> nextSong = newSong;
    }
}


void deletePlaylist(Song** head){
    Song* temp = (*head) -> nextSong;
    free(*head);
    Song* temp2;
    while(temp -> nextSong != NULL){
        temp2 = temp->nextSong;
        free(temp);
    }
    free(temp2);
}

