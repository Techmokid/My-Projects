/*
1. 1 is represented by 100 microsecond squarewave with 50% dutycycle
2. 0 is represented by 200 microsecond squarewave with 50% dutycycle

Note, portions within square [ ] brackets must occur one or more times.

-Preamble:
 The preamble to a packet consists of a sequence of "1" bits.
 A digital decoder must not accept as a valid, any preamble that has less then 10 complete one bits, or require for proper reception of a packet with more than 12 complete one bits.
 A command station must send a minimum of 14 full preamble bits.
 
-Packet Start Bit:
 The packet start bit is the first bit with a value of "0" that follows a valid preamble.
 The Packet Start Bit terminates the preamble and indicates that the next bits are an address data byte.

-Address Data Byte:
 The first data byte of the packet normally contains eight bits of address information2.
 The first transmitted address bit shall be defined to be the most significant bit of the address data byte.
 Address Data Bytes with values 00000000, 11111110, and 11111111 are reserved for special operations and must not be transmitted.
 
-[ Data Byte Start Bit: This bit precedes a data byte and has the value of "0".

-Data Byte:
 Each data byte contains eight bits of information used for address, instruction, data, or error detection purposes.
 The first transmitted data bit of each data byte shall be defined to be the most significant bit of the data byte. ]

-Packet End Bit:
 This bit marks the termination of the packet and has a value of "1".
 */
