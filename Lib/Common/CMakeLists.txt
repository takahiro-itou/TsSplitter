
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(module_title        "Common")

Include (${common_cmake_dir}/BuildCommon/ConfigModule.cmake)
Include (${common_cmake_dir}/BuildCommon/ConfigTarget.cmake)

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(library_source_files
       FileReader.cpp
       FileWriter.cpp
       SampleDocument.cpp
)

set(inclib_header_files
        ${inclib_source_dir}/FileReader.h
        ${inclib_source_dir}/FileWriter.h
        ${inclib_source_dir}/SampleDocument.h
        ${inclib_source_dir}/TsSplitterProject.h
        ${inclib_source_dir}/TsSplitterTypes.h
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
