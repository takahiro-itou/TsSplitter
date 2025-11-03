//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      -- TS Splitter Project. --                      **
**                                                                      **
**          Copyright (C), 2025-2025, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      サンプルプログラム。
**
**      @file       Bin/ExtractPID.cpp
**/

#include    "TsSplitter/Common/TsSplitterTypes.h"
#include    "TsSplitter/Common/FileReader.h"

#include    <cstdint>
#include    <cstring>
#include    <iostream>

using   namespace   TSSPLITTER_NAMESPACE;

int  main(int argc, char * argv[])
{
    Common::FileReader  fr;
    int64_t             thSkip  = 8388608;

    if ( argc >= 4 ) {
        thSkip  = std::stoll(argv[3], nullptr, 0);
    }
    std::cerr   <<  "Skip Threshold: "  <<  thSkip
                <<  std::endl;

    if ( argc >= 3 ) {
        fr.splitTsPid(argv[1], argv[2], thSkip);
    } else if ( argc >= 2 ) {
        fr.splitTsPid(argv[1], "out", thSkip);
    }

    return ( 0 );
}
