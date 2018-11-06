//
//  main.cpp
//  new_aghili_attack
//
//  Created by Mahyar on 10/19/17.
//  Copyright © 2017 Mahyar. All rights reserved.
//


#include <iostream>
#include <bitset>
#include <cstdint>
#include <time.h>
#include <stdlib.h>

using namespace std;

std::uint32_t rotl(std::uint32_t v, std::int32_t shift) {
    std::int32_t s =  shift>=0? shift%32 : -((-shift)%32);
    return (v<<s) | (v>>(32-s));
}

std::uint32_t rotr(std::uint32_t v, std::int32_t shift) {
    std::int32_t s =  shift>=0? shift%32 : -((-shift)%32);
    return (v>>s) | (v<<(32-s));
}

uint32_t hw(uint32_t N)
{
    uint32_t result = 0;
    while(N)
    {
        result++;
        N &=N-1;
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(NULL));
    
    bitset<32> K (rand());
    bitset<32> Sij (rand());
    bitset<32> Tij (rand());
    bitset<32> Nr (rand());
    bitset<32> Nt (rand());

    uint32_t _K = (uint32_t)K.to_ulong();
    uint32_t _Tij = (uint32_t)Tij.to_ulong();
    uint32_t m_star = rotr(_Tij, hw(_K));
    uint32_t hamming_weight_of_k = hw(_K);
    
    cout << "FAN Protocol Init" << endl;
    cout << "Secret Nr = " << Nr << endl;
    cout << "Secret Nt = " << Nt << endl;
    cout << "Secret K = " << K << endl;
    cout << "Tij = " << Tij << endl;
    cout << "Sij = " << Sij << endl;
    cout << "Secret HW(K) = " << hamming_weight_of_k << endl;
    cout << "M* = RoR(Tij, hw(K)) = " << bitset<32> (m_star) << endl;
    cout << "RoR(Sij, hw(Tij)) = " << bitset<32>(rotr(_Tij, hw((uint32_t)Sij.to_ulong()))) << endl;
    
    cout << "--------" << endl;
    
    cout << "Attacking..." << endl;
    
    for (uint32_t p = 0; p < 32; p++) {
        
        uint32_t x = rotr(_Tij, p);
        
        cout << "x = RoR(Tij, p) = " << bitset<32> (x) << endl;
        
        if (x == m_star) {
            
            cout << "Found HW of K: " << p << endl;
            
            break;
        }
        
    }

    getchar();
    
    return 0;
    
}

