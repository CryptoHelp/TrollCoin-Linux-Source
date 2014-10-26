// Copyright (c) 2009-2014 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2011-2014 TrollCoin Developers.
// Wallet Upgrade to Version 1.0 by Spencer Lievens

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0xf1b4cdf03c86099a0758f1c018d1a10bf05afab436c92b93b42bb88970de9821"))
            (     10000, uint256("0xd60b4e445508d081fe86d68c33c40ac0b2b10171f5127d0c707c0409ee0ff46c"))
            (     20000, uint256("0x7c833a31c1882fef279808c288c0daa237b66bb405fc1fc3640aca34a4282a43"))
            (     30000, uint256("0xfdd7c2fd7910186eebab806b73264ccb725a6de24d977cdf8a725f421a3104ce"))
            (     40000, uint256("0xd9f7143c86e31c800c41857740b58f5e3f7cde254918e6df37fc5cde08352d1b"))
            (     50000, uint256("0x59ddf33901d1b8050e00a65e68c2b0094273c5dd56c5e3c8b764fb048408416e"))
            (     60000, uint256("0xed07268836a01981f4090a79513cadbeafa53fa723454399dfc050eb2de0edfa"))
            (     70000, uint256("0x30e0190c594761be4ca30ef465ea183a64fa12f640c7f9a67b1e0f6bbc8b20f3"))
            (     80000, uint256("0x2f5240b2639b34071e9cdc66f7288bfceaeca2cfe88f57ad383b84ad6c69b496"))
            (     90000, uint256("0xee5e40d564735cddbf0bee760dab75b4649036f6e679b8e9b78db21c85f170d8"))
            (    100000, uint256("0x1f391825b4ed3204167e7a84dc7a852741fd2dedff0c71ab19978e1785517c18"))
            (    110000, uint256("0xf3c3b5466dfece6eec1a2391305aea7164cdc6a740e7a1083eb20954b981f72a"))
            (    125000, uint256("0x995b8bfef20ae43a45a72f93cffcfdc787cad4401c5e2dc7348beb34eb877fe6"))
            (    145000, uint256("0xf908a96328252dfc1486b30211c531ce2e0c5a4d16fc620fb9a6ce67911adee9"))
            (    160000, uint256("0xaf30077c7f26294069bef8fda38540c12bc0d1c330ac15650b6ec2b6abed5161"))
            (    170000, uint256("0x94f20c335f4859f29a92b8b67414720ad59b05f93e2a1aee4f7630b48cd04675"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
