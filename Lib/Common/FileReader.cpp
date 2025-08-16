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
#include    <vector>


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
    : m_fp(nullptr),
      m_curFilePos(0),
      m_cbTotalRead(0),
      m_lastPacket(),
      m_numPackets(0),
      m_offsetStack()
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

//----------------------------------------------------------------
//    特定の Program ID を持つパケットを検索する。
//

PacketData
FileReader::findNextPacket(
        const  BtProgramId  pid)
{
    return ( this->m_lastPacket );
}

//----------------------------------------------------------------
//    特定の Program ID を持つパケットを検索する。
//

PacketCount
FileReader::findPacketsWithPid(
        const  BtProgramId  pid,
        FindResult        & result)
{
    FindResult  tmp = { 0 };
    PacketData  packet;
    size_t      cbRead;
    size_t      payloadSize = 0;

    for (;;) {
        cbRead  = readNextPacket(packet);
        if ( cbRead != 188 ) {
            break;
        }
        if ( packet.phProgramId != pid ) {
            //  PID が異なるので無視する。  //
            continue;
        }

        if ( packet.puStartIdctr ) {
            //  このパケットに新しいペイロードが含まれる。  //
        }

        ++ tmp.numFind;
    }

    result  = tmp;
    return ( result.numFind = tmp.numFind );
}

//----------------------------------------------------------------

