// This is the Extended Dynamic I2C (Extended Dynamic Inter-Intergrated Circuit)

// Transmitted messages:                            Syntax:
//  - Handing over master control:                  "[New Master Address]|MS"
//  - Transmitting Generic Data:                    "[Slave Address]|GD:[Data]"
//  - Give new device I2C address:                  "-1|NA:[New Slave Address]"
//  - Give device "allNetworkAddresses" readout:    "[Slave Address]|UA:{List Of Addresses}"
//  - Give device "masterAddresses" readout:        "[Slave Address]|PM:{List Of Previous Masters}"
//  - Transmit corrupted data warning:              "[Slave Address]|CD:[Received Data]:[Received Params]"
//  - Leaving Network:                              "[My Address]|LN"

// Wiring:
//  - D2: Master lock (The master holds this high)
//  - D3: Transmitting Message Line (interrupt1)
//  - D4: Network Data line
//  - D5: Network Clock line
//  - D6: Address Request New line (Hold high until master responds)
//  - D7: Address Request Ready (From master)





// When joining the network, read pin "D2":
//  - If the lock is off after 100ms (To prevent jumping in during a master swap), then turn on the line and become a master.
//  - If the lock is on, become a slave and ask the master for an address

// If you receive a network ping for master-request AND you are master:
//  - Add the current address count to the network list in memory and increment the address counter
//  - Ping the network to notify other devices of the added device
//  - Ping the device with the current free I2C-address

// If you are master and you are handing over control:
//  - Transmit "Master Swap:", then the address of the next master in line
//  - Become slave and let go of master lock
