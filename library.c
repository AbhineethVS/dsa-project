#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

typedef struct HashNode {
    Song data;
    struct HashNode *next;
} HashNode;

HashNode *songHash[HASH_SIZE];
int songTotal = 0;

int hashId(int id) {
    if (id < 0) {
        id = -id;
    }
    return id % HASH_SIZE;
}

int hashInsert(Song s) {
    HashNode *n;
    int i;

    if (s.id < 1) {
        return ERR_INVALID;
    }
    if (songTotal >= MAX_SONGS) {
        return ERR_FULL;
    }
    if (searchSongById(s.id) != NULL) {
        return ERR_DUPLICATE;
    }

    i = hashId(s.id);
    n = (HashNode *)malloc(sizeof(HashNode));
    if (n == NULL) {
        return ERR_INVALID;
    }
    n->data = s;
    n->next = songHash[i];
    songHash[i] = n;
    songTotal = songTotal + 1;
    return OK;
}

int hashDelete(int id) {
    HashNode *cur;
    HashNode *prev;
    int i;

    i = hashId(id);
    cur = songHash[i];
    prev = NULL;

    while (cur != NULL) {
        if (cur->data.id == id) {
            if (prev == NULL) {
                songHash[i] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            songTotal = songTotal - 1;
            return OK;
        }
        prev = cur;
        cur = cur->next;
    }
    return ERR_NOT_FOUND;
}

Song *searchSongById(int id) {
    HashNode *cur;
    int i;

    if (id < 1) {
        return NULL;
    }

    i = hashId(id);
    cur = songHash[i];
    while (cur != NULL) {
        if (cur->data.id == id) {
            return &cur->data;
        }
        cur = cur->next;
    }
    return NULL;
}

Song *searchSongByName(char *title) {
    HashNode *cur;
    int i;

    if (title == NULL) {
        return NULL;
    }

    for (i = 0; i < HASH_SIZE; i++) {
        cur = songHash[i];
        while (cur != NULL) {
            if (strcmp(cur->data.title, title) == 0) {
                return &cur->data;
            }
            cur = cur->next;
        }
    }
    return NULL;
}

void freeHash(void) {
    HashNode *cur;
    HashNode *tmp;
    int i;

    for (i = 0; i < HASH_SIZE; i++) {
        cur = songHash[i];
        while (cur != NULL) {
            tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        songHash[i] = NULL;
    }
    songTotal = 0;
}

int addSongToAlbum(Album *a, Song s) {
    int i;
    int r;

    if (a == NULL) {
        return ERR_INVALID;
    }
    if (a->songCount >= MAX_SONGS_PER_ALBUM) {
        return ERR_FULL;
    }

    for (i = 0; i < a->songCount; i++) {
        if (a->songs[i].id == s.id) {
            return ERR_DUPLICATE;
        }
    }

    r = hashInsert(s);
    if (r != OK) {
        return r;
    }

    a->songs[a->songCount] = s;
    a->songCount = a->songCount + 1;
    return OK;
}

int removeSongFromAlbum(Album *a, int songId) {
    int i, j;
    int found = 0;

    if (a == NULL) {
        return ERR_INVALID;
    }

    for (i = 0; i < a->songCount; i++) {
        if (a->songs[i].id == songId) {
            found = 1;
            for (j = i; j < a->songCount - 1; j++) {
                a->songs[j] = a->songs[j + 1];
            }
            a->songCount = a->songCount - 1;
            break;
        }
    }

    if (found == 0) {
        return ERR_NOT_FOUND;
    }

    hashDelete(songId);
    return OK;
}

void displayAlbumSongs(Album *a) {
    int i;

    if (a == NULL) {
        return;
    }

    printf("Album: %s\n", a->name);
    if (a->songCount == 0) {
        printf("no songs\n");
        return;
    }

    for (i = 0; i < a->songCount; i++) {
        printf("%d. %s (%d sec)\n", a->songs[i].id, a->songs[i].title, a->songs[i].duration);
    }
}

int addArtist(Artist **root, char *name) {
    Artist *n;
    int cmp;

    if (root == NULL || name == NULL) {
        return ERR_INVALID;
    }

    if (*root == NULL) {
        n = (Artist *)malloc(sizeof(Artist));
        if (n == NULL) {
            return ERR_INVALID;
        }
        strcpy(n->name, name);
        n->albumCount = 0;
        n->left = NULL;
        n->right = NULL;
        *root = n;
        return OK;
    }

    cmp = strcmp(name, (*root)->name);
    if (cmp == 0) {
        return ERR_DUPLICATE;
    }
    if (cmp < 0) {
        return addArtist(&((*root)->left), name);
    }
    return addArtist(&((*root)->right), name);
}

Artist *searchArtist(Artist *root, char *name) {
    int cmp;

    if (root == NULL || name == NULL) {
        return NULL;
    }

    cmp = strcmp(name, root->name);
    if (cmp == 0) {
        return root;
    }
    if (cmp < 0) {
        return searchArtist(root->left, name);
    }
    return searchArtist(root->right, name);
}

int addAlbum(Artist *root, char *artistName, char *albumName) {
    Artist *a;
    int i;

    if (artistName == NULL || albumName == NULL) {
        return ERR_INVALID;
    }

    a = searchArtist(root, artistName);
    if (a == NULL) {
        return ERR_NOT_FOUND;
    }
    if (a->albumCount >= MAX_ALBUMS_PER_ARTIST) {
        return ERR_FULL;
    }

    for (i = 0; i < a->albumCount; i++) {
        if (strcmp(a->albums[i].name, albumName) == 0) {
            return ERR_DUPLICATE;
        }
    }

    strcpy(a->albums[a->albumCount].name, albumName);
    strcpy(a->albums[a->albumCount].artistName, artistName);
    a->albums[a->albumCount].songCount = 0;
    a->albumCount = a->albumCount + 1;
    return OK;
}

Album *searchAlbum(Artist *root, char *artistName, char *albumName) {
    Artist *a;
    int i;

    a = searchArtist(root, artistName);
    if (a == NULL) {
        return NULL;
    }

    for (i = 0; i < a->albumCount; i++) {
        if (strcmp(a->albums[i].name, albumName) == 0) {
            return &a->albums[i];
        }
    }
    return NULL;
}

void clearAlbumSongsFromHash(Album *alb) {
    int i;
    if (alb == NULL) {
        return;
    }
    for (i = 0; i < alb->songCount; i++) {
        hashDelete(alb->songs[i].id);
    }
    alb->songCount = 0;
}

int removeAlbum(Artist *root, char *artistName, char *albumName) {
    Artist *a;
    int i, j;
    int found = 0;

    a = searchArtist(root, artistName);
    if (a == NULL) {
        return ERR_NOT_FOUND;
    }

    for (i = 0; i < a->albumCount; i++) {
        if (strcmp(a->albums[i].name, albumName) == 0) {
            found = 1;
            clearAlbumSongsFromHash(&a->albums[i]);
            for (j = i; j < a->albumCount - 1; j++) {
                a->albums[j] = a->albums[j + 1];
            }
            a->albumCount = a->albumCount - 1;
            break;
        }
    }

    if (found == 0) {
        return ERR_NOT_FOUND;
    }
    return OK;
}

int removeSong(Artist *root, int songId) {
    Song *s;
    Album *alb;
    int r;

    s = searchSongById(songId);
    if (s == NULL) {
        return ERR_NOT_FOUND;
    }

    alb = searchAlbum(root, s->artistName, s->albumName);
    if (alb == NULL) {
        hashDelete(songId);
        return ERR_NOT_FOUND;
    }

    r = removeSongFromAlbum(alb, songId);
    return r;
}

Artist *minArtistNode(Artist *n) {
    while (n != NULL && n->left != NULL) {
        n = n->left;
    }
    return n;
}

void clearArtistAlbumsFromHash(Artist *a) {
    int i;
    if (a == NULL) {
        return;
    }
    for (i = 0; i < a->albumCount; i++) {
        clearAlbumSongsFromHash(&a->albums[i]);
    }
    a->albumCount = 0;
}

int removeArtist(Artist **root, char *name) {
    Artist *temp;
    int cmp;

    if (root == NULL || *root == NULL || name == NULL) {
        return ERR_NOT_FOUND;
    }

    cmp = strcmp(name, (*root)->name);

    if (cmp < 0) {
        return removeArtist(&((*root)->left), name);
    }
    if (cmp > 0) {
        return removeArtist(&((*root)->right), name);
    }

    clearArtistAlbumsFromHash(*root);

    if ((*root)->left == NULL) {
        temp = *root;
        *root = (*root)->right;
        free(temp);
        return OK;
    }
    if ((*root)->right == NULL) {
        temp = *root;
        *root = (*root)->left;
        free(temp);
        return OK;
    }

    temp = minArtistNode((*root)->right);
    strcpy((*root)->name, temp->name);
    (*root)->albumCount = temp->albumCount;
    memcpy((*root)->albums, temp->albums, sizeof(Album) * MAX_ALBUMS_PER_ARTIST);
    temp->albumCount = 0;
    return removeArtist(&((*root)->right), temp->name);
}

void displayArtists(Artist *root) {
    if (root == NULL) {
        return;
    }
    displayArtists(root->left);
    printf("%s\n", root->name);
    displayArtists(root->right);
}

void displayAlbums(Artist *root, char *artistName) {
    Artist *a;
    int i;

    if (artistName == NULL) {
        if (root == NULL) {
            return;
        }
        displayAlbums(root->left, NULL);
        printf("Artist: %s\n", root->name);
        if (root->albumCount == 0) {
            printf("  no albums\n");
        }
        for (i = 0; i < root->albumCount; i++) {
            printf("  %s\n", root->albums[i].name);
        }
        displayAlbums(root->right, NULL);
        return;
    }

    a = searchArtist(root, artistName);
    if (a == NULL) {
        printf("artist not found\n");
        return;
    }

    printf("Artist: %s\n", a->name);
    if (a->albumCount == 0) {
        printf("  no albums\n");
        return;
    }
    for (i = 0; i < a->albumCount; i++) {
        printf("  %s\n", a->albums[i].name);
    }
}

void displaySongs(Artist *root) {
    int i, j;

    if (root == NULL) {
        return;
    }

    displaySongs(root->left);

    for (i = 0; i < root->albumCount; i++) {
        printf("[%s - %s]\n", root->name, root->albums[i].name);
        if (root->albums[i].songCount == 0) {
            printf("  no songs\n");
        }
        for (j = 0; j < root->albums[i].songCount; j++) {
            printf("  %d. %s (%d sec)\n",
                   root->albums[i].songs[j].id,
                   root->albums[i].songs[j].title,
                   root->albums[i].songs[j].duration);
        }
    }

    displaySongs(root->right);
}

void freeArtistTree(Artist *root) {
    if (root == NULL) {
        return;
    }
    freeArtistTree(root->left);
    freeArtistTree(root->right);
    free(root);
}

void freeLibrary(Artist *root) {
    freeArtistTree(root);
    freeHash();
}
