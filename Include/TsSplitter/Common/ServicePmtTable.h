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
**      An Interface of ServicePmtTable class.
**
**      @file       Common/ServicePmtTable.h
**/

#if !defined( TSSPLITTER_COMMON_INCLUDED_SERVICE_PMT_TABLE_H )
#    define   TSSPLITTER_COMMON_INCLUDED_SERVICE_PMT_TABLE_H

#if !defined( TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_TYPES_H )
#    include    "TsSplitterTypes.h"
#endif


TSSPLITTER_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    ServicePmtTable  class.
//

class  ServicePmtTable
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
    ServicePmtTable();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ServicePmtTable();

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
    friend  class   ServicePmtTableTest;
};

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END

#endif
