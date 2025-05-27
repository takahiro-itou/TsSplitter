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
    std::cerr   <<  "Open : " <<  fileName  <<  std::endl;

    size_t  cbRead;
    size_t  numPckt = 0;
    size_t  cbTotal = 0;
    size_t  numErr  = 0;

    for (;;) {
        cbRead  = fread(buf, 1, 188, fp);
        cbTotal += cbRead;
        if ( cbRead != 188 ) {
            break;
        }
        ++ numPckt;
        if ( buf[0] != 0x47 ) {
            ++ numErr;
        }
        if ( (numPckt & 16383) == 0 ) {
            std::cerr   <<  "\r# of Packet = "  <<  numPckt
                        <<  ", total "  <<  cbTotal << " bytes, "
                        <<  "#Error = " <<  numErr;
        }
    }
    std::cerr   <<  "\n# of Packet = "  <<  numPckt
                <<  ", total "  <<  cbTotal << " bytes, "
                <<  "#Error = " <<  numErr;
    std::cerr   <<  std::endl;

    std::cerr   <<  "Total : "  <<  numPckt <<  " packets.\n"
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
