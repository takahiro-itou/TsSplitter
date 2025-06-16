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
**      An Implementation of TsCrc32 class.
**
**      @file       Common/TsCrc32.cpp
**/

#include    "TsSplitter/Common/TsCrc32.h"


TSSPLITTER_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    TsCrc32  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

TsCrc32::TsCrc32()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

TsCrc32::~TsCrc32()
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
//    CRC の値を計算する。
//

const   TsCrc32::CrcVal
TsCrc32::computeCrc32(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf)
{
    const   LpcByteReadBuf  pcData  = static_cast<LpcByteReadBuf>(inBuf);

    CrcVal  crc = 0xFFFFFFFF;

    for ( FileLength i = 0; i < cbBuf ; ++ i ) {
        BtByte  dat = pcData[i];
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

    return ( crc );
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

//========================================================================
//
//    Member Variables.
//

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END
