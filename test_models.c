#include <stdio.h>
#include <string.h>
#include "models.h"

int main() {
    Song s;
    s.id = 1;
    strcpy(s.title, "Blinding Lights");
    s.duration = 200;
    strcpy(s.artistName, "The Weeknd");
    strcpy(s.albumName, "After Hours");

    printf("id: %d\n", s.id);
    printf("title: %s\n", s.title);
    printf("duration: %d\n", s.duration);
    printf("artist: %s\n", s.artistName);
    printf("album: %s\n", s.albumName);

    return 0;
}
