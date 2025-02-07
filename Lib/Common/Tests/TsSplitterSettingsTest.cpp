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
**      An Implementation of Test Case 'TsSplitterSettings'.
**
**      @file       Common/Tests/TsSplitterSettingsTest.cpp
**/

#include    "TestDriver.h"
#include    "TsSplitter/Common/TsSplitterSettings.h"


SAMPLE_NAMESPACE_BEGIN

//========================================================================
//
//    TsSplitterSettingsTest  class.
//
/**
**    クラス TsSplitterSettings の単体テスト。
**/

class  TsSplitterSettingsTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TsSplitterSettingsTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TsSplitterSettingsTest );

//========================================================================
//
//    Tests.
//

void  TsSplitterSettingsTest::testNameSpace()
{
    return;
}

SAMPLE_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
