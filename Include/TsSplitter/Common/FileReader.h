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
**      An Interface of FileReader class.
**
**      @file       Common/FileReader.h
**/

#if !defined( TSSPLITTER_COMMON_INCLUDED_FILE_READER_H )
#    define   TSSPLITTER_COMMON_INCLUDED_FILE_READER_H

#if !defined( TSSPLITTER_COMMON_INCLUDED_TSSPLITTER_TYPES_H )
#    include    "TsSplitterTypes.h"
#endif

#if !defined( TSSPLITTER_COMMON_INCLUDED_TS_CRC32_H )
#    include    "TsCrc32.h"
#endif

#if !defined( TSSPLITTER_SYS_STL_INCLUDED_STRING )
#    include    <string>
#    define   TSSPLITTER_SYS_STL_INCLUDED_STRING
#endif


TSSPLITTER_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    FileReader  class.
//

class  FileReader
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    struct  PID_Map  {
        int     sid;
        int     stream_type;
        char    text[256];
    };

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
    FileReader();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~FileReader();

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
    /**
    **
    **/
    void
    parsePAT(
            const  uint8_t * p,
            int  (& pmt)[65536]);

    int
    parsePMT(
            const  int  sid,
            const  int  pmt_pid,
            const  uint8_t *  pmt,
            PID_Map  (& pid_map)[8192]);

    size_t
    parseTsFile(
            const  std::string  &fileName);

    size_t
    parseTsFile(
            FILE *  fp);

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
    friend  class   FileReaderTest;
};

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END

#endif
