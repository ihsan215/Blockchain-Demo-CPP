#include "lib/blockchain.hpp"

using namespace std;

int main(){

    Blockchain blockchain;

    // Blockchain Mine
    for(int i = 0; i<20; i++){
        blockchain.Mine("This is " + to_string(i+2) + "th block and some data ...");
        blockchain.Sleep();
    }
    
    // Get Blockchain (to txt file)
    blockchain.Get_BlockChain();

    return 0;
}