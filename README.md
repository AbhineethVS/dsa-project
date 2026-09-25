# Music Player (C / DSA)

A menu-driven console music player that simulates playback (no real audio). It demonstrates six data structures: **array** (songs per album), **binary search tree** (artists), **hash table** (lookup by song ID), **linked list** (playlists), **stack** (recently played / Previous), and **queue** (Play Next).

For setup and team workflow, see `START_HERE.md`. Shared names, limits, and APIs are in `CONTRACT.md`.

## Build and run

```bash
gcc -Wall -o music_player main.c library.c playlist.c player.c sample_data.c
./music_player
```

Optional library-only smoke test:

```bash
gcc -Wall -o test_library test_library.c library.c sample_data.c
./test_library
```

## Sample output

### Library test (`test_library`)

```text
=== Artists ===
Ed Sheeran
Queen
The Weeknd

=== Albums ===
Artist: Ed Sheeran
  Divide
Artist: Queen
  A Night at the Opera
Artist: The Weeknd
  After Hours

=== All Songs ===
[Ed Sheeran - Divide]
  3. Shape of You (233 sec)
  4. Perfect (263 sec)
[Queen - A Night at the Opera]
  5. Bohemian Rhapsody (354 sec)
[The Weeknd - After Hours]
  1. Blinding Lights (200 sec)
  2. Save Your Tears (215 sec)

=== Search by ID 3 ===
3. Shape of You - Ed Sheeran (233 sec)

=== Search by name Perfect ===
4. Perfect - Ed Sheeran (263 sec)
```

### Interactive player (excerpt)

After choosing menu options (e.g. set **Favorites**, play song `1`, queue song `4`, then **Next**):

```text
Choose Playlist: Favorites selected.
Enter Song ID to play:
Playing : Blinding Lights
Enter Song ID to add to Play Next: Song added to Play Next queue.

Playing : Perfect
Playing : Blinding Lights
```

The full menu lists library, playlist, player, and Play Next actions (options `0`–`19`).

## Repository files

| File | What it does |
|------|----------------|
| `models.h` | Shared `Song`, `Album`, and `Artist` types, capacity limits, and status codes (`OK`, `ERR_*`). |
| `library.h` / `library.c` | Music library: artist tree, album arrays, song hash table, search/display, and cleanup. |
| `playlist.h` / `playlist.c` | Playlist linked lists: create/delete, add/remove song IDs, display. |
| `player.h` / `player.c` | Playback: play/pause/resume, Next (queue then playlist), Previous (stack), Play Next queue. |
| `main.c` | Interactive menu; wires library, playlists, and player together. |
| `sample_data.h` / `sample_data.c` | Loads the five demo songs from `CONTRACT.md` into the library at startup. |
| `test_library.c` | Standalone program that loads sample data and prints artists, albums, songs, and searches. |
| `START_HERE.md` | Beginner guide, Person 1 / Person 2 checklists, Git workflow, and final demo script. |
| `CONTRACT.md` | Shared contract: field names, limits, public functions, playback rules, sample IDs. |
| `.gitignore` | Ignores build artifacts (`music_player`, `*.exe`). |

---

## Player architecture

```text
              PLAYER
                 │
       ┌─────────┴─────────┐
       ↓                   ↓
 PLAY-NEXT QUEUE       ACTIVE PLAYLIST
       │                   │
       │ priority          │ fallback
       └─────────┬─────────┘
                 ↓
             SONG TO PLAY
```

### Next-song flow

```text
                    NEXT
                      │
                      ▼
              Is queue non-empty?
                 /          \
               YES           NO
                │             │
          dequeue queue    Check playlist
                │             │
                ▼             ▼
             PLAY IT     Is there another song?
                           /          \
                         YES           NO
                          │             │
                     PLAY IT          STOP
```
