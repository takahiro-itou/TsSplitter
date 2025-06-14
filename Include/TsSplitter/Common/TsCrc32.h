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
**      An Interface of TsCrc32 class.
**
**      @file       Common/TsCrc32.h
**/

#if !defined( TSSPLITTER_COMMON_INCLUDED_TS_CRC32_H )
#    define   TSSPLITTER_COMMON_INCLUDED_TS_CRC32_H

#if !defined( TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_TYPES_H )
#    include    "TsSplitterTypes.h"
#endif


TSSPLITTER_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    TsCrc32  class.
//

class  TsCrc32
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     uint32_t    CrcVal;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    TsCrc32();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TsCrc32();

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
public:

    //----------------------------------------------------------------
    /**   CRC の値を計算する。
    **
    **  @param [in] inBuf   入力データのアドレス。
    **  @param [in] cbBuf   入力データのバイト数。
    **/
    static  const   CrcVal
    computeCrc32(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf);

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

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   TsCrc32Test;
};

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END

#endif
