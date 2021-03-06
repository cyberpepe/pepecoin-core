// Copyright (c) 2014 BlackCoin Developers
// Copyright (c) 2014 DashCoin Developers
// Copyright (c) 2015 Transfercoin Developer
// Copyright (c) 2015-2016 PepeCoin Developers
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

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x3a;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0x2f;
        vAlertPubKey = ParseHex("0x04688723a08e1038ff423c00483e7dee15f6a3016e27c2dadd23c6c338ad7a5cd7f9e3f3933b96b2c78705bba59845e07566b8c9f6638476fa60ff5ee8d1108888");
        nDefaultPort = 29377;
        nRPCPort = 29376;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "March 5, 2016: UN human rights chief backs Apple in FBI encryption row - BBC News";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1457184666, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1457184666;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 663024;

        hashGenesisBlock = genesis.GetHash();
/*
		if (false ) {
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

        //// debug print
	      printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
	      printf("block.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
	      printf("block.nTime = %u \n", genesis.nTime);
	      printf("block.nNonce = %u \n", genesis.nNonce);
*/
        assert(hashGenesisBlock == uint256("0x00008cae6a01358d774087e2daf3b2108252b0b5a440195ffec4fd38f9892272"));
        assert(genesis.hashMerkleRoot == uint256("0xf8d91b2c93bd7222515770b67f20d3380edf8292548daeb3b0ce82fd5764dcac"));


        base58Prefixes[PUBKEY_ADDRESS] = list_of(55); // pepecoin addresses start with P
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[STEALTH_ADDRESS] = list_of(40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        vSeeds.push_back(CDNSSeedData("First",  "seed.pepecoin.net"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "0xPJJBpDg5LKJhAkqGDhG4Wuo9AUXBkz4SWY";
        nLastPOWBlock = 130420;
        nPOSStartBlock = 9000;
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
        pchMessageStart[0] = 0x3a;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0x2f;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04cc24ab003c828cdd9cf4db2ebbde8e1cecb3bbfa8b3127fcb9dd9b84d44112080827ed7c49a648af9fe788ff42e316aee665879c553f099e55299d6b54edd7e0");
        nDefaultPort = 39377;
        nRPCPort = 39376;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 663024;

        assert(hashGenesisBlock == uint256("0x00008cae6a01358d774087e2daf3b2108252b0b5a440195ffec4fd38f9892272"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(55);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[STEALTH_ADDRESS] = list_of(40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 2000;
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
