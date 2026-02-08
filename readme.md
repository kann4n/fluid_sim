## compile

### main.c
```bash
gcc main.c -o main -lSDL3
```

### random_walk.c
```bash
gcc random_walk.c -o random_walk -lSDL3
```
```bash
./random_walk <num_of_agent> (optional)
```

### compile space_sim.c
```bash
gcc .\space_sim.c -o space_sim -l SDL3 -lSDL3_image
```

## screenshot
![main](/imgs/fluid-v1.png)
![walk](/imgs/random-walk-v1.png)
![space](/imgs/space-sim-v0.1.png)
