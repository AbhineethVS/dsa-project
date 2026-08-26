# Shared Decisions

Final names and rules both people must follow.  
Do not change these without telling the other person.

Quick daily lookup → **`CHEATSHEET.md`**  
Work split overview → **`SHARED.md`**

---

## 1. Who writes what in Git / main

| Role | Decision |
|------|----------|
| GitHub repo creator | Person 1 creates the repo and adds Person 2 as collaborator |
| First commit on `main` | Docs + shared `models.h` (Song / Album / Artist + status codes) |
| Menu / `main.c` | **Person 2** writes `main.c` and the menu |
| Person 1 branch | `person1-library` |
| Person 2 branch | `person2-player` |

Person 1 provides library lookup/display functions that the menu calls.  
Person 2 owns playlists + playback and wires everything in `main.c`.

---

## 2. Song ID and storage rules

| Decision | Choice |
|----------|--------|
| Song ID type | `int` |
| ID meaning | Unique number, starting from `1` |
| Titles unique? | No — IDs are unique, titles can repeat |
| Stack stores | Song **IDs** (`int`) |
| Queue stores | Song **IDs** (`int`) |
| Playlist linked list stores | Song **IDs** (`int`) |
| Hash table key | Song ID (`int`) primary; also support search by name |
| Duration unit | Integer **seconds** |

---

## 3. Shared models (exact field names)

### Song (Person 1 implements)
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `id` | `int` | Unique song ID |
| `title` | `char title[64]` | Song name |
| `duration` | `int` | Length in seconds |
| `artistName` | `char artistName[64]` | Artist name (for easy display) |
| `albumName` | `char albumName[64]` | Album name (for easy display) |

### Album (Person 1 implements)
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `name` | `char name[64]` | Album name |
| `artistName` | `char artistName[64]` | Artist this album belongs to |
| `songs` | array of `Song` | Songs in this album |
| `songCount` | `int` | How many songs currently in album |

### Artist (Person 1 implements)
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `name` | `char name[64]` | Artist name |
| `albums` | list/array/tree children | Albums under this artist |
| `albumCount` | `int` | How many albums |

### Playlist (Person 2 implements)
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `name` | `char name[64]` | Playlist name |
| `head` | linked list head | Ordered list of song IDs |

### Limits (same for both)
| Limit | Value |
|-------|-------|
| Max name / title length | `64` |
| Max songs per album | `50` |
| Max albums per artist | `20` |
| Max artists in library | `50` |
| Max songs in whole library | `200` |
| Max playlists | `20` |
| Max songs in one playlist | `100` |
| Max play-next queue size | `50` |
| Max recently-played stack size | `50` |

---

## 4. Shared status codes

| Code | Name (optional constant) | Meaning |
|------|--------------------------|---------|
| `0` | `OK` | Success |
| `-1` | `ERR_NOT_FOUND` | Song / artist / album / playlist not found |
| `-2` | `ERR_EMPTY` | Playlist / queue / stack empty |
| `-3` | `ERR_FULL` | Array / queue / stack / album full |
| `-4` | `ERR_DUPLICATE` | Duplicate song ID or duplicate name where not allowed |
| `-5` | `ERR_INVALID` | Bad input (null, bad ID, etc.) |

---

## 5. Shared function names

### Person 1 — Library API

| Function | Purpose |
|----------|---------|
| `addArtist` | Add artist to library tree |
| `addAlbum` | Add album under an artist |
| `addSongToAlbum` | Add song into an album array + register in hash table |
| `removeSong` | Remove song by ID from library structures |
| `removeAlbum` | Remove album under an artist |
| `removeArtist` | Remove artist from library |
| `searchSongById` | Return song details for an ID |
| `searchSongByName` | Find song(s) by title |
| `displayArtists` | Show all artists |
| `displayAlbums` | Show albums (all or under an artist) |
| `displaySongs` | Show songs (library / album) |

