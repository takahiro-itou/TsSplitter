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
**      An Implementation of Test Case 'TsFileSplitter'.
**
**      @file       DocCls/Tests/TsFileSplitterTest.cpp
**/

#include    "TestDriver.h"
#include    "TsSplitter/DocCls/TsFileSplitter.h"


TSSPLITTER_NAMESPACE_BEGIN
namespace  DocCls  {

//========================================================================
//
//    TsFileSplitterTest  class.
//
/**
**    クラス TsFileSplitter  の単体テスト。
**/

class  TsFileSplitterTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TsFileSplitterTest);
    CPPUNIT_TEST(testTsFileSplitter);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testTsFileSplitter();

private:
    typedef     TsFileSplitter  Testee;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TsFileSplitterTest );

//========================================================================
//
//    Tests.
//

void  TsFileSplitterTest::testTsFileSplitter()
{
    Testee  testee;
    return;
}

}   //  End of namespace  DocCls
TSSPLITTER_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
