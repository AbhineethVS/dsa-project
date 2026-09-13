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
