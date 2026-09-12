#ifndef MODELS_H
#define MODELS_H

#define OK 0
#define ERR_NOT_FOUND -1
#define ERR_EMPTY -2
#define ERR_FULL -3
#define ERR_DUPLICATE -4
#define ERR_INVALID -5

#define MAX_NAME 64
#define MAX_SONGS_PER_ALBUM 50
#define MAX_ALBUMS_PER_ARTIST 20
#define MAX_ARTISTS 50
#define MAX_SONGS 200
#define HASH_SIZE 101

typedef struct Song {
    int id;
    char title[MAX_NAME];
    int duration;
    char artistName[MAX_NAME];
    char albumName[MAX_NAME];
} Song;

typedef struct Album {
    char name[MAX_NAME];
    char artistName[MAX_NAME];
    Song songs[MAX_SONGS_PER_ALBUM];
    int songCount;
} Album;

typedef struct Artist {
    char name[MAX_NAME];
    Album albums[MAX_ALBUMS_PER_ARTIST];
    int albumCount;
    struct Artist *left;
    struct Artist *right;
} Artist;

#endif
