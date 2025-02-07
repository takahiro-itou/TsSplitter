
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   TsSplitterSettingsTest
    COMMAND  $<TARGET_FILE:TsSplitterSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(TsSplitterSettingsTest   TsSplitterSettingsTest.cpp)
