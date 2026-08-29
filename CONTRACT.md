# Shared Contract

This file contains the small set of technical decisions that both people must
follow. It is not a task list. For step-by-step work, use `START_HERE.md`.

Do not change a shared name or rule without telling your teammate. Each person
is free to design the private internals of their own files.

---

## 1. Ownership

### Person 1 owns

- `Song`, `Album`, and `Artist`
- Album song arrays
- Artist/album tree
- Song hash table
- Library add, remove, search, and display operations

### Person 2 owns

- Playlist linked lists
- Recently-played stack
- Play-next queue
- Player state and playback behavior
- `main.c` and the menu

### The shared boundary

Person 2 stores song IDs and calls Person 1's `searchSongById` when complete
song information is needed.

Do not directly read or modify the other person's private data structures.

---

## 2. Song identity and text

| Rule | Agreed value |
|---|---|
| Song ID type | `int` |
| First valid song ID | `1` |
| Are IDs unique? | Yes |
| Must titles be unique? | No |
| Duration unit | Whole seconds |
| Maximum text length | `64` characters including storage for `'\0'` |
| No current song | `currentSongId = -1` |

Playlists, queues, and stacks store an `int` song ID. They do not store or copy
the complete `Song`.

---

## 3. Shared model fields

These field names must remain consistent.

### `Song` — Person 1 implements

| Field | C type | Meaning |
|---|---|---|
| `id` | `int` | Unique song ID |
| `title` | `char[64]` | Song title |
| `duration` | `int` | Duration in seconds |
| `artistName` | `char[64]` | Artist name for display |
| `albumName` | `char[64]` | Album name for display |

### `Album` — Person 1 implements

| Field | Type | Meaning |
|---|---|---|
| `name` | `char[64]` | Album name |
| `artistName` | `char[64]` | Artist who owns the album |
| `songs` | Array of `Song` | Songs in this album |
| `songCount` | `int` | Number of songs currently stored |

### `Artist` — Person 1 implements

| Field | Type | Meaning |
|---|---|---|
| `name` | `char[64]` | Artist name |
| `albums` | Tree children, list, or array | Albums belonging to the artist |
| `albumCount` | `int` | Number of albums |

### `Playlist` — Person 2 implements

| Field | Type | Meaning |
|---|---|---|
| `name` | `char[64]` | Playlist name |
| `head` | Linked-list head | First node containing a song ID |

The internal tree and linked-list node fields are private. Only the public
behavior and the shared fields above must match.

---

## 4. Capacity limits

| Item | Maximum |
|---|---:|
| Artists in the library | 50 |
| Albums per artist | 20 |
| Songs per album | 50 |
| Songs in the complete library | 200 |
| Playlists | 20 |
| Songs in one playlist | 100 |
| Play-next queue entries | 50 |
| Recently-played stack entries | 50 |

Return `ERR_FULL` when a fixed-capacity structure cannot accept another item.

---

## 5. Status codes

Use the same meaning throughout the project:

| Value | Suggested constant | Meaning |
|---:|---|---|
| `0` | `OK` | Operation succeeded |
| `-1` | `ERR_NOT_FOUND` | Requested item does not exist |
| `-2` | `ERR_EMPTY` | Playlist, queue, or stack is empty |
| `-3` | `ERR_FULL` | Fixed-capacity structure is full |
| `-4` | `ERR_DUPLICATE` | An ID or unique name already exists |
| `-5` | `ERR_INVALID` | Invalid ID, pointer, position, or input |

If a function returns a pointer, a null pointer can represent “not found.”
Document that choice in its header. Do not mix different meanings for the same
return value.

---

## 6. Public function names

The `.h` files are the source of truth for exact C parameter and return types.
If a prototype is changed after sharing the header, tell the other person.

### Person 1 — declared in `library.h`

| Function | Required behavior |
|---|---|
| `addArtist` | Add an artist to the library |
| `addAlbum` | Add an album under an artist |
| `addSongToAlbum` | Add a song to the album array and hash table |
| `removeSong` | Remove a song using its ID |
| `removeAlbum` | Remove an album from an artist |
| `removeArtist` | Remove an artist |
| `searchSongById` | Find and return song information for an ID |
| `searchSongByName` | Find song information using a title |
| `displayArtists` | Print artists |
| `displayAlbums` | Print albums |
| `displaySongs` | Print songs |

