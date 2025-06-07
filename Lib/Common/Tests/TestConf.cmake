
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   TsSplitterProjectTest
    COMMAND  $<TARGET_FILE:TsSplitterProjectTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(TsSplitterProjectTest    TsSplitterProjectTest.cpp)

