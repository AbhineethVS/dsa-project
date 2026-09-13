#include <string.h>
#include "sample_data.h"

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
