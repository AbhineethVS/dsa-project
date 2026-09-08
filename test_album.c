#include <stdio.h>
#include <string.h>
#include "library.h"

int main() {
    Album a;
    Song s1, s2, s3;
    int r;

    strcpy(a.name, "After Hours");
    strcpy(a.artistName, "The Weeknd");
    a.songCount = 0;

    s1.id = 1;
    strcpy(s1.title, "Blinding Lights");
    s1.duration = 200;
    strcpy(s1.artistName, "The Weeknd");
    strcpy(s1.albumName, "After Hours");

    s2.id = 2;
    strcpy(s2.title, "Save Your Tears");
    s2.duration = 215;
    strcpy(s2.artistName, "The Weeknd");
    strcpy(s2.albumName, "After Hours");

    s3.id = 1;
    strcpy(s3.title, "fake dupe");
    s3.duration = 100;
    strcpy(s3.artistName, "x");
    strcpy(s3.albumName, "x");

    r = addSongToAlbum(&a, s1);
    printf("add 1: %d\n", r);
    r = addSongToAlbum(&a, s2);
    printf("add 2: %d\n", r);
    r = addSongToAlbum(&a, s3);
    printf("add dupe: %d\n", r);

    displayAlbumSongs(&a);

    r = removeSongFromAlbum(&a, 1);
    printf("remove 1: %d\n", r);
    displayAlbumSongs(&a);

    r = removeSongFromAlbum(&a, 99);
    printf("remove missing: %d\n", r);

    return 0;
}
