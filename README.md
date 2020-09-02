# Pong Clone

A clone of the classic Pong Game written in C++ with SDL2

## Requirements

SDL2 installed

## Running

A `run.sh` script is included as part of this repo to handle building, running, and removing the binary.  You may use it by first setting its execute bit and then running the script:
```
sudo chmod +x run.sh
./run.sh
```

Alternatively, you may use the `Makefile` to generate the binary and run it yourself:
```
make all
./pong
```