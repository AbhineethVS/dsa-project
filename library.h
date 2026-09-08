#ifndef LIBRARY_H
#define LIBRARY_H

#include "models.h"

int addSongToAlbum(Album *a, Song s);
int removeSongFromAlbum(Album *a, int songId);
void displayAlbumSongs(Album *a);

int addArtist(Artist **root, char *name);
Artist *searchArtist(Artist *root, char *name);
int addAlbum(Artist *root, char *artistName, char *albumName);
Album *searchAlbum(Artist *root, char *artistName, char *albumName);
int removeAlbum(Artist *root, char *artistName, char *albumName);
int removeArtist(Artist **root, char *name);
int removeSong(Artist *root, int songId);

Song *searchSongById(int id);
Song *searchSongByName(char *title);

void displayArtists(Artist *root);
void displayAlbums(Artist *root, char *artistName);
void displaySongs(Artist *root);

void freeHash(void);
void freeLibrary(Artist *root);

#endif
