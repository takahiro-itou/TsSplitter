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
**      @file       Bin/SampleApplication.cpp
**/

#include    "TsSplitter/Common/SampleDocument.h"

#include    <iostream>

using   namespace   TSSPLITTER_NAMESPACE;

size_t
parseTsFile(
        const  std::string  &fileName)
{
    size_t  PIDs[8192];
    uint8_t buf[204];

    FILE *  fp  = fopen(fileName.c_str(), "rb");
    if ( fp == nullptr ) {
        return ( 0 );
    }

    size_t  cbRead;
    size_t  num;
    for (;;) {
        cbRead  = fread(buf, 1, 188, fp);
        if ( cbRead != 188 ) {
            break;
        }
        ++ num;
    }

    std::cerr   <<  "Total : "  <<  num <<  " packets.\n"
                <<  "Last Read = "  <<  cbRead  <<  " bytes."
                <<  std::endl;
    fclose(fp);
}

int  main(int argc, char * argv[])
{
    if ( argc >= 2 ) {
        parseTsFile(argv[1]);
    }

    return ( 0 );
}
