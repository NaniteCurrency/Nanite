// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The NANITE developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
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

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000988bbd8738e3deb9994def8587ac894e1fa375a1aa72a4707a7b5072c39"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1520553600, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

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
        pchMessageStart[0] = 0x90;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xfd;
        pchMessageStart[3] = 0xe9;
        vAlertPubKey = ParseHex("04cb2b9206dec25c871410f4a32c3fc074b26e642fa6dc2c3c5d8dac30ab4faf1ff4f9cce705b14a2f67321f43af82513adca6d6efb713cbebfbe7e2b269141d67");
                                 
        nDefaultPort = 5818;
    	bnProofOfWorkLimit[ALGO_SCRYPT]  = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_GROESTL] = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_X17]     = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_LYRA2RE] = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_BLAKE]   = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // NANITE: 1 day
        nTargetSpacing = 1.5 * 60;  // NANITE: 1.5 minute
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 14000;
        nModifierUpdateBlock = 1;
        nZerocoinStartHeight = 15000;
        nZerocoinStartTime = 1520553600; // Friday, March 9, 2018 12:00:00 AM
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 15650; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 99999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 15648; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 15850; //Start enforcing the invalid UTXO's

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Happy Birthday Bull Market: TheStreet Takes a Look Back ... and a Look Ahead";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0490db2290a906032742617d660838914de4a73b194c05575df8b6dd162bf59d140bf6ddf61944f7fde730ed67958b918517a032455ad341a9e491134e800fcd5a") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1520553600; // Friday, March 9, 2018 12:00:00 AM
        genesis.nBits = bnProofOfWorkLimit[ALGO_X17].GetCompact();
        genesis.nNonce = 7703983;

        hashGenesisBlock = genesis.GetPoWHash(ALGO_X17);

       /* while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_X17]){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetPoWHash(ALGO_X17);
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit[ALGO_X17].GetCompact());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        genesis.print();
     */
        assert(hashGenesisBlock == uint256("0x00000839101eae5aa45d63346d852d532ab5d98c15a501368632b53a3f51eb3b"));
        assert(genesis.hashMerkleRoot == uint256("0xeb1a92db7bdaf6a90f89f658a72dd03654d8c6df037ea99b810573323c036cc4"));

        vSeeds.push_back(CDNSSeedData("nanite.org", "node1.nanite.org"));     // Primary DNS Seeder from Nanite
        vSeeds.push_back(CDNSSeedData("nanite.org", "node2.nanite.org"));    // Secondary DNS Seeder from Nanite
	vSeeds.push_back(CDNSSeedData("nanite.org", "node3.nanite.org"));    // 
	vSeeds.push_back(CDNSSeedData("nanite.org", "node4.nanite.org"));    // 

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 112);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "048CEE858A5E6CABB0D596E17A1B2D3981CA0FBCDF403D7E6C39022A8897F745946C092986B33A7D4414F521BD5385732ABF34540B142C300EE4F9A6741289CDB7";
        strObfuscationPoolDummyAddress = "nNjpkpgQyWNxWMwVJjuB5pDzTFmXhZbCph";
        nStartMasternodePayments = 1520553600; // Friday, March 9, 2018 12:00:00 AM

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 7; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
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
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("04cb2b9206dec25c871410f4a32c3fc074b26e642fa6dc2c3c5d8dac30ab4faf1ff4f9cce705b14a2f67321f43af82513adca6d6efb713cbebfbe7e2b269141d67");
        nDefaultPort = 15817;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // NANITE: 1 day
        nTargetSpacing = 1.5 * 60;  // NANITE: 1 minute
    	bnProofOfWorkLimit[ALGO_SCRYPT]  = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_GROESTL] = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_X17]     = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_LYRA2RE] = ~uint256(0) >> 20;
    	bnProofOfWorkLimit[ALGO_BLAKE]   = ~uint256(0) >> 20;
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1520553600;
        genesis.nNonce = 7703983;

        hashGenesisBlock = genesis.GetPoWHash(ALGO_X17);

      /* while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_X17]){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetPoWHash(ALGO_X17);
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit[ALGO_X17].GetCompact());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        genesis.print();
   */
   
        assert(hashGenesisBlock == uint256("0x00000839101eae5aa45d63346d852d532ab5d98c15a501368632b53a3f51eb3b"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("nanite.org", "node1-testnet.nanite.org"));
        vSeeds.push_back(CDNSSeedData("nanite.org", "node2-testnet.nanite.org"));
        vSeeds.push_back(CDNSSeedData("nanite.org", "node3-testnet.nanite.org"));
        vSeeds.push_back(CDNSSeedData("nanite.org", "node4-testnet.nanite.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet nanite addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet nanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet nanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet nanite BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet nanite BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "048CEE858A5E6CABB0D596E17A1B2D3981CA0FBCDF403D7E6C39022A8897F745946C092986B33A7D4414F521BD5385732ABF34540B142C300EE4F9A6741289CDB7";
        strObfuscationPoolDummyAddress = "yL6iG7n5QuzHotAGLLCaeqhsuR5rekEE27";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
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
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // NANITE: 1 day
        nTargetSpacing = 1 * 60;        // NANITE: 1 minutes
    	bnProofOfWorkLimit[ALGO_SCRYPT]  = ~uint256(0) >> 1;
    	bnProofOfWorkLimit[ALGO_GROESTL] = ~uint256(0) >> 1;
    	bnProofOfWorkLimit[ALGO_X17]     = ~uint256(0) >> 1;
    	bnProofOfWorkLimit[ALGO_LYRA2RE] = ~uint256(0) >> 1;
    	bnProofOfWorkLimit[ALGO_BLAKE]   = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12346;

        hashGenesisBlock = genesis.GetPoWHash(ALGO_X17);

       /*while (hashGenesisBlock > bnProofOfWorkLimit[ALGO_X17]){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetPoWHash(ALGO_X17);
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit[ALGO_X17].GetCompact());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
        genesis.print();
    */

        nDefaultPort = 51476;
        assert(hashGenesisBlock == uint256("0x0e3fc7437123823858a357b416c9f630701a559ec3ad0e244e12541b8be1d914"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

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
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

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
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
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
