#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct Song Song;



void playSong();

void pauseSong();

void resumeSong();

void nextSong();

void previousSong();

int viewCurrentSong();

void enqueuePlayNext();

void dequeuePlayNext();

void clearPlayNext();

void pushRecentlyPlayed();

int popRecentlyPlayed();

int isPlaying();

#endif