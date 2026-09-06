#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct Song Song;



void playSong(int id);

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

void addSongToPlaylist(int id, Song** head);

void deletePlaylist(Song** head);

void removeSongFromPlaylist(int id, Song** head);

int currentSongId = -1;

#endif