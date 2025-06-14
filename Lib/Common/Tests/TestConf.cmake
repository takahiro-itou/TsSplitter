
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(NAME   TsCrc32Test
    COMMAND  $<TARGET_FILE:TsCrc32Test>
)

add_test(NAME   TsSplitterProjectTest
    COMMAND  $<TARGET_FILE:TsSplitterProjectTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(TsCrc32Test              TsCrc32Test.cpp)
add_executable(TsSplitterProjectTest    TsSplitterProjectTest.cpp)