`searchSongById` is the first integration dependency and should be completed
early.

### Person 2 — declared in `playlist.h`

| Function | Required behavior |
|---|---|
| `createPlaylist` | Create an empty playlist |
| `deletePlaylist` | Delete a playlist and free its nodes |
| `addSongToPlaylist` | Append a song ID |
| `removeSongFromPlaylist` | Remove a song ID |
| `reorderSongInPlaylist` | Move a song to another position |
| `getPlaylistSongAt` | Get the ID at a zero-based position |
| `getPlaylistLength` | Return the number of song IDs |
| `getNextSongInPlaylist` | Return the ID after the current position |

### Person 2 — declared in `player.h`

| Function | Required behavior |
|---|---|
| `playSong` | Start playing a song ID |
| `pauseSong` | Pause without changing the current ID |
| `resumeSong` | Resume the paused song |
| `nextSong` | Select from the queue, then the active playlist |
| `previousSong` | Select from recently-played history |
| `enqueuePlayNext` | Add an ID to the end of the queue |
| `dequeuePlayNext` | Remove the oldest queued ID |
| `clearPlayNext` | Empty the queue |
| `pushRecentlyPlayed` | Push an ID onto history |
| `popRecentlyPlayed` | Pop the newest history ID |
| `getCurrentSong` | Return the current song ID |
| `isPlaying` | Return `1` when playing and `0` otherwise |

---

## 7. Player state

Person 2 owns and changes this state:

| State | Type | Meaning |
|---|---|---|
| `currentSongId` | `int` | Current song, or `-1` when none |
| `isPlayingFlag` | `int` | `1` for playing and `0` for paused/stopped |
| `currentPlaylistName` | `char[64]` | Active playlist, or empty text |
| `currentPlaylistIndex` | `int` | Current zero-based playlist position |

These do not need to be global variables. Person 2 may place them inside a
player structure as long as the behavior remains the same.

---

## 8. Next and Previous behavior

When the user chooses **Next**, or when a song is treated as finished:

1. If the play-next queue is not empty, dequeue and play its first ID.
2. Otherwise, if an active playlist has another song, play that ID.
3. Otherwise, stop and set `currentSongId` to `-1`.

Before changing away from a currently playing song, push its ID onto the
recently-played stack.

When the user chooses **Previous**:

1. Pop the latest ID from the recently-played stack.
2. Play that ID.
3. Return `ERR_EMPTY` if the stack has no IDs.

Person 1 does not decide playback order. Person 1 only resolves an ID into song
information for display.

---

## 9. File agreement

| File | Owner | Purpose |
|---|---|---|
| `models.h` | Person 1, shared interface | Models and status codes |
| `library.h` / `library.c` | Person 1 | Array, tree, hash table, library |
| `playlist.h` / `playlist.c` | Person 2 | Playlist linked lists |
| `player.h` / `player.c` | Person 2 | Stack, queue, and playback |
| `main.c` | Person 2 | Menu and complete demonstration |

Extra private `.c` and `.h` files are allowed. Public functionality must still
be available through the agreed headers.

---

## 10. Shared sample data

Use these values for integration and the final demonstration:

| ID | Title | Artist | Album | Seconds |
|---:|---|---|---|---:|
| 1 | Blinding Lights | The Weeknd | After Hours | 200 |
| 2 | Save Your Tears | The Weeknd | After Hours | 215 |
| 3 | Shape of You | Ed Sheeran | Divide | 233 |
| 4 | Perfect | Ed Sheeran | Divide | 263 |
| 5 | Bohemian Rhapsody | Queen | A Night at the Opera | 354 |

Demo playlist:

- Name: `Favorites`
- Song ID order: `1 -> 3 -> 5 -> 2`

Both people should use these IDs while testing so integration is predictable.

---

## 11. Before changing this contract

Ask:

1. Will this rename a field or public function?
2. Will this change a status code, ID, or playback rule?
3. Has the other person already written code that depends on it?

If any answer is yes, agree on the change first and update the public header and
this document together.
