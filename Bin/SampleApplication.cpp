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

#include    <cstdint>
#include    <cstring>
#include    <iostream>

using   namespace   TSSPLITTER_NAMESPACE;

void
parsePAT(
        const  uint8_t * p,
        int  (& pmt)[65536])
{
    printf("DUMP of PAT:\n");
    for ( int y = 0; y < 188; y += 16 ) {
        printf("%02x:", y);
        for ( int x = 0; x < 16; ++ x ) {
            int idx = y + x;
            if ( idx > 188 ) { break; }
            printf(" %02x", p[idx]);
        }
        printf("\n");
    }
    printf("\n");

    for ( int pg = 0; pg < 65536; ++ pg ) {
        pmt[pg] = -1;
    }

    int secLen  = ((p[4 + 2] << 8) & 0x0F00) | (p[4 + 3] & 0x00FF);
    int program_number;
    int program_PMT;
    printf(" PAT section length : %d\n", secLen);
    for ( int idx = 13; idx < 4 + 1 + secLen - 4; idx += 4 ) {
        program_number  = ((p[idx] << 8) & 0xFF00) | (p[idx+1] & 0x00FF);
        program_PMT = ((p[idx+2] << 8) & 0x1F00) | (p[idx+3] & 0x00FF);
        printf("  0x%04x(%05d), PMT: 0x%04x\n",
               program_number, program_number, program_PMT);
        pmt[program_number] = program_PMT;
    }
}

size_t
parseTsFile(
        const  std::string  &fileName)
{
    size_t  PIDs[8192] = { 0 };
    int     PMTs[65536] = { 0 };
    uint8_t buf[204];
    char    text[1024];

    FILE *  fp  = fopen(fileName.c_str(), "rb");
    if ( fp == nullptr ) {
        return ( 0 );
    }
    std::cerr   <<  "Open : " <<  fileName  <<  std::endl;

    size_t  cbRead;
    size_t  numPckt = 0;
    size_t  cbTotal = 0;
    size_t  numErr  = 0;
    size_t  numScr  = 0;

    int     flgPAT  = 1;

    memset(PIDs, 0, sizeof(PIDs));
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
        if ( buf[3] & 0xC0 ) {
            ++ numScr;
        }

        const  int  pid = ((buf[1] << 8) & 0x1F00) | (buf[2] & 0x00FF);
        ++ PIDs[pid];

        if ( flgPAT && pid == 0x0000 ) {
            parsePAT(buf, PMTs);
            flgPAT  = 0;
        }

        if ( (numPckt & 65535) == 0 ) {
            std::cerr   <<  "\r# of Packet = "  <<  numPckt
                        <<  ", total "  <<  cbTotal << " bytes, "
                        <<  "#Error = " <<  numErr
                        <<  ", #Scramble = "    <<  numScr;

        }
    }
    std::cerr   <<  "\r# of Packet = "  <<  numPckt
                <<  ", total "  <<  cbTotal << " bytes, "
                <<  "#Error = " <<  numErr
                <<  ", #Scramble = "  <<  numScr;
    std::cerr   <<  std::endl;

    std::cerr   <<  "Total : "  <<  numPckt <<  " packets.\n"
                <<  "Last Read = "  <<  cbRead  <<  " bytes."
                <<  std::endl;
    fclose(fp);

    for ( int i = 0; i < 8192; ++ i ) {
        if ( PIDs[i] ) {
            sprintf(text,
                    "PID: 0x%04x  Total:%9ld\n",
                    i, PIDs[i]);
            std::cout   <<  text;
        }
    }

    return ( numPckt );
}

int  main(int argc, char * argv[])
{
    if ( argc >= 2 ) {
        parseTsFile(argv[1]);
    }

    return ( 0 );
}
