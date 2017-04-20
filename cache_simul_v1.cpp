#include<iostream>
#include<fstream>
#include<math.h>
#include<new>
#include<stdlib.h>
#include<cstdlib>
#include<string.h>
#include<string>
#include<stdio.h>
#include<vector>
#include <pthread.h>
#include<cstdlib>
#include<sstream>

using namespace std;
#define addr_bit 32
int cache_size=0,block_size=0,way=0,num_of_bank=0;
int tag_size=0,lines_per_set,bank_size,num_of_set,num_of_block;

int get_no_of_bits(int val)
{
	int i=0;
	while(1)
	{
		if(pow(2,i)!=val) i++;
		else
		return i;
	}
}

void initialise(){

	num_of_block=(int)(cache_size/block_size);
	num_of_set=(int)(num_of_block/way);
	
	//calculating the no. of bits for the corresponding tag and bank id 
	tag_size=addr_bit-get_no_of_bits(block_size)-get_no_of_bits(num_of_set);
	lines_per_set=way;
	bank_size=get_no_of_bits(num_of_bank);
	
	cout<<"\nSize of each bank : "<<cache_size/num_of_bank<<" bytes.";
	cout<<"Number of tagsize :"<< tag_size<<"bits \n";
	cout<<"Number of Index bit size  :"<< get_no_of_bits(num_of_set)<<"bits \n";
	cout<<"Number of bits for block offset :"<<get_no_of_bits(block_size)<<" bits"<<endl;
	
	
	cout<<"Number of Blocks :"<< num_of_block<<"blocks"<<endl;
	cout<<"Number of sets :"<< num_of_set<<"sets"<<endl;
	cout<<"Number of lines per set :"<< lines_per_set<<"ways"<<endl;
	
}



bool charEqual(char* a, char* b, int N){
  int count=0;
  for(int i=0;i<N;++i){
    if(a[i]==b[i])count++;
  }
  
  if(count==N)
  	return true;
  else
  	return false;
}


char* hex_to_bin(char* input){ 
    int x = 4;
    int size;
    size = strlen(input);
    //printf("size is %d\n",size);

    char* output = new char[size*4+1];
   
    for (int i = 0; i < size; i++)
    {
        if (input[i] =='0') {
            output[i*x +0] = '0'; output[i*x +1] = '0';  output[i*x +2] = '0'; output[i*x +3] = '0';
        }
        else if (input[i] =='1') {
            output[i*x +0] = '0'; output[i*x +1] = '0'; output[i*x +2] = '0';  output[i*x +3] = '1';
        }    
        else if (input[i] =='2') {
            output[i*x +0] = '0';  output[i*x +1] = '0';  output[i*x +2] = '1';    output[i*x +3] = '0';
        }    
        else if (input[i] =='3') {
            output[i*x +0] = '0';     output[i*x +1] = '0';       output[i*x +2] = '1';        output[i*x +3] = '1';
        }    
        else if (input[i] =='4') {
            output[i*x +0] = '0';   output[i*x +1] = '1';     output[i*x +2] = '0';      output[i*x +3] = '0';
        }    
        else if (input[i] =='5') {
            output[i*x +0] = '0';    output[i*x +1] = '1';     output[i*x +2] = '0';        output[i*x +3] = '1';
        }    
        else if (input[i] =='6') {
            output[i*x +0] = '0';   output[i*x +1] = '1';      output[i*x +2] = '1';       output[i*x +3] = '0';
        }    
        else if (input[i] =='7') {
            output[i*x +0] = '0';    output[i*x +1] = '1';       output[i*x +2] = '1';      output[i*x +3] = '1';
        }    
        else if (input[i] =='8') {
            output[i*x +0] = '1';   output[i*x +1] = '0';       output[i*x +2] = '0';      output[i*x +3] = '0';
        }
        else if (input[i] =='9') {
            output[i*x +0] = '1';    output[i*x +1] = '0';      output[i*x +2] = '0';       output[i*x +3] = '1';
        }
        else if (input[i] =='a'||input[i] =='A') {    
            output[i*x +0] = '1';    output[i*x +1] = '0';      output[i*x +2] = '1';       output[i*x +3] = '0';
        }
        else if (input[i] =='b'||input[i] =='B') {
            output[i*x +0] = '1';   output[i*x +1] = '0';      output[i*x +2] = '1';        output[i*x +3] = '1';
        }
        else if (input[i] =='c'||input[i] =='C') {
            output[i*x +0] = '1';     output[i*x +1] = '1';    output[i*x +2] = '0';        output[i*x +3] = '0';
        }
        else if (input[i] =='d'||input[i] =='D') {    
            output[i*x +0] = '1';   output[i*x +1] = '1';     output[i*x +2] = '0';        output[i*x +3] = '1';
        }
        else if (input[i] =='e'||input[i] =='E'){    
            output[i*x +0] = '1';   output[i*x +1] = '1';     output[i*x +2] = '1';       output[i*x +3] = '0';
        }
        else if (input[i] =='f'||input[i] =='F') {
            output[i*x +0] = '1';   output[i*x +1] = '1';     output[i*x +2] = '1';       output[i*x +3] = '1';
        }
    }

    output[32] = '\0';
    return output;
}



