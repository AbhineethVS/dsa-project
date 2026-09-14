#ifndef PLAYLIST_H
#define PLAYLIST_H


typedef struct Playlist Playlist;

Playlist* createPlaylist(char* playlistName);

int addSongToPlaylist(Playlist* playlist, int id);

int deletePlaylist(Playlist* playlist);

int removeSongFromPlaylist(Playlist* playlist, int id);

int getPlaylistLength(Playlist* playlist);

int getNextSongInPlaylist(Playlist* playlist, int index);

int getPlaylistSongAt(Playlist* playlist, int index);

void displayPlaylist(Playlist* playlist);

#endif