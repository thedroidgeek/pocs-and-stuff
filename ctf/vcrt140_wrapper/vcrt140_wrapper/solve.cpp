
#include "stdafx.h"
#include "utils.h"
#include "solve.h"


void solve()
{
    /*
        'emulate' the vm instructions that load the encrypted credentials
    */

    // bytecode that pushes the encrypted creds to the vm stack
    auto loadCodeLoc = getExeAddress<uint16_t>(0x1A30A);

    // count the number of instructions/values
    size_t numValues = 0;
    const uint16_t pushImmOpcode = 0x31D; // 1D 03 XX XX XX XX
    for (auto i = loadCodeLoc; *i == pushImmOpcode; i += 3, numValues++);

    // allocate the 'fake stack' for these values
    uint32_t* fakeStack = new uint32_t[numValues];

    // 'push' them (fill array from bottom to top)
    int i = numValues - 1;
    for (auto j = loadCodeLoc + 1; i >= 0; j += 3, i--) {
        fakeStack[i] = *(uint32_t*)j;
    }

    /*
        decrypt the credentials using our function and write them on console stdin to unlock the flag
    */

    // decrypt the credentials
    decryptCredentials(fakeStack, numValues * sizeof(uint32_t));

    // write credentials to console input
    enterAsciiLineToStdin((char*)fakeStack);

    delete[] fakeStack;
}


/*
    the credential encryption function extracted from virtualized code
*/

void encryptCredentials(uint8_t* string, size_t len)
{
    static uint8_t prev_byte = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        uint8_t c = string[i] + 1;

        c = _rotr8(c, 1);
        c -= 14;
        c = ~c;
        c ^= 0xC3;
        c = -c;
        c += 62;
        c = _rotl8(c, 3);
        c--;
        c ^= prev_byte;

        prev_byte = c;
        string[i] = c;
    }
}


/*
    the credential decryption function obtained by logically reversing the encyption function
*/

void decryptCredentials(void* blob, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        uint8_t c = ((uint8_t*)blob)[i];
        uint8_t next_c = ((uint8_t*)blob)[i+1];

        c ^= next_c;
        c++;
        c = _rotr8(c, 3);
        c -= 62;
        c = -c;
        c ^= 0xC3;
        c = ~c;
        c += 14;
        c = _rotl8(c, 1);

        ((uint8_t*)blob)[i] = c - 1;
    }
    ((uint8_t*)blob)[size - 1] = '\0';
}
