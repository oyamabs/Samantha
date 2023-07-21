
# Samantha Trainer

Trainer for Call of Duty Black Ops Zombies.


## Badges
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

## Tech Stack

**Language:** C++

**Trainer type:** Internal

**Interface:** CLI, HTTP API


## Roadmap

- Add more basic trainer features

- Add a GUI with DirectX

- ~~Add an web API because why not~~

- ~~Make my own DLL injector~~

- Write the documentation for the web API


## Web API

The api can be accessed through the `1337` port. A small documentation can be accessed with the `/` endpoint.

### Endpoints

`/` - Shows a small documentation

`/setGodMode` - Set/unset the god mode cheat

`/setUnlimitedAmmos` - Set/unset unlimited ammo cheat

`/setUnlimitedPoints` - Set/unset unlimited points cheat

`/setNoclip` - Set/unset the no clip cheat

`/setPoints/:points` - Set points value for player (for example `/setPoints/1337` will set your points to 1337)


