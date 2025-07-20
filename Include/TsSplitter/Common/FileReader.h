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

#if !defined( TSSPLITTER_SYS_STL_INCLUDED_STACK )
#    include    <stack>
#    define   TSSPLITTER_SYS_STL_INCLUDED_STACK
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

private:

    typedef     FileReader      This;

    /**
    **    ファイルアクセス位置（ファイルオフセット）のスタック型。
    **/
    typedef     std::stack<FileLength>      OffsetStack;

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
    /**   特定の Program ID を持つパケットを検索する。
    **
    **  @param [in] pid   検索する PID
    **  @return     見つかったパケット。
    **/
    PacketData
    findNextPacket(
            const  BtProgramId  pid);

    //----------------------------------------------------------------
    /**   特定の Program ID を持つパケットを検索する。
    **
    **  @param [in] pid       検索する PID
    **  @param[out] result    検索結果を格納する変数。
    **  @return     見つかったパケットの数。
    **/
    PacketCount
    findPacketsWithPid(
            const  BtProgramId  pid,
            FindResult        & result);

    //----------------------------------------------------------------
    /**
    **
    **/
    TsCrc32::CrcVal
    parsePAT(
            const  uint8_t * p,
            const  TsCrc32::CrcVal  prvCrc,
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

    //----------------------------------------------------------------
    /**   スタックからファイルアクセス位置を取り出す。
    **
    **/
    FileLength
    popFileOffset();

    //----------------------------------------------------------------
    /**   スタックにファイルアクセス位置を詰む。
    **
    **/
    void
    pushFileOffset();

    //----------------------------------------------------------------
    /**   特定の Program ID を持つパケットを読み出す。
    **
    **  @param [in] pid   検索する PID
    **  @return     見つかったパケット。
    **/
    PacketData
    readCompletePackets(
            const  BtProgramId  pid);

    //----------------------------------------------------------------
    /**   入力を PID  毎のファイルに分割する。
    **
    **/
    PacketCount
    splitTsPid(
            const  std::string  &fileName,
            const  std::string  &outPrefix);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   次のファイルアクセス位置を取得する。
    **
    **  @return     現在の値。
    **/
    FileLength
    getCurrentFileOffset()  const
    {
        return ( this->m_curFilePos );
    }

    //----------------------------------------------------------------
    /**   次のファイルアクセス位置を設定する。
    **
    **  @param [in] posNew    設定する値。
    **/
    FileLength
    setCurrentFileOffset(
            const   FileLength  posNew);

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//
private:

    void
    dumpCurrentPacket();

    void
    dumpPacket(
            const  PacketData  &packet);

    //----------------------------------------------------------------
    /**   次のパケットを読みだす。
    **
    **  @param[out] packet    読み出したパケット。
    **  @return     読みだしたバイト数。
    **/
    FileLength
    readNextPacket(
            PacketData  &packet);

//========================================================================
//
//    Member Variables.
//
private:

    /**   入力ストリーム。  **/
    FILE  *         m_fp;

    /**   現在のファイルアクセス位置。  **/
    FileLength      m_curFilePos;

    /**   現在読み出した総バイト数。    **/
    FileLength      m_cbTotalRead;

    /**   最後に読みだしたパケット。    **/
    PacketData      m_lastPacket;

    /**   現在読み出した総パケット数。  **/
    PacketCount     m_numPackets;

    /**   ファイルオフセットスタック。  **/
    OffsetStack     m_offsetStack;

//========================================================================
//
//    Other Features.
//
private:
    FileReader          (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   FileReaderTest;
};

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END

#endif
