#include "playlist.h"

#include<stdlib.h>
#include<stdio.h>

struct Song{
    int id;
    struct Song* nextSong;
};

Song* createPlaylist(){
    Song* head = NULL; //NULL pointer
    return head;
}

void playSong(int id){
    printf("Currently playing %d",id);
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

void removeSongFromPlaylist(int id, Song** head){
    Song* temp = *head;
    if(temp == NULL){
        printf("\nPlaylist empty...\n");
        return;
    } 

    //if head is to be deleted!! 
    //since the code that follows deletes a node that has a previous node, not the first node...
    //we need to modify the head pointer in this case, hence passing pointer to the pointer as function parameter

    if((*head)->id == id){  //NOTE: -> has higher precedence the * so need to put brackets
        Song* toFree = *head;
        *head = (*head) ->nextSong; //preserve links if any
        free(toFree);
        return;
    }

    //traverse till the Song node before the one to delete

    while((temp -> nextSong != NULL) && (temp -> nextSong -> id != id)){
        //FUN FACT: Have to give the NULL check first as '&&' is left associative 
        //so if head points to NULL then the second condition is an invalid reference!!!
        //"Short Circuit Evaluation"
        
        temp = temp -> nextSong;
    }


    //if reached last node then song not in playlist

    if(temp-> nextSong == NULL){
        printf("\nSong not found...\n");
        return;
    }
    Song* temp2 = temp -> nextSong; //assign the nextSong of temp (which is what we want to delete) to temp2

    temp->nextSong = temp2->nextSong; //remove the song from the link

    free(temp2); //free memory of the song

    return;
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

