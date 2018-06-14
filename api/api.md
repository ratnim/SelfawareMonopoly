
# Server Routes
```
/
/lobby
/game
```

## overview
Route: /

### Enter lobby:
expects:

    {
        "request" : "enter_lobby"
        "data" :
        {
            "player_name": <player_name>
        }
    }
returns:

    {
        "name" : "enter_lobby"
        "data" :
        {
            "session": <session>
        }
    }

Client should redirect to ```/lobby?session=<session>```

Some kind of overview page. Shows highscore, register and login players.

### login
A session key is generated and it is stored locally inside the URL as get parameter `?session=@@@@@@@`.

## lobby
__Route:__ /lobby

__Sends frequently:__

    {
        "name" : "game_list",
        "data" :
        {
            games :
            [
                {
                    "game_id" : <game_id>,
                    "game_label" : <label of the game>
                    "player_list" : [],
                    "game_status" : <game_status>
                }
            ]
        }
    }

__Requests:__
### Create a game:
expects:

    {
        "request" : "create_game",
        "data" :
        {
            "game_label" : "<label_of_the_game>"
        }
    }
returns:

    {
        "name" : "create_game"
        "data" :
        {
            "game_id": <game_id>
        }
    }

Client should redirect to ```/game?game_id=<game_id>&session=<session>```

## Game
__Route:__ /game

__Incoming Events:__
```
    {
        "name" : "possible_actions",
        "data" :
        {
            names : [{name : <name>}]
        }
    }
```
```
    {
        "name" : "error",
        "data" :
        {
            "id" : <id>,
            "message" : <message>
        }
    }
```
```
    {
        "name" : "player_move",
        "data" :
        {
            player_name : <player_name>,
            distance : <distance>
        }
    }
```
```
    {
        "name" : "end_game"
    }
```

__Requests:__
### Join Game
Expects:

    {
        "request" : "join_game"
    }

Returns:

    {
        "name" : "join_game",
        "data" :
        {
            player_name : <player_name>
        }
    }
### Ready
Expects:

    {
        "request" : "player_ready",
    }

Returns:

    {
        "name" : "player_ready",
        "data" :
        {
            player_name : <player_name>
        }
    }

### Start a game:
Expects:

    {
        "request" : "game_start",
    }

Returns:

    {
        "name" : "game_start"
    }

### End turn:
Expects:

    {
        "request" : "end_turn",
    }

Returns:

    {
        "name" : "change_turn",
        "data" :
        {
            player_name : <player_name>
        }
    }

### Roll dice:
Expects:

    {
        "request" : "roll_dice",
    }

Returns:

    {
        "name" : "roll_dice",
        "data" :
        {
            eyes : [<eye1>, <eye2>]
        }
    }
