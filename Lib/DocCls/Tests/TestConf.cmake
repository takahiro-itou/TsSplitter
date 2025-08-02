
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   TsFileSplitterTest
    COMMAND  $<TARGET_FILE:TsFileSplitterTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(TsFileSplitterTest       TsFileSplitterTest.cpp)

