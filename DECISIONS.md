# Shared Decisions

Final names and rules both people must follow.  
Do not change these without telling the other person.

Quick daily lookup → **`CHEATSHEET.md`**

---

## 1. Who writes what in Git / main

| Role | Decision |
|------|----------|
| GitHub repo creator | Person 1 creates the repo and adds Person 2 as collaborator |
| First commit on `main` | `SHARED.md`, this file, and shared model headers |
| Menu / `main.c` | **Person 2** writes `main.c` and the menu (player needs to drive the demo) |
| Person 1 branch | `person1-library` |
| Person 2 branch | `person2-player` |

Person 1 still provides library functions that the menu calls.

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

Use these exact struct / field names in C.

### Song
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `id` | `int` | Unique song ID |
| `title` | `char title[64]` | Song name |
| `duration` | `int` | Length in seconds |
| `artistName` | `char artistName[64]` | Artist name (for easy display) |
| `albumName` | `char albumName[64]` | Album name (for easy display) |

### Album
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `name` | `char name[64]` | Album name |
| `artistName` | `char artistName[64]` | Artist this album belongs to |
| `songs` | array of `Song` | Songs in this album |
| `songCount` | `int` | How many songs currently in album |

### Artist
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `name` | `char name[64]` | Artist name |
| `albums` | list/array/tree children | Albums under this artist |
| `albumCount` | `int` | How many albums |

### Playlist
| Field | Type idea | Meaning |
|-------|-----------|---------|
| `name` | `char name[64]` | Playlist name |
| `head` | linked list head | Ordered list of song IDs |

### Limits (same for both)
| Limit | Value |
|-------|-------|
| Max name / title length | `64` characters (including null terminator space as you implement) |
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

Use these exact return values everywhere:

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

These are the public names both sides rely on.  
Implement them in your own files, but keep the names the same.

### Person 1 — Library API

| Function | Purpose |
|----------|---------|
| `addArtist` | Add artist to library tree |
| `addAlbum` | Add album under an artist |
| `addSongToAlbum` | Add song into an album array + register in hash table |
| `removeSong` | Remove song by ID from library structures |
| `searchSongById` | Return song details for an ID |
| `searchSongByName` | Find song(s) by title |
| `createPlaylist` | Create empty playlist |
| `addSongToPlaylist` | Append song ID to playlist linked list |
| `removeSongFromPlaylist` | Remove song ID from playlist |
| `getPlaylistSongAt` | Get song ID at position in playlist (0-based) |
| `getPlaylistLength` | Number of songs in playlist |
| `getNextSongInPlaylist` | Given current index, return next song ID |

### Person 2 — Player API

| Function | Purpose |
|----------|---------|
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

### Shared playback state (Person 2 owns)

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
| `models.h` | Shared | Song, Album, Artist, Playlist structs + status codes |
| `library.h` / `library.c` | Person 1 | Tree, hash, album arrays, playlist LL, library APIs |
| `player.h` / `player.c` | Person 2 | Stack, queue, playback APIs |
| `main.c` | Person 2 | Menu + demo wiring |
| `SHARED.md` | Shared | High-level split |
| `DECISIONS.md` | Shared | This file |
| `CHEATSHEET.md` | Shared | Short daily lookup |

Person 1 may split internals into more files if needed (`playlist.c`, `hash.c`, etc.), as long as public APIs stay in `library.h`.  
Person 2 may split (`stack.c`, `queue.c`), as long as public APIs stay in `player.h`.

---

## 7. Next-song rule (final)

When user presses **Next** or a song ends:

1. If play-next queue is **not empty** → play from queue  
2. Else if a playlist is active → ask library for next playlist song  
3. Else → stop (`currentSongId = -1`, not playing)

When user presses **Previous**:

1. Push current song to recently-played only when leaving it via next/auto-next (Person 2 handles this)
2. Previous pops from recently-played stack and plays that ID
3. If stack empty → return `ERR_EMPTY`

---

## 8. Sample demo data (same for both)

Use these so integration testing matches:

| ID | Title | Artist | Album | Duration |
|----|-------|--------|-------|----------|
| 1 | Blinding Lights | The Weeknd | After Hours | 200 |
| 2 | Save Your Tears | The Weeknd | After Hours | 215 |
| 3 | Shape of You | Ed Sheeran | Divide | 233 |
| 4 | Perfect | Ed Sheeran | Divide | 263 |
| 5 | Bohemian Rhapsody | Queen | A Night at the Opera | 354 |

Demo playlist name: `Favorites`  
Songs in playlist order: `1 → 3 → 5 → 2`

---

## 9. Quick freeze checklist

Already decided in this file:

- [x] Model field names
- [x] Song ID format (`int`, from 1)
- [x] Stack / queue store IDs
- [x] Shared function names
- [x] Who owns `currentSongId` (Person 2)
- [x] Status codes
- [x] Who writes `main` (Person 2)
- [x] Who creates GitHub repo (Person 1)
- [x] File names
- [x] Sample demo data

If both accept this file, start coding on your branches.
