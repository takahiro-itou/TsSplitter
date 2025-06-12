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

#include    "TsSplitter/Common/TsSplitterTypes.h"
#include    "TsSplitter/Common/FileReader.h"

#include    <cstdint>
#include    <cstring>
#include    <iostream>

using   namespace   TSSPLITTER_NAMESPACE;

struct  PID_Map  {
    int     sid;
    int     stream_type;
    char    text[256];
};

PID_Map     pid_map[8192];
Common::FileReader  fr;

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
            if ( idx >= 188 ) { break; }
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

int
parsePMT(
        const  int  sid,
        const  int  pmt_pid,
        const  uint8_t *  pmt,
        PID_Map  (& pid_map)[8192])
{
    printf("SID = 0x%04x(%05d), PMT PID = 0x%04x\n",
           sid, sid, pmt_pid);
    printf("DUMP of PMT:\n");
    for ( int y = 0; y < 188; y += 16 ) {
        printf("%02x:", y);
        for ( int x = 0; x < 16; ++ x ) {
            int idx = y + x;
            if ( idx >= 188 ) { break; }
            printf(" %02x", pmt[idx]);
        }
        printf("\n");
    }
    printf("\n");

    int secLen  = ((pmt[6] << 8) & 0x0F00) | (pmt[4 + 3] & 0x00FF);
    int n1  = ((pmt[15] << 8) & 0x0F00) | (pmt[16] & 0x00FF);
    printf("  PMT section length : %d\n", secLen);
    printf("  PMT Program Info Length : %d\n", n1);
    char    text[128];

    int numComp = 0;
    int pos = n1 + 17;
    while ( pos < secLen - 4 ) {
        int stream_type = pmt[pos] & 0x00FF;
        int element_pid = ((pmt[pos+1] << 8) & 0x1F00) | (pmt[pos+2] & 0x00FF);
        int es_info_len = ((pmt[pos+3] << 8) & 0x0F00) | (pmt[pos+4] & 0x00FF);
        switch ( stream_type ) {
        case  0x01:
            sprintf(text, "MPEG1 VIDEO");
            break;
        case  0x02:
            sprintf(text, "MPEG2 VIDEO");
            break;
        case  0x06:
            sprintf(text, "字幕");
            break;
        case  0x0d:
            sprintf(text, "データカルーセル");
            break;
        case  0x0f:
            sprintf(text, "MPEG2 AAC");
            break;
        case  0x1b:
            sprintf(text, "H.264 ワンセグ");
            break;
        default:
            sprintf(text, "UNK");
            break;
        }
        printf("  PID: 0x%04x, InfoLen:%d, Type:%d, %s\n",
               element_pid, es_info_len, stream_type, text);

        if ( pid_map[element_pid].sid != -1 ) {
            printf("WARNING! Duplicate PID : 0x%04x, SID=%d, PrevSID=%d\n",
                   element_pid, sid, pid_map[element_pid].sid);
        } else {
            pid_map[element_pid].sid    = sid;
            sprintf(pid_map[element_pid].text,
                    "Service:0x%04x(%05d), type=%d, %s",
                    sid, sid, stream_type, text);
        }

        ++  numComp;
        pos += (es_info_len + 5);
    }

    return ( numComp );
}

void
testCrc32()
{
#if 0
    BtByte  buf[188] = {
        0x00, 0xb0, 0x1d, 0x7f, 0xd1, 0xc1, 0x00, 0x00,
        0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xe1, 0xf0,
        0x08, 0x09, 0xe3, 0xf0, 0x08, 0x0a, 0xe4, 0xf0,
        0x09, 0x88, 0xff, 0xc8, 0xcd, 0xd4, 0xea, 0xe8,
    };
#endif

    BtByte  buf[188] = {
        0xff
    };

    uint32_t crc = 0xFFFFFFFF;
    for ( int i = 0; i < 1 ; ++ i ) {
        BtByte  dat = buf[i];
        for ( int b = 0; b < 8; ++ b ) {
            if ( crc & 0x80000000 ) {
                crc = (crc << 1) ^ 0x04C11DB7;
            } else {
                crc = (crc << 1);
            }
            if ( dat & 0x80 ) {
                crc ^= 0x04C11DB7;
            }
            dat <<= 1;
        }
    }
    printf("CRC = %08x\n", crc);
}

int  main(int argc, char * argv[])
{
    testCrc32();

    if ( argc >= 2 ) {
        fr.parseTsFile(argv[1]);
    }

    return ( 0 );
}