TsCrc32::CrcVal
FileReader::parsePAT(
        const  uint8_t * p,
        const  TsCrc32::CrcVal  prvCrc,
        int  (& pmt)[65536])
{
    const  int  secLen  = ((p[4 + 2] << 8) & 0x0F00) | (p[4 + 3] & 0x00FF);
    const  TsCrc32::CrcVal  crcAct  = TsCrc32::computeCrc32(p + 5, secLen + 3 - 4);
    const  TsCrc32::CrcVal  crcRec  = (
            (p[secLen + 5 + 3 - 4] << 24) | (p[secLen + 5 + 3 - 3] << 16) |
            (p[secLen + 5 + 3 - 2] <<  8) | (p[secLen + 5 + 3 - 1]      )
    );

    if ( crcAct == prvCrc ) {
        return ( crcAct );
    }

    printf("DUMP of PAT:\n");
    dumpCurrentPacket();

    for ( int pg = 0; pg < 65536; ++ pg ) {
        pmt[pg] = -1;
    }

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
    printf("SID = 0x%04x(%05d), PMT PID = 0x%04x @"
           " 0x%08" PRIx64 ", %08" PRIx64 "\n",
           sid, sid, pmt_pid,
           this->m_cbTotalRead - 188, this->m_numPackets);
    printf("DUMP of PMT:\n");
    dumpCurrentPacket();

    if ( !(pmt[1] & 0x40) ) {
        printf("Payload Unit Start Indicator = 0\n");
        return ( -1 );
    }

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
    //uint8_t buf[408];
    char    text[1024];

    FILE *  fp  = fopen(fileName.c_str(), "rb");
    if ( fp == nullptr ) {
        return ( 0 );
    }
    this->m_fp  = fp;
    std::cerr   <<  "Open : " <<  fileName  <<  std::endl;

    size_t  cbRead;
    size_t  numPckt = 0;
    size_t  cbTotal = 0;
    size_t  numErr  = 0;
    size_t  numScr  = 0;

    int     flgPAT  = 1;
    TsCrc32::CrcVal crcPAT  = 0;
    TsCrc32::CrcVal crcPrv  = 0;
    int     numPMTs = 0;

    for ( int i = 0; i < 8192; ++ i ) {
        pid_map[i].sid  = -1;
        pid_map[i].text[0]  = '\0';
    }

    size_t  numShow = 0;

    memset(PIDs, 0, sizeof(PIDs));
    for (;;) {
        cbRead  = readNextPacket(this->m_lastPacket);
        if ( cbRead != 188 ) {
            break;
        }

        LpcByteReadBuf  const   buf = this->m_lastPacket.buf;
        if ( buf[0] != 0x47 ) {
            ++ numErr;
        }
        if ( buf[3] & 0xC0 ) {
            ++ numScr;
        }

        const  int  pid = ((buf[1] << 8) & 0x1F00) | (buf[2] & 0x00FF);
        ++ PIDs[pid];

        // if ( this->m_lastPacket.payloadStart != 0 ) {
        //     dumpCurrentPacket();
        // }

        if ( pid == 0x0000 ) {
            crcPrv  = crcPAT;
            crcPAT  = parsePAT(buf, crcPrv, PMTs);

            if ( crcPAT != crcPrv ) {
                for ( int i = 0; i < 65536; ++ i ) {
                    if ( PMTs[i] > 0 ) {
                        ++ numPMTs;
                    }
                }
                std::cerr   <<  "\nDetected PAT changed."   <<  std::endl;
            }
        }

        if ( numPMTs >= 1 ) {
            for ( int i = 0; i < 65536; ++ i ) {
                if ( PMTs[i] == pid ) {
                    parsePMT(i, pid, buf, pid_map);
                    -- numPMTs;
                    //  PMTs[i] |= 65536;
                    ++ numShow;
                    break;
                }
            }
        }

        cbTotal += cbRead;
        ++ numPckt;
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
    this->m_fp  = nullptr;
    fclose(fp);

    for ( int i = 0; i < 8192; ++ i ) {
        if ( PIDs[i] ) {
            sprintf(text,
                    "PID: 0x%04" PRIx32 "  Total:%9" PRIx64 "\t%s\n",
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

//----------------------------------------------------------------
//    スタックからファイルアクセス位置を取り出す。
//

FileLength
FileReader::popFileOffset()
{
    FileLength  pos = this->m_offsetStack.top();
    this->m_offsetStack.pop();
    return  this->setCurrentFileOffset(pos);
}

//----------------------------------------------------------------
//    スタックにファイルアクセス位置を詰む。
//

void
FileReader::pushFileOffset()
{
    this->m_offsetStack.push(this->m_curFilePos);
}

//----------------------------------------------------------------
//    特定の Program ID を持つパケットを読み出す。
//

PacketData
FileReader::readCompletePackets(
        const  BtProgramId  pid)
{
    return ( this->m_lastPacket );
}

//----------------------------------------------------------------
//    入力を PID  毎のファイルに分割する。
//

PacketCount
FileReader::splitTsPid(
        const  std::string  &fileName,
        const  std::string  &outPrefix)
{
    std::vector<FILE *>     pid_fp;
    std::vector<int64_t>    pid_skip;
    std::vector<int>        pid_cnts;

    pid_fp.clear();
    pid_skip.clear();
    pid_cnts.clear();

    pid_fp.resize(8192);
    pid_skip.resize(8192);
    pid_cnts.resize(8192);

    for ( BtProgramId i = 0; i < 8192; ++ i ) {
        pid_fp[i]   = nullptr;
        pid_skip[i] = 0;
        pid_cnts[i] = 0;
    }

    FILE *  fp  = fopen(fileName.c_str(), "rb");
    if ( fp == nullptr ) {
        return ( 0 );
    }
    this->m_fp  = fp;
    std::cerr   <<  "Open : " <<  fileName  <<  std::endl;

    size_t  cbRead;
    size_t  numPckt = 0;
    size_t  cbTotal = 0;
    size_t  numErr  = 0;
    size_t  numScr  = 0;

    PacketData  packet;

    for (;;) {
        cbRead  = readNextPacket(packet);
        if ( cbRead != 188 ) {
            break;
        }

        LpcByteReadBuf  const   buf = packet.buf;
        if ( buf[0] != 0x47 ) {
            ++ numErr;
        }
        if ( buf[3] & 0xC0 ) {
            ++ numScr;
        }
        const  BtProgramId  pid = packet.phProgramId;

        if ( pid_fp[pid] == nullptr ) {
            char    outName[1024];
            sprintf(outName, "%s-%04x-%d.ts",
                    outPrefix.c_str(), pid, pid_cnts[pid]
            );
            pid_fp[pid] = fopen(outName, "wb");
            fprintf(stderr,
                    "\nOpen PID %s\n", outName);
            ++ pid_cnts[pid];
            pid_skip[pid]   = 0;
        }

        fwrite(buf, 1, cbRead, pid_fp[pid]);
        pid_skip[pid]   = 0;

        for ( BtProgramId i = 0; i < 8192; ++ i ) {
            if ( pid_fp[i] == nullptr ) {
                continue;
            }
            if ( ++ pid_skip[i] >= 8388608 ) {
                //  しばらく出現していない ID は一旦閉じる  //
                fprintf(stderr,
                        "\nClose PID %04x\n", i);
                fclose(pid_fp[i]);
                pid_fp[i]   = nullptr;
                pid_skip[i] = 0;
            }
        }

        cbTotal += cbRead;
        ++ numPckt;
        if ( (numPckt & 65535) == 0 ) {
            std::cerr   <<  "\r# of Packet = "  <<  numPckt
                        <<  ", total "  <<  cbTotal << " bytes, "
                        <<  "#Error = " <<  numErr
                        <<  ", #Scramble = "    <<  numScr;

        }
    }

    this->m_fp  = nullptr;
    fclose(fp);

    for ( BtProgramId i = 0; i < 8192; ++ i ) {
        if ( pid_fp[i] != nullptr ) {
            fclose(pid_fp[i]);
        }
        pid_fp[i]   = nullptr;
    }

    return ( numPckt );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    次のファイルアクセス位置を設定する。
//

FileLength
FileReader::setCurrentFileOffset(
        const   FileLength  posNew)
{
    if ( this->m_fp != nullptr ) {
        fseek(this->m_fp, static_cast<long>(posNew), SEEK_SET);
    }
    return ( this->m_curFilePos  = posNew );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

void
FileReader::dumpCurrentPacket()
{
    return  dumpPacket(this->m_lastPacket);
}

void
FileReader::dumpPacket(
        const  PacketData  &packet)
{
    LpcByteReadBuf const p  = packet.buf;

    printf("Offet: 0x%08" PRIx64 "\n", packet.offset);
    for ( int y = 0; y < 188; y += 16 ) {
        printf("%02x:", y);
        for ( int x = 0; x < 16; ++ x ) {
            int idx = y + x;
            if ( idx >= 188 ) { break; }
            printf(" %02x", p[idx]);
        }
        printf("\n");
    }
    printf("Header.TransportErrorIndicator   = 0x%02x\n",
           packet.tsErrorIdctr ? 0x80 : 0);
    printf("Header.PayloadUnitStartIndicator = 0x%02x\n",
           packet.puStartIdctr ? 0x40 : 0);
    printf("Header.TransportPriority         = 0x%02x\n",
           packet.tspPriority);
    printf("Header.PID                       = 0x%04x\n",
           packet.phProgramId);
    printf("Header.TransportScrambleControl  = %d\n",
           packet.ctlScramble);
    printf("Header.AdaptationFieldControl    = %1x\n",
           packet.ctlAdaptFld);
    printf("Header.ContinuityCounter         = %d\n",
           packet.contCounter);
    printf("Payload Start Position           = %d\n",
           packet.payloadStart);
    printf("\n");

    return;
}

//----------------------------------------------------------------
//    次のパケットを読みだす。
//

FileLength
FileReader::readNextPacket(
        PacketData  &packet)
{
    const   FileLength  cbRead =
        fread(packet.buf, 1, 188, this->m_fp);

    LpcByteReadBuf  const   buf = packet.buf;
    const  BtProgramId  pid = ((buf[1] << 8) & 0x1F00) | (buf[2] & 0x00FF);

    packet.offset   = this->m_curFilePos;

    packet.headSyncByte = buf[0];
    packet.tsErrorIdctr = (buf[1] & 0x80);
    packet.puStartIdctr = (buf[1] & 0x40);
    packet.tspPriority  = (buf[1] & 0x20);
    packet.phProgramId  =  pid;
    packet.ctlScramble  = (buf[3] >> 6) & 0x03;
    packet.ctlAdaptFld  = (buf[3] >> 4) & 0x03;
    packet.contCounter  = (buf[3]     ) & 0x0F;

    BtByte  plStart = 4;
    BtByte  adptLen = 0;

    //  アダプテーションフィールドの解析。  //
    if ( packet.ctlAdaptFld & 0x02 ) {
        adptLen = buf[4];
        ++ plStart;
    }
    packet.adaptation.adaptationFieldLength = adptLen;
    if ( adptLen > 0 ) {
        packet.adptBuf  = packet.packets + plStart;
        plStart += adptLen;
    }

    //  ペイロードの開始位置を求める。  //
    if ( packet.puStartIdctr ) {
        if ( buf[plStart] != 0 ) {
            // fprintf(stderr, "Not Implemented: Payload Start != 0 @[%d], %d\n",
            //         plStart, buf[plStart]
            // );
        }
        packet.payloadStart = buf[plStart];
        ++ plStart;
    }

    packet.packets  = buf;
    packet.payload  = packet.packets + plStart;

    this->m_curFilePos  += cbRead;
    ++  this->m_numPackets;

    return ( cbRead );
}

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END
