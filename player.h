//Song details

void playSong(int id);

void pauseSong();

void resumeSong();

void nextSong();

void previousSong();

int viewCurrentSong();


//PlayNextQueue

void enqueuePlayNext();

void dequeuePlayNext();

void clearPlayNext();

void pushRecentlyPlayed();

int popRecentlyPlayed();

int isPlaying();


int currentSongId = -1;