int bankId(char* temp){ 
		char *addrBin=hex_to_bin(temp);
  		int tmp=0;
  		//cout<<addrBin<<"Bits for bank"<<bits_for_bank<<endl;
  		for(int i=0;i<get_no_of_bits(num_of_bank);++i){
    			if(addrBin[tag_size+i]=='1') 
    			tmp+= pow(2,get_no_of_bits(num_of_bank)-1+i);
  		}
  		return tmp;
}


int getSetIndex(char* addrBin){ //Convertes the bits of bank id into decimal and return it
  int tmp=0;
  for(int i=0;i<get_no_of_bits(num_of_set);++i){
    if(addrBin[tag_size+i]=='1') tmp+= pow(2,get_no_of_bits(num_of_set)-1-i);
  }
  return tmp;
}



char* dec_to_bin(int addrDec){
  char* addrBin = new char[32]; 
  for(int i=0;i<32;++i){
    if( (addrDec & (1<<i))>>i) addrBin[31-i]='1';
    else addrBin[31-i]='0';
  }
  return addrBin;
}


 	

class cacheline{    // For the storage of the cache meta data create cachelines for each meta data.
	public:
		bool valid;
		bool dirty;
		char *tag ;
		int lru;
	public: 

  		cacheline(){
    			   valid=false;
    			   dirty=false;
    			   lru=0;
    			   tag=new char(tag_size);
    			   for(int i=0;i<tag_size;++i)
    			   {
    			   tag[i]='x';
    			   //cout<<"hii";
    			   }
			}
};




class set{  //creates sets and define operations on the set which can be applied on a single set. Called by the other class

public:
	vector<cacheline> c_line;
	
	set()
	{
    		for(int i=0;i<lines_per_set;++i)
    		c_line.push_back(cacheline());
	}
	
	
	void incrementLru(int hit)
	{
		for(int i=0;i<way;++i)
		{
      			if(c_line[i].valid&&i!=hit){
			c_line[i].lru++;
			c_line[i].lru = c_line[i].lru%way;
      			}
		}
	}
	
	void read(char *bin_addr)//
	{
		
		int i=0;
		while(i<lines_per_set)//for(int i=0;i<way;++i)
		{
		
      			if(c_line[i].valid&&charEqual(c_line[i].tag,bin_addr,tag_size)){//here binary tag matched with the bin value passed to this  
      				c_line[i].lru=0;
      				incrementLru(i);
      				cout<<"Block Accesed";
      				break;
      			}
      			i++;
		}
		cout<<"Read Miss, block to be loaded from l2\n";
	}//End of function read()
	
	
	void evictBlock()
	{
		int max=0,val=0;
		
		for(int i=0;i<lines_per_set;i++)
		{
      			if(c_line[i].valid)
      				if(c_line[i].lru>max)
      					{
      					max=c_line[i].lru;
      					val=i;
      					}
		}
		
		c_line[val].lru=0;
		c_line[val].valid=false;
	}
	
	bool isFull(){ //if set is vacant or not.
		int i=0,count=0;
	
		while(i<lines_per_set){
		
			if(c_line[i].valid)
			count++;
			i++;
		}	
	if(count==lines_per_set)
		return true;
	else
		return false;
	
	}
	
	
	void updateDirty(char* bin_addr)
	{
		int i=0;
		while(i<way)
		{
			if(c_line[i].valid&&charEqual(c_line[i].tag,bin_addr,tag_size)){  //For dirty bit updation when there is a write hit
      				c_line[i].dirty=true;
      				//break;
      			}
      			i++;
      		}
      	}
	
