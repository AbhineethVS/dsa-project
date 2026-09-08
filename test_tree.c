#include <stdio.h>
#include <string.h>
#include "library.h"

int main() {
    Artist *root = NULL;
    Album *alb;
    Song s1, s2, s3, s4;
    int r;

    r = addArtist(&root, "The Weeknd");
    printf("add artist weeknd: %d\n", r);
    r = addArtist(&root, "Ed Sheeran");
    printf("add artist ed: %d\n", r);
    r = addArtist(&root, "Queen");
    printf("add artist queen: %d\n", r);
    r = addArtist(&root, "The Weeknd");
    printf("add dupe artist: %d\n", r);

    r = addAlbum(root, "The Weeknd", "After Hours");
    printf("add album after hours: %d\n", r);
    r = addAlbum(root, "Ed Sheeran", "Divide");
    printf("add album divide: %d\n", r);
    r = addAlbum(root, "Queen", "A Night at the Opera");
    printf("add album opera: %d\n", r);
    r = addAlbum(root, "Nobody", "X");
    printf("add album missing artist: %d\n", r);

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

    s3.id = 3;
    strcpy(s3.title, "Shape of You");
    s3.duration = 233;
    strcpy(s3.artistName, "Ed Sheeran");
    strcpy(s3.albumName, "Divide");

    s4.id = 4;
    strcpy(s4.title, "Perfect");
    s4.duration = 263;
    strcpy(s4.artistName, "Ed Sheeran");
    strcpy(s4.albumName, "Divide");

    alb = searchAlbum(root, "The Weeknd", "After Hours");
    if (alb != NULL) {
        addSongToAlbum(alb, s1);
        addSongToAlbum(alb, s2);
    }

    alb = searchAlbum(root, "Ed Sheeran", "Divide");
    if (alb != NULL) {
        addSongToAlbum(alb, s3);
        addSongToAlbum(alb, s4);
    }

    printf("\n--- artists ---\n");
    displayArtists(root);

    printf("\n--- albums ---\n");
    displayAlbums(root, NULL);

    printf("\n--- songs ---\n");
    displaySongs(root);

    r = removeSongFromAlbum(searchAlbum(root, "The Weeknd", "After Hours"), 1);
    printf("\nremove song 1: %d\n", r);

    r = removeAlbum(root, "Queen", "A Night at the Opera");
    printf("remove queen album: %d\n", r);

    printf("\n--- after removes ---\n");
    displaySongs(root);

    freeLibrary(root);
    return 0;
}
