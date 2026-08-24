# Music Player DSA Project — Shared Contract

Simple agreement so Person 1 and Person 2 can work separately without breaking each other.

---

## Who does what

### Person 1 — Music Library & Playlists

- Array: songs in an album
- Linked List: playlists
- Tree: Artist → Album → Songs
- Hash Table: Song ID / name → Song
- Add / remove / search songs
- Manage artists, albums, playlists

### Person 2 — Music Player & Playback

- Stack: recently played / back
- Queue: play-next queue
- Play / pause / next / previous
- Add / remove songs from play-next
- Playback history
- Automatic next-song handling

### Shared

- Song, Album, Artist models
- Song identity (ID)
- Common function names both sides call
- Error / status codes
- Demo flow

---

## What is SHARED (freeze this first)

Both people must use the **same names and meaning** for these.

### 1. Models

| Model  | Must agree on                      |
| ------ | ---------------------------------- |
| Song   | id, title, duration, link to album |
| Album  | name, songs, link to artist        |
| Artist | name, albums under them            |

Also agree:

- Duration = integer seconds
- Names = fixed-size text (same max length)
- Unique song identity = **Song ID** (not title alone)

### 2. What the player stores

Stack and Queue should store **Song IDs** (or pointers to Song),  
**not** a second copy of full song data.

Person 2 asks Person 1: “give me the song for this ID.”

### 3. Who owns current playback state

| Thing             | Owner    | Notes                         |
| ----------------- | -------- | ----------------------------- |
| currentSong       | Person 2 | Only player changes this      |
| isPlaying / pause | Person 2 | Only player changes this      |
| currentPlaylist   | Person 2 | Player may ask library for it |
| Library / tree    | Person 1 | Player only reads via lookups |

### 4. Function boundary (who owns which verbs)

**Person 1 provides**

- add / remove / search song
- manage artist / album / playlist
- get song by ID
- get song by name
- get songs from a playlist (in order)

**Person 2 provides**

- play / pause
- next / previous
- add / remove play-next
- use recently-played stack
- decide what plays when a song ends

**Important rule for “next song”**

- Person 2 decides playback flow
- If play-next queue has songs → play from queue
- If queue is empty → Person 2 asks Person 1 for the next song in the playlist

### 5. Shared status codes

Use the same return style everywhere, e.g.:

- `0` = success
- `-1` = failed / not found / empty

Common cases both should handle the same way:

- song not found
- playlist empty
- queue empty
- stack empty (nothing to go back to)
- duplicate song ID

### 6. File ownership

| Area                         | Owner               | Shared? |
| ---------------------------- | ------------------- | ------- |
| Song / Album / Artist models | Both                | YES     |
| Array, Tree, Hash, Playlist  | Person 1            | NO      |
| Stack, Queue, Player         | Person 2            | NO      |
| Main menu                    | One person (decide) | YES     |

---

## What is NOT shared

Do **not** edit each other’s internals.

**Person 1 only**

- How album arrays are stored
- How playlist linked list nodes work
- How the artist/album tree is built
- How the hash table is implemented

**Person 2 only**

- How the recently-played stack works
- How the play-next queue works
- Pause / resume logic
- History management details

You only depend on each other’s **public functions**, not private details.

---

## GitHub workflow (how we work together)

Use **one shared GitHub repo**. Do **not** use two repos.

### Branches

| Branch            | Who      | What goes here              |
| ----------------- | -------- | --------------------------- |
| `main`            | Both     | Only finished, merged work  |
| `person1-library` | Person 1 | Library, playlists, tree, hash |
| `person2-player`  | Person 2 | Stack, queue, playback      |

### Rules

1. Create one common repo. Add the other person as collaborator.
2. Put `SHARED.md` + shared models on `main` first.
3. Each person works only on their own branch.
4. Do **not** commit feature work straight to `main`.
5. When a piece is ready, open a **Pull Request (PR)** into `main`.
6. Other person can review lightly, then merge.
7. After merge, both pull latest `main` before continuing.
8. Don’t edit each other’s files. Shared files = discuss first, then one PR.

### Suggested merge timing

- **Mid-way:** once Person 1 has song lookup + playlist ready (Person 2 needs this)
- **End:** final integration + demo

### Bottom line for Git

- One repo
- Two branches
- PRs into `main`
- Merge mid-way + at the end

---

## One meeting checklist (do this before coding)

All of these are now decided in **`DECISIONS.md`**.

- Read `DECISIONS.md` once together
- Use **`CHEATSHEET.md`** every day while coding
- Only change decisions if both agree

---

## Simple demo plan (for final integration)

1. Person 1 builds a small library + one playlist
2. Person 2 plays that playlist
3. User adds a song to play-next
4. Previous uses the recently-played stack
5. Search a song by ID/name (hash table)

If this demo runs, the project is integrated.

---

## Bottom line

- **Shared** = models + IDs + function names + status codes + who owns current song
- **Not shared** = how each data structure is built inside
- Freeze the shared part first, then code in parallel
- **Git** = one repo, two branches (`person1-library`, `person2-player`), PRs into `main`
