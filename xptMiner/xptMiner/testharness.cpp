#include <gmp.h>
#include <stdio.h>
#include <stdint.h>
#include "rh_riecoin.h"

void riecoin_init(uint64_t, int);
extern "C" void rh_search(mpz_t target);

volatile uint32_t monitorCurrentBlockHeight; // used to notify worker threads of new block data
volatile uint32_t monitorCurrentBlockTime; // keeps track of current block time, used to detect if current work data is outdated

// stats
volatile uint32_t totalShareCount = 0;
volatile uint32_t totalRejectedShareCount = 0;
volatile uint32_t total2ChainCount = 0;
volatile uint32_t total3ChainCount = 0;
volatile uint32_t total4ChainCount = 0;

typedef uint32_t uint32;
typedef uint8_t uint8;
typedef uint64_t uint64;

typedef struct
{
        // block data (order and memory layout is important)
        uint32  version;
        uint8   prevBlockHash[32];
        uint8   merkleRoot[32];
        uint32  nBits; // Riecoin has order of nBits and nTime exchanged
        uint64  nTime; // Riecoin has 64bit timestamps
        uint8   nOffset[32];
        // remaining data
        uint32  uniqueMerkleSeed;
        uint32  height;
        uint8   merkleRootOriginal[32]; // used to identify work
        // uint8        target[32];
        // uint8        targetShare[32];
        // compact target
        uint32  targetCompact;
        uint32  shareTargetCompact;
}minerRiecoinBlock_t;

extern minerRiecoinBlock_t* verify_block;

int main()
{
  minerRiecoinBlock_t block;
  monitorCurrentBlockHeight = 1200;
  block.height = 1200;
  verify_block = &block;

  riecoin_init(0, 0); 

  mpz_t target;
  mpz_init_set_str(target, "2001617f4d78f05f0787e8ed9dd5c0d03df3f36098fc9fe1270772ecd697b0a94a0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 16);

  rh_search(target);

  return 0;
}
