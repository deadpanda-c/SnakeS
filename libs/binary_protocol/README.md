# Binary Protocol



## Server part

### Player identification (login)

* Player 1: `0000 0001`
* Player 2: `0000 0010`
* Player 3: `0000 0011`
* Player 4: `0000 0100`



### Player disconnection

The `*` represents the player id.s

* `* 1111`

### Snake's Motion

The `*` represents the player id.

* Up: `* 0001`
* Down: `* 0010`
* Right: `* 0011`
* Left: `* 0100`



### Snake action

* Eat: `* 0001`
* Die: `* 0010`
* Level up: `* 0011`



## Client part

### Snake's Motion

* Up: `0000 0001`
* Down: `0000 0010`
* Right: `0000 0011`
* Left: `0000 0100`



### Snake action

* Eat: `0000 0001`
* Die: `0000 0010`
* Level up: `0000 0011`