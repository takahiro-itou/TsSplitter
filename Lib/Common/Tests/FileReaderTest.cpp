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
**      An Implementation of Test Case 'FileReader'.
**
**      @file       Common/Tests/FileReaderTest.cpp
**/

#include    "TestDriver.h"
#include    "TsSplitter/Common/FileReader.h"


TSSPLITTER_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    FileReaderTest  class.
//
/**
**    クラス FileReader  の単体テスト。
**/

class  FileReaderTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(FileReaderTest);
    CPPUNIT_TEST(testFileReader);
    CPPUNIT_TEST(testOffsetStack);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testFileReader();
    void  testOffsetStack();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FileReaderTest );

//========================================================================
//
//    Tests.
//

void  FileReaderTest::testFileReader()
{
    FileReader  testee;
    return;
}

void  FileReaderTest::testOffsetStack()
{
    FileReader  testee;

    CPPUNIT_ASSERT_EQUAL(0UL, testee.getCurrentFileOffset());

    CPPUNIT_ASSERT_EQUAL(188UL, testee.setCurrentFileOffset(188));
    CPPUNIT_ASSERT_EQUAL(188UL, testee.getCurrentFileOffset());

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
