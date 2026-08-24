# Cheatsheet

Daily lookup while coding.  
Full rules → `DECISIONS.md` · Project split → `SHARED.md`

| Doc | Use for |
|-----|---------|
| `CHEATSHEET.md` | Quick names (this file) |
| `DECISIONS.md` | Exact shared decisions |
| `SHARED.md` | Who does what + Git workflow |

**Person 1:** library / playlists / tree / hash  
**Person 2:** player / stack / queue / `main.c`

---

## Core rules
- Song ID = `int` (starts at 1)
- Stack / Queue / Playlist store **IDs**, not full songs
- No song → `currentSongId = -1`
- Strings max length = 64
- Next song: queue → playlist → stop
- Previous song: recently-played stack

## Status codes
| Code | Meaning |
|------|---------|
| `0` | OK |
| `-1` | not found |
| `-2` | empty |
| `-3` | full |
| `-4` | duplicate |
| `-5` | invalid |

## Song fields
`id` · `title` · `duration` · `artistName` · `albumName`

## Album fields
`name` · `artistName` · `songs` · `songCount`

## Artist fields
`name` · `albums` · `albumCount`

## Playlist fields
`name` · `head` (linked list of song IDs)

## Files
| File | Who |
|------|-----|
| `models.h` | Shared |
| `library.h` / `library.c` | Person 1 |
| `player.h` / `player.c` | Person 2 |
| `main.c` | Person 2 |

## Branches
`main` · `person1-library` · `person2-player`

---

## Person 1 functions
`addArtist` · `addAlbum` · `addSongToAlbum` · `removeSong`  
`searchSongById` · `searchSongByName`  
`createPlaylist` · `addSongToPlaylist` · `removeSongFromPlaylist`  
`getPlaylistSongAt` · `getPlaylistLength` · `getNextSongInPlaylist`

## Person 2 functions
`playSong` · `pauseSong` · `resumeSong` · `nextSong` · `previousSong`  
`enqueuePlayNext` · `dequeuePlayNext` · `clearPlayNext`  
`pushRecentlyPlayed` · `popRecentlyPlayed`  
`getCurrentSong` · `isPlaying`

## Person 2 state
`currentSongId` · `isPlayingFlag` · `currentPlaylistName` · `currentPlaylistIndex`

## Next song order
1. play-next queue  
2. else playlist  
3. else stop

## Demo data
| ID | Song |
|----|------|
| 1 | Blinding Lights |
| 2 | Save Your Tears |
| 3 | Shape of You |
| 4 | Perfect |
| 5 | Bohemian Rhapsody |

Playlist `Favorites`: `1 → 3 → 5 → 2`
