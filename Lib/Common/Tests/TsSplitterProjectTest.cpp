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
**      An Implementation of Test Case 'TsSplitterProject'.
**
**      @file       Common/Tests/TsSplitterProjectTest.cpp
**/

#include    "TestDriver.h"
#include    "TsSplitter/Common/TsSplitterProject.h"


TSSPLITTER_NAMESPACE_BEGIN

//========================================================================
//
//    TsSplitterProjectTest  class.
//
/**
**    クラス TsSplitterProject の単体テスト。
**/

class  TsSplitterProjectTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TsSplitterProjectTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TsSplitterProjectTest );

//========================================================================
//
//    Tests.
//

void  TsSplitterProjectTest::testNameSpace()
{
    return;
}

TSSPLITTER_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
