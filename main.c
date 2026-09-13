#include "playlist.h"
#include "sample_data.h"

#include <stdio.h>
#include <stdlib.h>

int main(){

    Artist *root = NULL;

    loadSampleSongs(&root);

    playSong(2);

}