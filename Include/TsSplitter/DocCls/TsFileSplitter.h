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
**      An Interface of TsFileSplitter class.
**
**      @file       DocCls/TsFileSplitter.h
**/

#if !defined( TSSPLITTER_DOCCLS_INCLUDED_TS_FILE_SPLITTER_H )
#    define   TSSPLITTER_DOCCLS_INCLUDED_TS_FILE_SPLITTER_H

#if !defined( TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_TYPES_H )
#    include    "TsSplitter/Common/TsSplitterTypes.h"
#endif


TSSPLITTER_NAMESPACE_BEGIN
namespace  DocCls  {

//========================================================================
//
//    TsFileSplitter  class.
//

class  TsFileSplitter
{

//========================================================================
//
//    Internal Type Definitions.
//

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
    TsFileSplitter();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TsFileSplitter();

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
    friend  class   TsFileSplitterTest;
};

}   //  End of namespace  DocCls
TSSPLITTER_NAMESPACE_END

#endif
