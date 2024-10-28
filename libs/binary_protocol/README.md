### 1. Packet Types and Headers

Each packet starts with a **header** that includes the packet type and length.

#### Header (1 byte)

- Bits 0-3

   \- Packet Type

  - `0001` - Player Action
  - `0010` - Game State Update
  - `0011` - Player Join
  - `0100` - Player Leave
  - `0101` - Game Over
  - `0110` - Keep-Alive

- **Bits 4-7** - Length Indicator (number of bytes that follow in the payload, up to 15 bytes)

For example, a `Player Action` packet with a 3-byte payload would have the header `0001 0011`.

### 2. Payload Structures

#### a. **Player Action** (Type `0001`)

Used when a player changes direction.

- Byte 1

   \- Player ID (0–255 values)

  - `0000 0000`

- Byte 2

   \- Direction

  - **Bits 0-1** - Direction (`00` = Up, `01` = Down, `10` = Left, `11` = Right)
  - **Bits 2-7** - Unused (set to `0`)

Example: A packet where Player 5 moves up would look like:

- Header: `0001 0011` (Type `0001`, 3 bytes follow)
- Payload: `0000 0101` (Player ID 5), `0000 0000` (Direction: Up)

#### b. **Game State Update** (Type `0010`)

Contains the current game state, including all players’ positions and the position of food.

- Byte 1-4

   \- Game Timestamp (milliseconds since game start)

  - `0000 0000 0000 0000 0000 0000 0000 0000`

- Player Data (repeated for each player)

  :

  - Byte 1

     \- Player ID

    - `0000 0000`

  - Byte 2-3

     \- Position X and Position Y (0–65535 values each)

    - `0000 0000 0000 0000`

  - Byte 4

     \- Direction and Snake Length

    - **Bits 0-1** - Current Direction (`00` = Up, `01` = Down, `10` = Left, `11` = Right)
    - **Bits 2-7** - Snake Length (up to 63 units)

Example: For Player 1 at position `(1024, 2048)` moving down with a snake length of 4:

- Header: `0010 1000` (Type `0010`, 8 bytes follow)
- Payload:
  - `0000 0000 0000 0000 0000 0000 0000 0001` (Timestamp, 4 bytes)
  - `0000 0001` (Player ID)
  - `0000 0100 0000 0000` (Position X: 1024)
  - `0000 1000 0000 0000` (Position Y: 2048)
  - `0000 0100` (Down, Length 4)

#### c. **Player Join** (Type `0011`)

When a new player joins the game.

- Byte 1

   \- Player ID

  - `0000 0000`

- Bytes 2–n

   \- Player Name (optional, up to 15 characters)

  - Each character encoded in ASCII (`0000 0000` per byte)

Example: Player 3 with the name "ACE":

- Header: `0011 0100` (Type `0011`, 4 bytes follow)
- Payload:
  - `0000 0011` (Player ID: 3)
  - `0100 0001` (ASCII 'A')
  - `0100 0011` (ASCII 'C')
  - `0100 0101` (ASCII 'E')

#### d. **Player Leave** (Type `0100`)

Used when a player disconnects or leaves.

- Byte 1

   \- Player ID

  - `0000 0000`

Example: Player 5 leaves:

- Header: `0100 0001` (Type `0100`, 1 byte follows)
- Payload:
  - `0000 0101` (Player ID: 5)

#### e. **Game Over** (Type `0101`)

Announces the game’s end and may optionally include the winning player.

- **Byte 1** - Winning Player ID (optional, can be `0000 0000` if no specific winner)

Example: Game over with Player 2 winning:

- Header: `0101 0001` (Type `0101`, 1 byte follows)
- Payload:
  - `0000 0010` (Winning Player ID: 2)

#### f. **Keep-Alive** (Type `0110`)

This packet keeps the connection alive and doesn’t require a payload.

- Header: `0110 0000` (Type `0110`, 0 bytes follow)