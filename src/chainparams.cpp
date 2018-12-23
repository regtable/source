// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xa4;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0xc5;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 48794;
        nRPCPort = 48894;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "Google releases the first stable public version of their web browser";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1544606400, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1544606400;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1345989;

        if (false && genesis.GetHash() != hashGenesisBlock) {

                // This will figure out a valid hash and Nonce if you're
                // creating a different genesis block:
                    uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                    while (genesis.GetHash() > hashTarget)
                       {
                           ++genesis.nNonce;
                           if (genesis.nNonce == 0)
                           {
                               printf("NONCE WRAPPED, incrementing time");
                               ++genesis.nTime;
                           }
                       }
        }

        hashGenesisBlock = genesis.GetHash();

        //printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        //printf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("block.nTime = %u \n", genesis.nTime);
        //printf("block.nNonce = %u \n", genesis.nNonce);
        //printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        assert(hashGenesisBlock == uint256("0x0000079e330949c96f40cd10201f59b7a60b82e627c34c2fcf0cc5e6bb1ffa50"));
        assert(genesis.hashMerkleRoot == uint256("0xba40a03f5bd1a5186dd73e9d0f86a004ab74b36872148335fdda69c719c7daec"));

    
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("Oculor1.nodes", "80.211.81.239"));
        vSeeds.push_back(CDNSSeedData("Oculor2.nodes", "80.211.42.139"));
        vSeeds.push_back(CDNSSeedData("Oculor3.nodes", "80.211.137.213"));
        vSeeds.push_back(CDNSSeedData("Oculor4.nodes", "80.211.10.39"));
        vSeeds.push_back(CDNSSeedData("Oculor5.nodes", "80.211.83.138"));
        vSeeds.push_back(CDNSSeedData("Oculor6.nodes", "80.211.151.122"));
        vSeeds.push_back(CDNSSeedData("Oculor7.nodes", "80.211.60.164"));
        vSeeds.push_back(CDNSSeedData("Oculor8.nodes", "80.211.55.201"));
        vSeeds.push_back(CDNSSeedData("Oculor9.nodes", "80.211.178.62"));
        vSeeds.push_back(CDNSSeedData("Oculor10.nodes", "77.81.234.173"));
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,44);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,142);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 10000000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xbb;
        pchMessageStart[1] = 0xb4;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xb5;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 43544;
        nRPCPort = 43644;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 1497040584;
        genesis.nNonce = 213861;
		
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,229);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
