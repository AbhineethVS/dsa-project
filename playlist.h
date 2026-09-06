#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct Song Song;

Song* createPlaylist();

void addSongToPlaylist(int id, Song** head);

void deletePlaylist(Song** head);

void removeSongFromPlaylist(int id, Song** head);


#endif