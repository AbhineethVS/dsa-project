#include "playlist.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//internal implementation of Playlist using Song nodes

typedef struct songNode{
    int id;
    struct songNode* nextSong;
} songNode;

struct Playlist{
    char playlistName[64];
    songNode* head;
    int length;
};

// PlayList Functions

Playlist* createPlaylist(char* playlistName){
    Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));

    if(playlist == NULL){
        return NULL;    //malloc allocation failed
    }
    
    playlist->head = NULL; //NULL pointer
    strcpy(playlist->playlistName, playlistName);
    playlist->length = 0;

    return playlist;
}

int addSongToPlaylist(Playlist* playlist, int id){

    if (playlist == NULL){
        return ERR_INVALID;
    }

    if(playlist->length >= 100){    // Max playlist length taken to be 100
        printf("Playlist is full...");
        return ERR_FULL;
    }

    songNode* newSong = (songNode*)malloc(sizeof(songNode));

    if(newSong == NULL){
        return ERR_INVALID; // FIX MALLOC RETURN ERROR CODE
    }


    newSong -> id = id;
    newSong -> nextSong = NULL;

    if(playlist->head == NULL){
        playlist->head = newSong;
    }
    else{
        songNode* temp = playlist->head;
        while(temp -> nextSong != NULL){
            temp = temp -> nextSong;
        }
        temp -> nextSong = newSong;
    }

    (playlist -> length)++;

    return OK;
}

int removeSongFromPlaylist(Playlist* playlist, int id){

    if(playlist == NULL){
        return ERR_INVALID;
    }

    songNode* temp = playlist->head;

    if(temp == NULL){
        printf("\nPlaylist empty...\n");
        return ERR_EMPTY;
    } 

    //if head is to be deleted!! 
    //since the code that follows deletes a node that has a previous node, not the first node...

    if(playlist->head->id == id){
        songNode* toFree = playlist->head;
        playlist->head = (playlist->head) ->nextSong; //preserve links if any
        free(toFree);
        (playlist -> length)--;
        return OK;
    }

    //traverse till the Song node before the one to delete

    while((temp -> nextSong != NULL) && (temp -> nextSong -> id != id)){
        //FUN FACT: Have to give the NULL check first as '&&' evaluates operators left to right 
        //so if head points to NULL then the second condition is an invalid reference!!!
        //"Short-Circuit Evaluation"

        temp = temp -> nextSong;
    }


    //if reached last node then song not in playlist

    if(temp-> nextSong == NULL){
        printf("\nSong not found...\n");
        return ERR_NOT_FOUND;
    }
    songNode* temp2 = temp -> nextSong; //assign the nextSong of temp (which is what we want to delete) to temp2

    temp->nextSong = temp2->nextSong; //remove the song from the link

    free(temp2); //free memory of the song

    (playlist -> length)--;

    return OK;
}

int removeSongFromPlaylist(Playlist* playlist, int id){
    
    Song* temp = (*head) -> nextSong;
    free(*head);
    Song* temp2;
    while(temp -> nextSong != NULL){
        temp2 = temp->nextSong;
        free(temp);
    }
    free(temp2);
}
