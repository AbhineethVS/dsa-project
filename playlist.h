#ifndef PLAYLIST_H
#define PLAYLIST_H

//NOTE: IF DEFINED IN "MODELS.H" THEN REMOVE BELOW PREPROCESSOR DIRECTIVES

#define OK 0
#define ERR_NOT_FOUND -1
#define ERR_EMPTY -2
#define ERR_FULL -3
#define ERR_DUPLICATE -4
#define ERR_INVALID -5

typedef struct Playlist Playlist;

Playlist* createPlaylist();

int addSongToPlaylist(Playlist* head, int id);

void deletePlaylist(Playlist* head);

void removeSongFromPlaylist(Playlist* head, int id);


#endif