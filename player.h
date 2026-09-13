//HistoryStack

int pushRecentlyPlayed(int id);

int popRecentlyPlayed(int *id);


//PlayNextQueue

int enqueuePlayNext(int id);

int dequeuePlayNext(int *id);

int clearPlayNext();


//Player

int playSong(int id);

int pauseSong();

int resumeSong();

int nextSong();

int previousSong();

int getCurrentSong();

int isPlaying();