//------------------------------------------------------------------------------
/*
	Copyright (c) 2012, 2013 Skywell Labs Inc.
	Copyright (c) 2017-2018 TrueChain Foundation.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef SKYWELL_CORE_LOADFEETRACK_H_INCLUDED
#define SKYWELL_CORE_LOADFEETRACK_H_INCLUDED

#include <cstdint>
#include <beast/utility/Journal.h>
#include <common/json/json_value.h>

namespace truechain {

/** Manages the current fee schedule.

    The "base" fee is the cost to send a reference transaction under no load,
    expressed in millionths of one SWT.

    The "load" fee is how much the local server currently charges to send a
    reference transaction. This fee fluctuates based on the load of the
    server.
*/
//  TODO Rename "load" to "current".
class LoadFeeTrack
{
public:
    /** Create a new tracker.
    */
    static LoadFeeTrack* New (beast::Journal journal);

    virtual ~LoadFeeTrack () { }

    // Scale from fee units to millionths of a truechain
    virtual std::uint64_t scaleFeeBase (std::uint64_t fee, std::uint64_t baseFee,
                                        std::uint32_t referenceFeeUnits) = 0;

    // Scale using load as well as base rate
    virtual std::uint64_t scaleFeeLoad (std::uint64_t fee, std::uint64_t baseFee,
                                        std::uint32_t referenceFeeUnits,
                                        bool bAdmin) = 0;

    virtual void setRemoteFee (std::uint32_t) = 0;

    virtual std::uint32_t getRemoteFee () = 0;
    virtual std::uint32_t getLocalFee () = 0;
    virtual std::uint32_t getClusterFee () = 0;

    virtual std::uint32_t getLoadBase () = 0;
    virtual std::uint32_t getLoadFactor () = 0;

    virtual Json::Value getJson (std::uint64_t baseFee, std::uint32_t referenceFeeUnits) = 0;

    virtual void setClusterFee (std::uint32_t) = 0;
    virtual bool raiseLocalFee () = 0;
    virtual bool lowerLocalFee () = 0;
    virtual bool isLoadedLocal () = 0;
    virtual bool isLoadedCluster () = 0;
};

} // truechain

#endif