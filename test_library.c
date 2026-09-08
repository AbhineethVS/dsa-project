#include <stdio.h>
#include <string.h>
#include "library.h"

Song makeSong(int id, char *title, int dur, char *artist, char *album) {
    Song s;
    s.id = id;
    strcpy(s.title, title);
    s.duration = dur;
    strcpy(s.artistName, artist);
    strcpy(s.albumName, album);
    return s;
}

int main() {
    Artist *root = NULL;
    Album *alb;
    Song *found;
    int r;

    addArtist(&root, "The Weeknd");
    addArtist(&root, "Ed Sheeran");
    addArtist(&root, "Queen");

    addAlbum(root, "The Weeknd", "After Hours");
    addAlbum(root, "Ed Sheeran", "Divide");
    addAlbum(root, "Queen", "A Night at the Opera");

    alb = searchAlbum(root, "The Weeknd", "After Hours");
    addSongToAlbum(alb, makeSong(1, "Blinding Lights", 200, "The Weeknd", "After Hours"));
    addSongToAlbum(alb, makeSong(2, "Save Your Tears", 215, "The Weeknd", "After Hours"));

    alb = searchAlbum(root, "Ed Sheeran", "Divide");
    addSongToAlbum(alb, makeSong(3, "Shape of You", 233, "Ed Sheeran", "Divide"));
    addSongToAlbum(alb, makeSong(4, "Perfect", 263, "Ed Sheeran", "Divide"));

    alb = searchAlbum(root, "Queen", "A Night at the Opera");
    addSongToAlbum(alb, makeSong(5, "Bohemian Rhapsody", 354, "Queen", "A Night at the Opera"));

    r = addSongToAlbum(alb, makeSong(5, "dupe", 10, "Queen", "A Night at the Opera"));
    printf("dupe id add: %d\n", r);

    found = searchSongById(1);
    if (found != NULL) {
        printf("by id 1: %s\n", found->title);
    } else {
        printf("by id 1: not found\n");
    }

    found = searchSongById(99);
    if (found == NULL) {
        printf("by id 99: not found\n");
    }

    found = searchSongByName("Perfect");
    if (found != NULL) {
        printf("by name Perfect: id %d\n", found->id);
    }

    found = searchSongByName("No Song");
    if (found == NULL) {
        printf("by name No Song: not found\n");
    }

    printf("\n--- all songs ---\n");
    displaySongs(root);

    r = removeSong(root, 2);
    printf("\nremove song 2: %d\n", r);
    found = searchSongById(2);
    if (found == NULL) {
        printf("id 2 after remove: not found\n");
    }

    printf("\n--- final ---\n");
    displayArtists(root);
    displaySongs(root);

    freeLibrary(root);
    return 0;
}
