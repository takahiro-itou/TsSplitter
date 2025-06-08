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
**      Type Definitions.
**
**      @file       Common/TsSplitterTypes.h
**/

#if !defined( TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_TYPES_H )
#    define   TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_TYPES_H

#if !defined( TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_PROJECT_H )
#    include    "TsSplitterProject.h"
#endif

#if !defined( TSSPLITTER_SYS_INCLUDED_CSTDINT )
#    include    <cstdint>
#    define   TSSPLITTER_SYS_INCLUDED_CSTDINT
#endif

#if !defined( TSSPLITTER_SYS_INCLUDED_STDDEF_H )
#    include    <stddef.h>
#    define   TSSPLITTER_SYS_INCLUDED_STDDEF_H
#endif


TSSPLITTER_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum class  ErrCode
{
    /**   正常終了。    **/
    SUCCESS                 = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    FAILURE                 = 1,

    /**   無効なインデックス指定。  **/
    INDEX_OUT_OF_RANGE      = 2,

    /**   ファイルオープンエラー。  **/
    FILE_OPEN_ERROR         = 3,

    /**   ファイル入出力エラー。    **/
    FILE_IO_ERROR           = 4,

    /**   不正なファイル形式。      **/
    FILE_INVALID_FORMAT     = 5,
};


//----------------------------------------------------------------
/**
**    読み取り専用バッファ。
**/

typedef     const  void  *      LpcReadBuf;

//--------------------------------------------------------------------------
/**
**    読み書き両用バッファ。
**/

typedef     void  *             LpWriteBuf;

//----------------------------------------------------------------
/**
**    バイト型。
**/

typedef     uint8_t             BtByte;

/**
**    バイト型の読み取り専用バッファ。
**/

typedef     const  BtByte  *    LpcByteReadBuf;

/**
**    バイト型の読み書き両用バッファ。
**/

typedef     BtByte  *           LpByteWriteBuf;

//----------------------------------------------------------------
/**
**    パケット数。
**/

typedef     size_t              PacketCount;

/**
**    サービス ID
**/

typedef     int                 BtServiceId;

/**
**    プログラム ID
**/

typedef     int                 BtProgramId;

/**
**    PMT (Program Map Table) の PID
**/

typedef     BtProgramId         PmtPid;

//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void  *  p)
{
    return ( static_cast<T>(p) );
}

template  <typename  T>
T  pointer_cast(const  void  *  p)
{
    return ( static_cast<T>(p) );
}


TSSPLITTER_NAMESPACE_END

#endif
