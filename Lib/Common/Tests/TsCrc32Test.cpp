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
**      An Implementation of Test Case 'TsCrc32'.
**
**      @file       Common/Tests/TsCrc32Test.cpp
**/

#include    "TestDriver.h"
#include    "TsSplitter/Common/TsCrc32.h"


TSSPLITTER_NAMESPACE_BEGIN

//========================================================================
//
//    TsCrc32Test  class.
//
/**
**    クラス TsCrc32  の単体テスト。
**/

class  TsCrc32Test : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TsCrc32Test);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TsCrc32Test );

//========================================================================
//
//    Tests.
//

void  TsCrc32Test::testNameSpace()
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
