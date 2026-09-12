#ifndef PLAYLIST_H
#define PLAYLIST_H


typedef struct Playlist Playlist;

Playlist* createPlaylist();

int addSongToPlaylist(Playlist* playlist, int id);

int deletePlaylist(Playlist* playlist);

int removeSongFromPlaylist(Playlist* playlist, int id);


#endif