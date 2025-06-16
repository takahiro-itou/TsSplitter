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
**      An Implementation of FileReader class.
**
**      @file       Common/FileReader.cpp
**/

#include    "TsSplitter/Common/FileReader.h"

#include    <cstring>
#include    <iostream>


TSSPLITTER_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.

FileReader::PID_Map     pid_map[8192];

//========================================================================
//
//    FileReader  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

FileReader::FileReader()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

FileReader::~FileReader()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

TsCrc32::CrcVal
FileReader::parsePAT(
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

    const  TsCrc32::CrcVal  crcAct  = TsCrc32::computeCrc32(p + 5, secLen - 4);
    const  TsCrc32::CrcVal  crcRec  = (
            (p[secLen - 4] << 24) | (p[secLen - 3] << 16) |
            (p[secLen - 2] <<  8) | (p[secLen - 1]      )
    );
    printf("CRC(Actual) = %08x, CRC(Record) = %08x\n", crcAct, crcRec);
    return ( crcAct );
}

int
FileReader::parsePMT(
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

size_t
FileReader::parseTsFile(
        const  std::string  &fileName)
{
    size_t  PIDs[8192] = { 0 };
    int     PMTs[65536] = { 0 };
    uint8_t buf[408];
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
    int     numPMTs = 0;

    for ( int i = 0; i < 8192; ++ i ) {
        pid_map[i].sid  = -1;
        pid_map[i].text[0]  = '\0';
    }

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

            for ( int i = 0; i < 65536; ++ i ) {
                if ( PMTs[i] > 0 ) {
                    ++ numPMTs;
                }
            }
            flgPAT  = 0;
        }

        if ( numPMTs >= 1 ) {
            for ( int i = 0; i < 65536; ++ i ) {
                if ( PMTs[i] == pid ) {
                    parsePMT(i, pid, buf, pid_map);
                    -- numPMTs;
                    PMTs[i] |= 65536;
                    break;
                }
            }
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
                    "PID: 0x%04x  Total:%9ld\t%s\n",
                    i, PIDs[i], pid_map[i].text);
            std::cout   <<  text;
        }
    }

    return ( numPckt );
}

size_t
FileReader::parseTsFile(
        FILE *  fp)
{
    return ( 0 );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END
