# Start Here

This is a beginner-friendly guide for the Music Player DSA project.

Do not try to understand the whole project at once. Find your role below, complete
one step at a time, and test each step before moving on.

Need an exact shared name, limit, or rule? Open `CONTRACT.md`.

---

## 1. What are we building?

A menu-based music player in C that demonstrates six data structures:

- **Person 1:** Array, Tree, and Hash Table
- **Person 2:** Linked List, Stack, and Queue

This is a simulation. It stores song information and prints what is playing; it
does not need to play real audio.

---

## 2. The five rules both people must remember

1. Every song has a unique integer ID starting from `1`.
2. Playlists, the play-next queue, and history store only song IDs.
3. Person 1 owns song details and the music library.
4. Person 2 owns playlists, playback, the queue, and history.
5. Person 2 gets song details from Person 1 using `searchSongById`.

Example: a playlist stores `1 -> 3 -> 5`, not three complete `Song` objects.

---

## 3. Which files do I work on?

### Person 1 — Music library

Work on branch `person1-library`.

Your files:

- `models.h`
- `library.h`
- `library.c`
- Optional private files such as `tree.c` or `hash.c`

Do not implement playlists or the player.

### Person 2 — Playlist and player

Work on branch `person2-player`.

Your files:

- `playlist.h`
- `playlist.c`
- `player.h`
- `player.c`
- `main.c`

Do not implement the library, tree, or hash table.

---

## 4. Person 1 checklist

Complete these in order.

### Step 1 — Define the shared models

- [ ] Create `models.h`.
- [ ] Add `Song`, `Album`, and `Artist` using the fields in `CONTRACT.md`.
- [ ] Add the shared status codes.
- [ ] Check that a small test program can include `models.h` and compile.

### Step 2 — Implement the album array

- [ ] Store songs in an album using an array.
- [ ] Add a song.
- [ ] Remove a song.
- [ ] Display the songs in an album.
- [ ] Test full-array, duplicate, and not-found cases.

### Step 3 — Implement the artist tree

- [ ] Insert artists and albums.
- [ ] Search for an artist or album.
- [ ] Traverse the tree to display data.
- [ ] Test with at least two artists and two albums.

### Step 4 — Implement the song hash table

- [ ] Insert a song using its ID.
- [ ] Search for a song using its ID.
- [ ] Search for songs using a title.
- [ ] Delete a song.
- [ ] Test both found and not-found searches.

### Step 5 — Finish the public library functions

- [ ] Put the public declarations in `library.h`.
- [ ] Make `searchSongById` work first because Person 2 needs it.
- [ ] Test all add, remove, search, and display operations.
- [ ] Commit and open a PR when the library compiles.

### Person 1 is finished when

- The array, tree, and hash table are visibly used.
- `searchSongById` returns the correct song for a valid ID.
- Invalid IDs return the agreed error result.
- The sample songs from `CONTRACT.md` can be displayed.

---

## 5. Person 2 checklist

Complete these in order. You can build and test using song IDs even before
Person 1's library is ready.

### Step 1 — Implement playlist linked lists

- [ ] Create and delete a playlist.
- [ ] Add a song ID to the end.
- [ ] Remove a song ID.
- [ ] Reorder song IDs.
- [ ] Display IDs temporarily, for example `1 -> 3 -> 5`.

### Step 2 — Implement the recently-played stack

- [ ] Push the current song ID before changing songs.
- [ ] Pop an ID when the user chooses Previous.
- [ ] Return the empty error when there is no history.

### Step 3 — Implement the play-next queue

- [ ] Enqueue a song ID.
- [ ] Dequeue the oldest song ID.
- [ ] Clear the queue.
- [ ] Test empty and full cases.

### Step 4 — Implement player behavior

- [ ] Play, pause, and resume.
- [ ] Implement Next: queue first, playlist second, otherwise stop.
- [ ] Implement Previous using the stack.
- [ ] Use `-1` when no song is selected.

### Step 5 — Build the menu

- [ ] Put the menu in `main.c`.
- [ ] Call Person 1's public functions instead of accessing library internals.
- [ ] Replace temporary ID-only output with `searchSongById` after integration.
- [ ] Run the complete demo listed below.

### Person 2 is finished when

- The linked list, stack, and queue are visibly used.
- Playlist order is correct after adding, removing, and reordering.
- Next always checks the queue before the playlist.
- Previous works using history.
- The menu demonstrates both people's features.

---

## 6. How to work with Git

### Save normal progress on your branch

```powershell
git status
git add <files-you-changed>
git commit -m "Describe the completed feature"
git push
```

Replace `<files-you-changed>` with actual filenames. Avoid changing the other
person's files.

### Bring new changes from `main` into your branch

First commit your current work. Then run:

```powershell
git switch main
git pull origin main
git switch person1-library
git merge main
```

Person 2 uses `git switch person2-player` instead.

If Git reports a conflict, stop and discuss it together instead of deleting
either person's code.

---

## 7. Integration order

1. Person 1 gets `models.h`, `library.h`, and `searchSongById` working.
2. Person 1 opens a PR and merges that working part into `main`.
3. Person 2 merges the latest `main` into `person2-player`.
4. Person 2 includes `library.h` and uses `searchSongById` for display.
5. Both branches are merged into `main`.
6. Compile and run the final demo together.

Person 2 does not need to wait while Person 1 codes. Playlist, stack, queue, and
most player behavior can be tested using IDs alone.

---

## 8. Final demo

Use this as the minimum presentation:

1. Display the music library.
2. Search for a song by ID and by name.
3. Create playlist `Favorites` with IDs `1 -> 3 -> 5 -> 2`.
4. Start playing the playlist.
5. Add another song to the play-next queue.
6. Press Next and show that the queued song plays first.
7. Press Previous and show that the stack restores the earlier song.

If these actions work and you can explain where all six data structures are
used, the project is ready for its basic demonstration.

---

## 9. Where should I look when confused?

- **What should I do next?** Read your checklist in this file.
- **What exact name or value should I use?** Read `CONTRACT.md`.
- **How does my teammate's private code work?** You do not need to know.
- **Can I rename a shared field or function?** Discuss it before changing it.
- **Can I test before integration?** Yes. Use sample song IDs.
