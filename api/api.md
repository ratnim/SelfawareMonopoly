
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
        "request" : "enter_lobby",
        "data" :
        {
            "player_name": <player_name>
        }
    }
returns:

    {
        "name" : "enter_lobby",
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
                    "game_label" : <label of the game>,
                    "player_list" : [],
                    "game_status" : <initialized | started | finished>
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
        "name" : "create_game",
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
        "name" : "possible_requests",
        "data" :
        {
            requests : [{request:<request>, data: {}}]
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
Where id is:
    EXPECT_EQ(Error::NoError, 0);
    EXPECT_EQ(Error::InvalidRoute, 1);
    EXPECT_EQ(Error::UnsupportedAction, 2);
    EXPECT_EQ(Error::MalformedRequest, 3);
    EXPECT_EQ(Error::InvalidRequest, 4);
    EXPECT_EQ(Error::InternalError, 5);
    EXPECT_EQ(Error::InsufficientMoney, 6);
    EXPECT_EQ(Error::InsufficientCoins, 7);

```
    {
        "name" : "money_change",
        "data" :
        {
            player: <name>,
            deposit: <new_value>
        }
    }
```
```
{
    "name" : "property_change",
    "data" :
    {
        index: <index>,
        owner: <player_name>,
        construction_level: <level>
    }
}
```
```
    {
        "name" : "player_move",
        "data" :
        {
            player_name : <player_name>,
            type : <forward | backward | jump>
            target : <field_index>
        }
    }
```
```
    {
        "name" : "end_game"
    }
```

__Requests:__

### Game Board
Expects: 

    {
        "request" : "game_board"
    }

Returns:

    {
        "name" : "game_board",
        "data" : {
            fields : 
            [
                {
                    name : <field_name>,
                    type : < start | street | station | event_card | society_card | jail | free | go_to_jail | tax | utility >,
                    group : < 0 | 1 | ... | 9 >,
                    price : <price>,
                    house_price : <price>,
                    rent : [ <base_rent>, <one_house_rent>, ..., <hotel_rent> ]
                },
                ...
            ]
        } 
    }

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
        "request" : "player_ready"
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
        "request" : "game_start"
    }

Returns:

    {
        "name" : "game_start"
    }

### End turn:
Expects:

    {
        "request" : "end_turn"
    }

Returns:

    {
        "name" : "change_turn",
        "data" :
        {
            player_name : <player_name>
        }
    }

### Roll dices:
Expects:

    {
        "request" : "roll_dice"
    }

Returns:

    {
        "name" : "roll_dice",
        "data" :
        {
            player_name : <player_name>,
            eyes : [<eye1>, <eye2>]
        }
    }

### Don't buy a Street

Possible Request:
```
    {
        "request" : "dont_buy_field",
    }
```

### Buy a Street

Possible Request:
```
    {
        "request" : "buy_field",
    }
```

Returns:

on success:
```
{
    "name" : "property_change",
    "data" :
    {
        index: <index>,
        owner: <player_name>,
        construction_level: <level>
    }
}
```

or

on failure:
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

### Pay a Debt
Possible Request:

```
{
    "request" : pay_debt,
    "data": { 
        "amount": <amount>,
        "beneficiary" : <name>
    } 
}
```

Possible Request:

```
{
    "request" : file_bankruptcy
}
```

Request:

```
{
    "request" : pay_debt,
    "data": {
        "beneficiary": <name>
    } 
}
```

Returns:

on success:
```
    {
        "name" : "money_change",
        "data" :
        {
            player: <name>,
            deposit: <new_value>
        }
    }
```

or

on failure:
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

### Build Houses

Possible Request:

```
{
    "request" : build_houses,
    "data": { 
        "groups": [<group_id>, ...]
    } 
}
```

Request:

Construction level needs to be in range from 0 = no building, 1 = one house, ... up to 5 = hotel. 
A request can only contain fields from one group.

```
{
    "request" : build_houses,
    "data": {
        "building_sites": { <field_id> : <construction_level>, ... }
    } 
}
```

Returns:

on success:
```
{
    "name" : "property_change",
    "data" :
    {
        index: <index>,
        owner: <player_name>,
        construction_level: <level>
    }
}
```

or


on failure:
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

#

## Watson

Is a game manipulating instance, which allows the player to cheat around in the game. But it comes for a price. Watson demands real life actions and informations.

Some actions have direct impact on the game while others generate Watson Coins. 

__Watson Coins__ 
can be used as currency by the course of 1 coin to 50 ingame money.


### Advertising

Client sends on click to server:

```
    {
        "request" : "clicked_on_add",
        "data" :
        {
            "add_name" : <add_name>
        }
    }
```

Effect: 
Server manipulates the current players roll dice result.

### Scanned GMail Account

Client sends on scan gmail account to server:

```
    {
        "request" : "scanned_gmail_account",
        "data" :
        {
            "dices" : [ <eyes>, <eyes> ]
        }
    }
```

Effect: 
Player will roll the requested eyes on next roll dice.

### Add Watson Coins

Client sends for each round a player hast activated bitcoin mining a request to add a watson coin:

```
    {
        "request" : "add_watson_coin",
        "data" :
        {
            "amount" : <amount>,
            "source" : "bitcoin_mining"
        }
    }
```
