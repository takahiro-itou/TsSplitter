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
namespace  Common  {

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
    CPPUNIT_TEST(testComputeCrc1);
    CPPUNIT_TEST(testComputeCrc2);
    CPPUNIT_TEST(testComputeCrc3);
    CPPUNIT_TEST(testCrcConstTable);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testComputeCrc1();
    void  testComputeCrc2();
    void  testComputeCrc3();
    void  testCrcConstTable();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TsCrc32Test );

//========================================================================
//
//    Tests.
//

void  TsCrc32Test::testComputeCrc1()
{
    BtByte  data[] = {
        0x00
    };

    TsCrc32::CrcVal crc = TsCrc32::computeCrc32(data, getArraySize(data));
    CPPUNIT_ASSERT_EQUAL(0x4E08BFB4u, crc);

    return;
}

void  TsCrc32Test::testComputeCrc2()
{
    BtByte  data[] = {
        0xFE
    };

    TsCrc32::CrcVal crc = TsCrc32::computeCrc32(data, getArraySize(data));
    CPPUNIT_ASSERT_EQUAL(0xFB3EE2B7u, crc);

    return;
}

void  TsCrc32Test::testComputeCrc3()
{
    BtByte  data[] = {
        0xFF
    };

    TsCrc32::CrcVal crc = TsCrc32::computeCrc32(data, getArraySize(data));
    CPPUNIT_ASSERT_EQUAL(0xFFFFFF00u, crc);

    return;
}

void  TsCrc32Test::testCrcConstTable()
{
    //  今はまだテーブルが無いので何もしない。  //
    return;
}

}   //  End of namespace  Common
TSSPLITTER_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
