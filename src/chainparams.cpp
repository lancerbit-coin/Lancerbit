// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The Lancerbit developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"

/**
 * Main network
 */
//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
                (0, uint256("0x000003cb1aac143d719b2e06c003952958a77a16dad2343ec17df5804e518f60"));

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1524769569, // * UNIX timestamp of last checkpoint block
        15000,      // * total number of transactions between genesis and last checkpoint
        //   (the tx=... number in the SetBestChain debug.log lines)
        1400        // * estimated number of transactions per day after checkpoint
};
static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000040df09b15ba874400ba995f342b82573864b9ee10c255dc4448ce334438"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1523855288,
    0,
    250};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1521117300,
    0,
    100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc5;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xe1;
        pchMessageStart[3] = 0xd6;
        vAlertPubKey = ParseHex("04889c5f8d7aaab2630eb00bd060d125adc52b073e77f7691fbef150ee88c55fbf5148d603adfb37c8259a29fc4e68d5be49afcfa08cd04619c7e4761bfca1099a");
        nDefaultPort = 3489;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Lancerbit starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Lancerbit: 1 minute
        nTargetSpacing = 1 * 60;  // Lancerbit: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 60;
        nModifierUpdateBlock = 1;
	

	    const char* pszTimestamp = "Lancerbit Starter. Good things for a good future. Start 2018.6.28 12:00:00";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0462ddd7254e7285f4edb97d0280878130e757a5fc14e463fd477d355ecbd530d3b483cbf8d0c174d237e843d86f9e84aeb9ea7d4caa9365d890f76362c2817c48") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1530190500;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 561698;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000001dc1d7f61ef15bd44d072ef07bc9757235505efbd624c2c7ca6874a1d39"));
        assert(genesis.hashMerkleRoot == uint256("0x8d307db628d2fc58093f08e4e131db3d2d3cb61b9ed6556f403547e2a406fe7f"));

        vSeeds.push_back(CDNSSeedData("0",  "dnsseed.lancerbit.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is 'TBD'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "04a71d2f5a6188aaa08c8b8ba0a15e6a3a8ce63c49f4aa8554935af8b1f831ae1502b51b4b46d64ef15e2823ca5b914326306a2037feb8aac9c1231dc9b2bd22a9";
        
        strObfuscationPoolDummyAddress = "BKcUbM3ryKwfdjbd33FnAYFspaxDp4vWLs";
        nStartMasternodePayments = 1523435473;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x75;
        pchMessageStart[3] = 0x86;
        vAlertPubKey = ParseHex("04207f3e4229bdd4f408e77918571292e149c52b3ff92ef0ec55c5c4e34ae633c331e24e6e70173b03c18549284e29eea43f74d5b32eba631a5d0c277486103c66");
        nDefaultPort = 13489;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Lancerbit: 1 day
        nTargetSpacing = 1 * 60;  // Lancerbit: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 60;
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1523855288;
        genesis.nNonce = 2733486;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000040df09b15ba874400ba995f342b82573864b9ee10c255dc4448ce334438"));
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("", ""));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 112);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 29);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 240);
        // Testnet lancerbit BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet lancerbit BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet lancerbit BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04df60d7360059adbd96509eb20b9c6f637b364b02874312c9ef46c44ffc1492993e54c2f464512d9632a21e8c6f0ac5c07bd32c9a4e4f3d969b63be70009f3ca5";
        strObfuscationPoolDummyAddress = "";
        nStartMasternodePayments = 1522903751;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x64;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Lancerbit: 1 day
        nTargetSpacing = 1 * 60;        // Lancerbit: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1523854631;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 7065194;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 20229;
        //assert(hashGenesisBlock == uint256("0x000006e6fa091a20a38fe6f0212d03e5df72b44d76e2eb4246b4d366dbb01faf"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 21229;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;
CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}
const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
