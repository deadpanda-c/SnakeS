### 1. Packet Types and Headers

Each packet starts with a **header** that includes the packet type and length.

#### Header (1 byte)

- **Bits 0-3** - Packet Type
  - `0001` - Player Position
  - `0010` - Apple Position
  - `0011` - Player Join
  - `0100` - Player Leave
  - `0101` - Game Overs
  - `0110` - Keep-Alive

- **Bits 4-7** - Length Indicator (number of bytes that follow in the payload, up to 15 bytes)

For example, a `Player Position` packet with a 3-byte payload would have the header `0001 0011`.

### 2. Payload Structures

#### a. **Player Position** (Type `0001`)

Used to send player position

- **Byte 1** - Player ID (0–255 values)

  - `0000 0000`

The next bytes are the positions of the segments: 

- **Bytes 2-3** - Segment pos 1
  - `xxxxxxx yyyyyyyy`

- **Bytes n-n+1** - Segment pos n/2 (etc...)

**Example**: Snake of id `1` is at pos `[(15, 20), (16, 20), (16, 21), (16, 22)]`
  - **Header**
    - `0001 1001`
  - **Payload**
    - Binary:
      - `00000001` Player id
      - `00001111` `00010100` 15 20
      - `00010000` `00010100` 16 20
      - `00010000` `00010101` 16 21
      - `00010000` `00010110` 16 22
    - Hex:
      - `01`
      - `0F` `14`
      - `10` `14`
      - `10` `15`
      - `10` `16`

#### b. **Apple Position** (Type `0010`)

- **Byte 1-2** - Position x and y
  - `xxxxxxxx yyyyyyyy`

#### c. **Player Join** (Type `0011`)

When a new player joins the game.

- **Byte 1** - Player ID
  - `0000 0000`

- **Bytes 2–n** - Player Name (optional, up to 15 characters)
  - Each character encoded in ASCII (`0000 0000` per byte)

**Example**: Player 3 with the name "ACE":
- **Header**: `0011 0100` (Type `0011`, 4 bytes follow)
- **Payload**:
  - `0000 0011` (Player ID: 3)
  - `0100 0001` (ASCII 'A')
  - `0100 0011` (ASCII 'C')
  - `0100 0101` (ASCII 'E')

#### d. **Player Leave** (Type `0100`)

Used when a player disconnects or leaves.

- **Byte 1** - Player ID
  - `0000 0000`

**Example**: Player 5 leaves:
- **Header**: `0100 0001` (Type `0100`, 1 byte follows)
- **Payload**: `0000 0101` (Player ID: 5)

#### e. **Game Over** (Type `0101`)

Announces the game’s end and may optionally include the winning player.

- **Byte 1** - Winning Player ID (optional, can be `0000 0000` if no specific winner)

**Example**: Game over with Player 2 winning:
- **Header**: `0101 0001` (Type `0101`, 1 byte follows)
- **Payload**: `0000 0010` (Winning Player ID: 2)

#### f. **Keep-Alive** (Type `0110`)

This packet keeps the connection alive and doesn’t require a payload.

- **Header**: `0110 0000` (Type `0110`, 0 bytes follow)