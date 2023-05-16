#ifndef __BLOCKCHAIN_HPP__
#define __BLOCKCHAIN_HPP__


#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include "sha256.h"
#include <fstream>


using namespace std;

class Blockchain{

    private:

    typedef struct Block{

        uint64_t index;
        uint64_t nonce;
        
        time_t time_stamp;

        string data;
        string prev_hash;
        string current_hash;

    }Block_st;


    Block_st block;

    void generate_genesis_block();
    string hash(string _data);
    void proof_of_work(Block_st *_block);
    string block_2_string(Block_st *_block);
    void clear_current_block();
    string uint64_to_string(uint64_t _number);
    bool check_hash_is_available(string _hash);
  
    public:

    Blockchain();

    void Mine(string _data);

    void Get_BlockChain();

    bool Check_Chain_Is_Valid();

    vector<Block_st> Chain;


};


#endif