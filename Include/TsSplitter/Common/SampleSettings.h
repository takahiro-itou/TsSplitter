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
**      プロジェクトの設定。
**
**      @file       Common/SampleSettings.h
**/

#if !defined( TSSPLITTER_COMMON_INCLUDED_SAMPLE_SETTINGS_H )
#    define   TSSPLITTER_COMMON_INCLUDED_SAMPLE_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( TSSPLITTER_USE_PRE_CONFIGURED_MSVC )
#    include    "TsSplitter/.Config/PreConfigSample.msvc.h"
#else
#    include    "TsSplitter/.Config/ConfiguredTsSplitter.h"
#endif

SAMPLE_NAMESPACE_BEGIN

/**
**    ダミーの型宣言。
**/

typedef     int     CommonType;

SAMPLE_NAMESPACE_END

#endif
