#include <stdio.h>
#include "sample_data.h"

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
