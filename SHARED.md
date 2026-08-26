# Music Player DSA Project — Shared Contract

Simple agreement so Person 1 and Person 2 can work separately without breaking each other.

---

## Who does what

### Person 1 — Music Library & Song Management

**Data structures**
- Array → songs within an album
- Tree → Artist → Album → Songs
- Hash Table → Song ID / name → Song

**Responsibilities**
- Song, Album, Artist structures
- Music library
- Add / remove songs
- Add / remove artists and albums
- Search songs by ID / name
- Display albums / artists / songs
- Array ops for album songs
- Tree insertion / traversal / search
- Hash-table insertion / search / deletion

### Person 2 — Playlists & Music Player

**Data structures**
- Linked List → playlist
- Stack → recently played / back
- Queue → play-next queue

**Responsibilities**
- Playlist structure
- MusicPlayer / playback state
- Create / delete playlists
- Add / remove / reorder songs in playlists
- Play a song
- Next / previous (back)
- Add / remove songs from play-next queue
- Recently played history
- Automatic next-song selection
- Coordinate playlist + queue + stack

### Shared

- Song, Album, Artist field names (same in both codebases)
- Song identity (ID)
- Status codes
- How Person 2 looks up a song from Person 1 (`searchSongById`)
- Demo flow
- Git workflow

---

## What is SHARED (freeze this first)

Both people must use the **same names and meaning** for these.

### 1. Models

| Model | Must agree on | Owner of implementation |
|-------|---------------|-------------------------|
| Song / Album / Artist fields | Same field names | Person 1 |
| Playlist fields | Same field names | Person 2 |

Also agree:
- Duration = integer seconds
- Names = fixed-size text (same max length)
- Unique song identity = **Song ID** (not title alone)

### 2. What playlists / player store

Linked list, stack, and queue store **Song IDs** (`int`),  
**not** full copies of song data.

Person 2 asks Person 1: “give me the song for this ID” via `searchSongById`.

### 3. Who owns what state

| Thing | Owner | Notes |
|-------|-------|-------|
| Library / tree / hash / album arrays | Person 1 | Person 2 only reads via lookup APIs |
| Playlists (linked lists) | Person 2 | Fully owned by Person 2 |
| `currentSongId` / playing flag | Person 2 | Only player changes these |
| Play-next queue | Person 2 | |
| Recently-played stack | Person 2 | |

### 4. Function boundary

**Person 1 provides**
- add / remove artist, album, song
- search song by ID / name
- display artists / albums / songs

**Person 2 provides**
- create / delete playlist
- add / remove / reorder playlist songs
- play / pause / next / previous
- play-next queue ops
- recently-played stack ops
- decide what plays when a song ends

**Important rule for “next song”**
- Person 2 decides playback flow alone
- If play-next queue has songs → play from queue
- If queue is empty → Person 2 uses **their own** playlist linked list for the next song
- Person 1 is only needed to resolve song ID → song details for display

### 5. Shared status codes

Same return style everywhere (see `DECISIONS.md`):
- `0` = success
- negative = error (not found / empty / full / duplicate / invalid)

### 6. File ownership

| Area | Owner | Shared? |
|------|-------|---------|
| Song / Album / Artist models | Person 1 (fields agreed) | YES (names) |
| Array, Tree, Hash, library | Person 1 | NO |
| Playlist linked list | Person 2 | NO |
| Stack, Queue, Player | Person 2 | NO |
| Main menu / `main.c` | Person 2 | YES (wires both) |

---

## What is NOT shared

Do **not** edit each other’s internals.

**Person 1 only**
- How album arrays are stored
- How the artist/album tree is built
- How the hash table is implemented
- Display formatting for library contents

**Person 2 only**
- How playlist linked list nodes work
- How the recently-played stack works
- How the play-next queue works
- Pause / resume / next-song coordination

You only depend on each other’s **public functions**, not private details.

---

## GitHub workflow (how we work together)

Use **one shared GitHub repo**. Do **not** use two repos.

### Branches

| Branch | Who | What goes here |
|--------|-----|----------------|
| `main` | Both | Only finished, merged work |
| `person1-library` | Person 1 | Array, tree, hash, library APIs |
| `person2-player` | Person 2 | Playlist LL, stack, queue, player, `main.c` |

### Rules

1. Create one common repo. Add the other person as collaborator.
2. Put shared docs + `models.h` on `main` first.
3. Each person works only on their own branch.
4. Do **not** commit feature work straight to `main`.
5. When a piece is ready, open a **Pull Request (PR)** into `main`.
6. Other person can review lightly, then merge.
7. After merge, both pull latest `main` before continuing.
8. Don’t edit each other’s files. Shared files = discuss first, then one PR.

### Suggested merge timing

- **Mid-way:** once Person 1 has `searchSongById` working (Person 2 needs this for display / play info)
- **End:** final integration + demo

### Bottom line for Git

- One repo
- Two branches
- PRs into `main`
- Merge mid-way + at the end

---

## Docs to use

| Doc | Use for |
|-----|---------|
| `SHARED.md` | Who does what + Git (this file) |
| `DECISIONS.md` | Exact names, APIs, sample data |
| `CHEATSHEET.md` | Daily quick lookup while coding |

---

## Simple demo plan (for final integration)

1. Person 1 builds a small library (artists / albums / songs)
2. Person 2 creates playlist `Favorites` and plays it
3. User adds a song to play-next
4. Previous uses the recently-played stack
5. Search a song by ID/name (Person 1 hash table)

If this demo runs, the project is integrated.

---

## Bottom line

- **Person 1** = library (array + tree + hash)
- **Person 2** = playlists + player (linked list + stack + queue)
- **Shared** = Song/Album/Artist field names + IDs + status codes + lookup API
- **Git** = one repo, two branches, PRs into `main`
