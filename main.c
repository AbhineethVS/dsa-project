#include <stdio.h>
#include <string.h>
#include "library.h"

void makeSong(Song *s, int id, char *title, int duration, char *artist, char *album) {
    s->id = id;
    strcpy(s->title, title);
    s->duration = duration;
    strcpy(s->artistName, artist);
    strcpy(s->albumName, album);
}

void loadSampleSongs(Artist **root) {
    Song s;
    Album *alb;

    addArtist(root, "The Weeknd");
    addArtist(root, "Ed Sheeran");
    addArtist(root, "Queen");

    addAlbum(*root, "The Weeknd", "After Hours");
    addAlbum(*root, "Ed Sheeran", "Divide");
    addAlbum(*root, "Queen", "A Night at the Opera");

    alb = searchAlbum(*root, "The Weeknd", "After Hours");
    makeSong(&s, 1, "Blinding Lights", 200, "The Weeknd", "After Hours");
    addSongToAlbum(alb, s);
    makeSong(&s, 2, "Save Your Tears", 215, "The Weeknd", "After Hours");
    addSongToAlbum(alb, s);

    alb = searchAlbum(*root, "Ed Sheeran", "Divide");
    makeSong(&s, 3, "Shape of You", 233, "Ed Sheeran", "Divide");
    addSongToAlbum(alb, s);
    makeSong(&s, 4, "Perfect", 263, "Ed Sheeran", "Divide");
    addSongToAlbum(alb, s);

    alb = searchAlbum(*root, "Queen", "A Night at the Opera");
    makeSong(&s, 5, "Bohemian Rhapsody", 354, "Queen", "A Night at the Opera");
    addSongToAlbum(alb, s);
}

int main(void) {
    Artist *root = NULL;
    Song *found;

    loadSampleSongs(&root);

    printf("=== Artists ===\n");
    displayArtists(root);

    printf("\n=== Albums ===\n");
    displayAlbums(root, NULL);

    printf("\n=== All Songs ===\n");
    displaySongs(root);

    printf("\n=== Search by ID 3 ===\n");
    found = searchSongById(3);
    if (found != NULL) {
        printf("%d. %s - %s (%d sec)\n", found->id, found->title, found->artistName, found->duration);
    } else {
        printf("not found\n");
    }

    printf("\n=== Search by name Perfect ===\n");
    found = searchSongByName("Perfect");
    if (found != NULL) {
        printf("%d. %s - %s (%d sec)\n", found->id, found->title, found->artistName, found->duration);
    } else {
        printf("not found\n");
    }

    freeLibrary(root);
    return 0;
}