### Person 2 — Playlist + Player API

| Function | Purpose |
|----------|---------|
| `createPlaylist` | Create empty playlist |
| `deletePlaylist` | Delete a playlist |
| `addSongToPlaylist` | Append song ID to playlist linked list |
| `removeSongFromPlaylist` | Remove song ID from playlist |
| `reorderSongInPlaylist` | Change song order in playlist |
| `getPlaylistSongAt` | Get song ID at position (0-based) |
| `getPlaylistLength` | Number of songs in playlist |
| `getNextSongInPlaylist` | Given current index, return next song ID |
| `playSong` | Start playing a song ID |
| `pauseSong` | Pause current song |
| `resumeSong` | Resume current song |
| `nextSong` | Go to next (queue first, else playlist) |
| `previousSong` | Go back using recently-played stack |
| `enqueuePlayNext` | Add song ID to play-next queue |
| `dequeuePlayNext` | Remove next song ID from play-next queue |
| `clearPlayNext` | Empty the play-next queue |
| `pushRecentlyPlayed` | Push song ID onto recently-played stack |
| `popRecentlyPlayed` | Pop last played song ID |
| `getCurrentSong` | Return current song ID |
| `isPlaying` | Return whether music is playing |

### Playback state (Person 2 owns)

| Variable | Type idea | Meaning |
|----------|-----------|---------|
| `currentSongId` | `int` | Currently playing song (`-1` if none) |
| `isPlayingFlag` | `int` (`0`/`1`) | Playing or paused |
| `currentPlaylistName` | `char[64]` | Active playlist name (empty if none) |
| `currentPlaylistIndex` | `int` | Position in current playlist |

---

## 6. File names (so folders don’t collide)

| File | Owner | Contains |
|------|-------|----------|
| `models.h` | Shared | Song, Album, Artist structs + status codes |
| `library.h` / `library.c` | Person 1 | Tree, hash, album arrays, library APIs |
| `playlist.h` / `playlist.c` | Person 2 | Playlist linked list APIs |
| `player.h` / `player.c` | Person 2 | Stack, queue, playback APIs |
| `main.c` | Person 2 | Menu + demo wiring |
| `SHARED.md` | Shared | High-level split |
| `DECISIONS.md` | Shared | This file |
| `CHEATSHEET.md` | Shared | Short daily lookup |

Person 1 may split internals (`hash.c`, `tree.c`, etc.) as long as public APIs stay in `library.h`.  
Person 2 may keep playlist + player in fewer files if preferred, as long as names above stay clear.

---

## 7. Next-song rule (final)

When user presses **Next** or a song ends:

1. If play-next queue is **not empty** → play from queue  
2. Else if a playlist is active → Person 2 gets next ID from **their** playlist linked list  
3. Else → stop (`currentSongId = -1`, not playing)

When user presses **Previous**:

1. Person 2 manages recently-played stack
2. Previous pops from stack and plays that ID
3. If stack empty → return `ERR_EMPTY`

Person 1 is only used here to **look up song details** by ID for display.

---

## 8. Sample demo data (same for both)

| ID | Title | Artist | Album | Duration |
|----|-------|--------|-------|----------|
| 1 | Blinding Lights | The Weeknd | After Hours | 200 |
| 2 | Save Your Tears | The Weeknd | After Hours | 215 |
| 3 | Shape of You | Ed Sheeran | Divide | 233 |
| 4 | Perfect | Ed Sheeran | Divide | 263 |
| 5 | Bohemian Rhapsody | Queen | A Night at the Opera | 354 |

Demo playlist name: `Favorites` (created by **Person 2**)  
Songs in playlist order: `1 → 3 → 5 → 2`

---

## 9. Work split reminder

| Person 1 (3 DS) | Person 2 (3 DS) |
|-----------------|-----------------|
| Array | Linked List |
| Tree | Stack |
| Hash Table | Queue |

If both accept this file, start coding on your branches.
