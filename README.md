## PLAYER ARCHITECTURE

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

### MINDMAP

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