	void write(char *bin_addr)
	{
	
		int i=0;
		
		if(isFull())
			evictBlock();
		
		while(i<lines_per_set)//for(int i=0;i<way;++i)
		{
      			
      			if(!c_line[i].valid){       // When there is a write allocation 
      			cout<<" Way no:- "<<i<<"\n";
      			c_line[i].valid=true;
      			c_line[i].dirty=false;
			c_line[i].lru=0;
    			for(int j=0;j<tag_size;++j)
    			   	c_line[i].tag[j]=bin_addr[j];
    			
    			incrementLru(i);
    			break;
      			}
      			
      			++i;
      			
		}
	}
	
	
	
	
	
	

};


class cache_bank{ //Create one bank of l1 cache structure 
	
	public:
	vector<set> sets;

 	cache_bank()
 	{
 		//cout<<"oBject created for bank"<<endl;
   		for(int i=0;i<num_of_set;++i) 
   			sets.push_back(set());
	}
	
	
	bool isHit(char* tag, int setIndex)
	{
      		for(int j=0;j<lines_per_set;++j)
      		{
			if (charEqual(sets[setIndex].c_line[j].tag,tag, tag_size)&& sets[setIndex].c_line[j].valid){
	  			return true;
				}
     		}
    		return false;
 	}

	
	
	
	void map(char *dec_addr,char *op,int bid)
	{
		
		
		char *bin_addr=hex_to_bin(dec_addr);
		int setIndex=getSetIndex(bin_addr);
		
		
		if (!strcmp(op,"r"))
		{
			if (isHit(bin_addr,setIndex))
			{
				cout<<"Address: "<<dec_addr<<" Reading Block data from set: "<<setIndex<<endl;
				cout<<"Hit at the Address: "<<dec_addr<<":=\t"<<bin_addr<<"\tBank Id: "<<bid<<endl;
				sets[setIndex].read(bin_addr);
				cout<<"\n";
			}
			else
			{	
				cout<<"Reading request but found Read Miss Data will be loaded and writen to following addresses:"<<endl;
				cout<<""<<"Address: "<<dec_addr<<"\t"<<bin_addr<<"\tBank Id: "<<bid<<"\tEntering Value in set: "<<setIndex<<endl;
				cout<<"Read Miss at the Address: "<<dec_addr<<":=\t"<<bin_addr<<"\tBank Id: "<<bid<<endl;
				sets[setIndex].write(bin_addr);cout<<"\n";
			} 
			
		}
		else if(!strcmp(op,"w"))
		{
			if (isHit(bin_addr,getSetIndex(bin_addr)))
			{
				cout<<"Address: "<<dec_addr<<" Accessing Block data in set: "<<setIndex<<endl;
				cout<<"Hit at the Address: "<<dec_addr<<":=\t"<<bin_addr<<"\tBank Id: "<<bid<<endl;
				sets[setIndex].updateDirty(bin_addr);cout<<"\n";
			}
			else
			{
				cout<<"Address: "<<dec_addr<<":=\t"<<bin_addr<<"\tBank Id: "<<bid<<"\tEntering Value in set: "<<getSetIndex(bin_addr)<<endl;
				cout<<"Write Miss at the Address: "<<dec_addr<<":=\t"<<bin_addr<<"\tBank Id: "<<bid<<endl;
				sets[setIndex].write(bin_addr);cout<<"\n";
			}
		 }
		
			
	}//end of function map()
	
	
};



class l1_cache //Create multibanks of l1 cache
{
	public:
		
	vector<cache_bank> bank;

 	l1_cache()
 	{
 		//cout<<"oBject created for bank"<<endl;
   		for(int i=0;i<num_of_bank;++i) 
   			bank.push_back(cache_bank());
	}
		
};




int main(){

	
	int i=0;
	char addr[9],opr[2];
	
	ifstream loadconfig,inFile;
	loadconfig.open("config.txt");//Loading the confiuguration from the file for initialization 
	
	if (loadconfig.fail()) /// In case of file not opned
	{
		cerr<<"Error while opening configuration file"<<endl;
		exit(1);
	}
	
	inFile.open("cb1.txt");
	
	if (inFile.fail()) /// In case of file not opned
	{
		cerr<<"Error while opening input file"<<endl;
		exit(1);
	}
	
	loadconfig>>cache_size>>block_size>>way>>num_of_bank;
	cout<<"Cache Details \n"<<cache_size<<"KB with block size of "<<block_size<<"bytes and "<<way<<"-way associative "<<num_of_bank<<" Banks"<<endl;
	cache_size*=1024;
	
	initialise();
	l1_cache l1;
	
	for(int i=0;i<18;i++){
	
	inFile>>addr>>opr;
	cout<<addr<<"-"<<opr<<endl;
		l1.bank[0].map(addr,opr,0);
	cout<<"Iteration: "<<i;
	}
	


return 0;
}

