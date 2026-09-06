#ifndef PLAYLIST_H
#define PLAYLIST_H


typedef struct Playlist Playlist;

Playlist* createPlaylist();

void addSongToPlaylist(Playlist* head, int id);

void deletePlaylist(Playlist* head);

void removeSongFromPlaylist(Playlist* head, int id);


#endif