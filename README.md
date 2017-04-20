# CacheSimulator
***********************************************************************************
				CACHE SIMULATOR v1
************************************************************************************
				Documentation:
************************************************************************************
The cache simulator version v1.1 Single bank single file input. and
The cache simulator version v1.2. Multi bank Multi file input. output printing on the screen
The cache simulator version v1.3. Multi bank Multi file input. output printing on the single file1.txt
The cache simulator version v1.4. Multi bank Multi file input. output printing on the multiple file1.txt
The cache simulator version v1.5 Multi bank Multi file input. output printing on the multiple file1.txt(Number of files can be vary according to that it will generate output files with no. of banks)


NOTE: file cache_simul.cpp for compilation and random.cpp for generating random addresses. 1.txt, 2.txt, etc are sample input files. 
---------------
HOW TO COMPILE:
---------------
$ g++ cache_simul.cpp -pthread
$ ./a.out 1.txt 2.txt

NOTE: input files will be according to the number of banks required can be changed in config.txt file. 


miss_log.txt and output_bank_*.txt files will be created automatically


**************************************************************************************
					INPUT
**************************************************************************************

Use the input.txt as input file. Output will be printing on the screen. 



**************************************************************************************
			Auxilary Function for preprocessing:
**************************************************************************************

1. get_no_of_bits():This function returning the no of bits used to map input decimal value.

2. initialise()	: All the calculation of regarding Size of each bank, Number of tag bit size, Number of Index bit size, Number of bits for block offset, Number of Blocks, 
		Number of sets and Number of lines per set.

3. charEqual()	:its a function returning boolean value input will be two strings which is used to compare and no. of bits from the starting.

4. hex_to_bin()	:converts hexadecimal value to binary value return string of containing binary value. 

5. getSetIndex():returns the set index for according to input parameter of binary address and returns a decimal value of set index.



***************************************************************************************
			Details regarding different class methods 
***************************************************************************************

Class cacheline: Methods: this class containing only one constructor which creates blank single cacheline including initialising the data e.g. Valid bit, dirty bit, etc.

---------------------------------------

Class set: This class containing one constructor which will create blank cacheline inside seta according to the number of lines per set. 

Function of the class set:
1. evictblock()	:This will evict the block from the set when no space in the set for new block. It will check for the leaset recently used policy for the eviction of the 			block.check for the valid blocks of the set. Evict the block which having maximum lru value. Changes the lru bit to zero which means recently accessed and 			make valid bit as false.
	
2. read()	:Check for the valid locations of the cacheline in the corresponding set and matches tag bits of that location with the given address. The update LRU bit 			of the accessed location calling incrementLRU.

3. incrementLru():This will icrement all the lru value except the place which is given as integer input to this function. 

4. isFull()	:Checking weather the given set is full or empty this will return a boolean value if set is full 1 else zero.Check valid bits in all the cachelines of sets.  

5. updateDirty(): To update dirty bit when he get a hit inside cache and want to change some details in that cache block. 

6. write()	: Check for isFull and according to that evict the block when set is full. Writes on the one of the vacant location of the corresponding set. Also set 			different bits.

--------------------------------------

Class cache_bank: This class one constructor which create sets according to the total no. of sets after calculation and further constructors will be called automatically.

Function of the class cache_bank:
1. isHit()	: Check for valid locations and and response hit when tag values match found.
 
2. map()	: Mapping function and creating different logs according to the hit and misses. 

3. tostr()	: Converts integer value to string value. 

--------------------------------------

Class l1_cache: Create multibanks of l1 cache having single constructor which create multiple banks calling further constructors automatically. 


***************************************************************************************
			Details regarding structures used
***************************************************************************************
structure arg_struct used for sending data into the threads cb which cache we want to access, filename from which the address will be fetched filename,thread_id and thread_num explicitly 



***************************************************************************************
			Details regarding make_thread
*************************************************************************************** 
This is the function which will be called into the thread and multiple copies will be created. All the detauils of the thread extracted insode this corresponding file reading will be done and according the address and operation the details passed to map function. 

