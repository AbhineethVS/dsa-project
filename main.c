#include <stdio.h>
#include <stdlib.h>

#include "models.h"
#include "library.h"
#include "playlist.h"
#include "player.h"
#include "sample_data.h"


void displayMenu(){

    printf("\n\n========== MUSIC PLAYER ==========\n");

    printf("\n--- Library ---\n");
    printf("1. Display Artists\n");
    printf("2. Display Albums\n");
    printf("3. Display Songs\n");
    printf("4. Search Song by ID\n");
    printf("5. Search Song by Name\n");

    printf("\n--- Playlist ---\n");
    printf("6. Create Playlist\n");
    printf("7. Add Song to Playlist\n");
    printf("8. Remove Song from Playlist\n");
    printf("9. Display Playlist\n");

    printf("\n--- Player ---\n");
    printf("10. Set Current Playlist\n");
    printf("11. Play Song\n");
    printf("12. Pause\n");
    printf("13. Resume\n");
    printf("14. Next Song\n");
    printf("15. Previous Song\n");
    printf("16. Get Current Song\n");
    printf("17. Check Playing Status\n");

    printf("\n--- Play Next Queue ---\n");
    printf("18. Add to Play Next\n");
    printf("19. Clear Play Next Queue\n");

    printf("\n0. Exit\n");

    printf("\nEnter choice: ");
}


int main(){

    Artist *root = NULL;

    /* Load sample songs */
    loadSampleSongs(&root);


    /* Create sample playlist */
    Playlist *favorites = createPlaylist("Favorites");

    addSongToPlaylist(favorites, 1);
    addSongToPlaylist(favorites, 3);
    addSongToPlaylist(favorites, 5);
    addSongToPlaylist(favorites, 2);


    /* User-created playlist */
    Playlist *userPlaylist = NULL;


    int choice;

    do{

        displayMenu();
        scanf("%d", &choice);


        switch(choice){

            /* =====================================
                         LIBRARY
            ===================================== */

            case 1:

                displayArtists(root);

                break;


            case 2:{

                char artistName[64];

                printf("Enter Artist Name: ");
                scanf(" %63[^\n]", artistName);

                displayAlbums(root, artistName);

                break;
            }


            case 3:

                displaySongs(root);

                break;


            case 4:{

                int id;

                printf("Enter Song ID: ");
                scanf("%d", &id);

                Song *song = searchSongById(id);

                if(song == NULL){

                    printf("Song not found.\n");

                }
                else{

                    printf("\nID       : %d", song->id);
                    printf("\nTitle    : %s", song->title);
                    printf("\nArtist   : %s", song->artistName);
                    printf("\nAlbum    : %s", song->albumName);
                    printf("\nDuration : %d seconds\n", song->duration);

                }

                break;
            }


            case 5:{

                char title[64];

                printf("Enter Song Name: ");
                scanf(" %63[^\n]", title);

                Song *song = searchSongByName(title);

                if(song == NULL){

                    printf("Song not found.\n");

                }
                else{

                    printf("\nID       : %d", song->id);
                    printf("\nTitle    : %s", song->title);
                    printf("\nArtist   : %s", song->artistName);
                    printf("\nAlbum    : %s", song->albumName);
                    printf("\nDuration : %d seconds\n", song->duration);

                }

                break;
            }


            /* =====================================
                         PLAYLIST
            ===================================== */

            case 6:{

                char name[64];

                printf("Enter Playlist Name: ");
                scanf(" %63[^\n]", name);

                userPlaylist = createPlaylist(name);

                if(userPlaylist == NULL){

                    printf("Failed to create playlist.\n");

                }
                else{

                    printf("Playlist created successfully.\n");

                }

                break;
            }


            case 7:{

                int id;

                if(userPlaylist == NULL){

                    printf("Create a playlist first.\n");
                    break;

                }

                printf("Enter Song ID: ");
                scanf("%d", &id);

                int result = addSongToPlaylist(userPlaylist, id);

                if(result == OK){

                    printf("Song added to playlist.\n");

                }
                else{

                    printf("Could not add song. Error: %d\n", result);

                }

                break;
            }


            case 8:{

                int id;

                if(userPlaylist == NULL){

                    printf("Create a playlist first.\n");
                    break;

                }

                printf("Enter Song ID to remove: ");
                scanf("%d", &id);

                int result = removeSongFromPlaylist(userPlaylist, id);

                if(result == OK){

                    printf("Song removed from playlist.\n");

                }
                else{

                    printf("Could not remove song. Error: %d\n", result);

                }

                break;
            }


            case 9:{

                if(userPlaylist == NULL){

                    printf("No user playlist exists.\n");

                }
                else{

                    displayPlaylist(userPlaylist);

                }

                break;
            }


            /* =====================================
                         PLAYER
            ===================================== */

            case 10:{

                int playlistChoice;

                printf("\n1. Favorites\n");
                printf("2. User Playlist\n");

                printf("Choose Playlist: ");
                scanf("%d", &playlistChoice);


                if(playlistChoice == 1){

                    int result = setCurrentPlaylist(favorites);

                    if(result == OK){

                        printf("Favorites selected.\n");

                    }

                }
                else if(playlistChoice == 2){

                    if(userPlaylist == NULL){

                        printf("Create a playlist first.\n");

                    }
                    else{

                        int result = setCurrentPlaylist(userPlaylist);

                        if(result == OK){

                            printf("User playlist selected.\n");

                        }

                    }

                }
                else{

                    printf("Invalid choice.\n");

                }

                break;
            }


            case 11:{

                int id;

                printf("Enter Song ID to play: ");
                scanf("%d", &id);

                int result = playSong(id);

                if(result != OK){

                    printf("Could not play song. Error: %d\n", result);

                }

                break;
            }


            case 12:{

                int result = pauseSong();

                if(result != OK){

                    printf("Could not pause song.\n");

                }

                break;
            }


            case 13:{

                int result = resumeSong();

                if(result != OK){

                    printf("Could not resume song. Error: %d\n", result);

                }

                break;
            }


            case 14:{

                int result = nextSong();

                if(result != OK){

                    printf("\nNo next song. Error: %d\n", result);

                }

                break;
            }


            case 15:{

                int result = previousSong();

                if(result != OK){

                    printf("\nNo previous song. Error: %d\n", result);

                }

                break;
            }


            case 16:{

                int id = getCurrentSong();

                if(id < 0){

                    printf("No song is currently selected.\n");

                }
                else{

                    printf("Current Song ID: %d\n", id);

                }

                break;
            }


            case 17:{

                if(isPlaying()){

                    printf("A song is currently playing.\n");

                }
                else{

                    printf("No song is currently playing.\n");

                }

                break;
            }


            /* =====================================
                       PLAY NEXT QUEUE
            ===================================== */

            case 18:{

                int id;

                printf("Enter Song ID to add to Play Next: ");
                scanf("%d", &id);

                int result = enqueuePlayNext(id);

                if(result == OK){

                    printf("Song added to Play Next queue.\n");

                }
                else{

                    printf("Could not add song. Error: %d\n", result);

                }

                break;
            }


            case 19:{

                clearPlayNext();

                printf("Play Next queue cleared.\n");

                break;
            }


            /* =====================================
                         EXIT
            ===================================== */

            case 0:

                printf("\nExiting Music Player...\n");

                break;


            default:

                printf("\nInvalid choice.\n");

        }

    } while(choice != 0);


    /* Free playlists */
    deletePlaylist(favorites);

    if(userPlaylist != NULL){

        deletePlaylist(userPlaylist);

    }


    /* Free library */
    freeLibrary(root);


    return 0;
}