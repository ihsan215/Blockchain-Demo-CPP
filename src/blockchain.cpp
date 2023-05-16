#include "../lib/blockchain.hpp"


/////////////////////////////
// Public Functions

// Constructure
Blockchain::Blockchain(){
    this->generate_genesis_block();
}


// Mine Block
void Blockchain::Mine(string _data){

    this->block.prev_hash = this->Chain.at(this->block.index-1).current_hash;
    this->block.index++;
    this->block.time_stamp = time(0);
    this->block.data = _data;
    this->proof_of_work(&this->block);
    this->Chain.push_back(this->block);

}

// Check Chain is valid
bool Blockchain::Check_Chain_Is_Valid(){
    
    int _length = this->Chain.size();
     for(int i = 0; i<_length; i++){

          string _data = this->block_2_string(&this->Chain.at(i));
          uint64_t _nonce = this->Chain.at(i).nonce;
          string _hash = this->hash(_data + uint64_to_string(_nonce));
        
          if(i >= 1){
            if(!(this->Chain.at(i).prev_hash == this->Chain.at(i-1).current_hash)){
                return false;
            }
          }

          if(!this->check_hash_is_available(_hash)){
            return false;
          }
 
     }


    return true;
}

// Get Chain (to txt file)

void Blockchain::Get_BlockChain(){


    // Create and open 
    ofstream ChainFile("Blockchain.txt");

    string _str = "";

    if(this->Check_Chain_Is_Valid()){
        
         _str += "Chain is Valid"; 

        for(int i = 0; i<this->Chain.size(); i++){

        _str = "\n-------------------------------------\n";
        _str += "\nIndex: " + uint64_to_string(this->Chain.at(i).index);
        _str += "\nTime-Stamp: ";
        _str +=  ctime(&this->Chain.at(i).time_stamp);
        _str += "Nonce: " + uint64_to_string(this->Chain.at(i).nonce);
        _str += "\nData: " + this->Chain.at(i).data;
        _str += "\nPrev. Hash: " + this->Chain.at(i).prev_hash;
        _str += "\nCurrent Hash: " + this->Chain.at(i).current_hash + "\n";
        _str += "\n-------------------------------------\n";
        
        // Write to the file
        ChainFile << _str;
    }
    }

    else{
         _str += "Chain is not Valid"; 
         ChainFile << _str;
    }

 

    ChainFile.close();
}

// Public Functions
/////////////////////////////


/////////////////////////////
// Private Functions

 // Genesis Block
void Blockchain::generate_genesis_block(){

    this->block.index = 1;
    this->block.time_stamp = time(0);
    this->block.data = "This is Genesis Block";
    this->block.prev_hash = "0000000000000000000000000000000000000000000000000000000000000000";
    this->proof_of_work(&this->block);
    this->Chain.push_back(this->block);
}

// Calculate Nonce and Hash
void Blockchain::proof_of_work(Block_st *_block){

    // Get block full data for calculate nonce and hash
    string _data = this->block_2_string(_block);
    uint64_t _nonce = 0;

    string _hash = "FFFF";
    // Find the nonce value for available  hash
    while (!this->check_hash_is_available(_hash))
    {   
        _nonce++;
        _hash = this->hash(_data + uint64_to_string(_nonce));
    }
    
    // Assign the correct Value
    _block->nonce = _nonce;
    _block->current_hash = _hash;
    
}

// Convert block to string
 string Blockchain::block_2_string(Block_st *_block){

    // Full block data
    string _data;

    // Add index to data
    _data += uint64_to_string(_block->index);

    // Add timestamp to data
    _data += ctime(&_block->time_stamp);

    // Add block data
    _data += _block->data;

    // Add prev. Has
    _data += _block->prev_hash;

    return _data;
 }

// Clear Current Block
void Blockchain::clear_current_block(){

    this->block.index = -1;
    this->block.time_stamp = -1;
    this->block.data = "-1";
    this->block.prev_hash = "-1";
    this->block.current_hash = "-1";
    this->block.nonce = -1;

}

// uint64_t to string converter
string Blockchain::uint64_to_string(uint64_t _number){

    ostringstream _str;
    _str << _number;
    return (_str.str());

}

// Check Hash
bool Blockchain::check_hash_is_available(string _hash){

    for(uint8_t i = 0; i<4; i++ ){
        if(_hash[i] != '0')
        return false;
    }

    return true;
}

// SHA 256
 string Blockchain::hash(string _data){
    return sha256(_data);
 }

// Private Functions
/////////////////////////////
