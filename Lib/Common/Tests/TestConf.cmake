
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   SampleSettingsTest
    COMMAND  $<TARGET_FILE:SampleSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(SampleSettingsTest       SampleSettingsTest.cpp)
