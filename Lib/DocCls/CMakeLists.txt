
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(module_title        "DocCls")

Include (${common_cmake_dir}/BuildCommon/ConfigModule.cmake)
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(library_source_files
        TsFileSplitter.cpp
)

set(inclib_header_files
        ${inclib_source_dir}/TsFileSplitter.h
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${common_cmake_dir}/BuildCommon/BuildLib.cmake)
Include (${common_cmake_dir}/BuildCommon/Install.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

Add_SubDirectory (Tests)

