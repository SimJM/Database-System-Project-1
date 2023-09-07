# Database-System-Project-1
This project is to design and implement the following two components of a database management system, storage and indexing.

## (1) For the storage component, the following settings are assumed.
• a fraction of main memory is allocated to be used as disk storage for simplicity (and thus there is no need to worry about the buffer management); In the following, by disk storage, it refers to this allocated memory storage.
• the disk capacity could be 100 - 500 MB1 (depending on your machine’s main memory configuration);
• the disk storage is organized and accessed with a block as a unit; Note that since this disk storage is the allocated memory storage and can in fact be accessed with a byte/word as a unit, some mechanism needs to be designed here to simulate accesses with a block as a unit.
• the block size is set to be 400 B;
## (2) For the indexing component, the following settings are assumed.
• a B+ tree is used;
• for simplicity, the B+ tree is stored in main memory, with each node is stored in a memory region bounded by the block size (this simulates the case that each B+ tree node could be stored in a block on actual disk when necessary);
