# SpcLibcurlSample

インターネット上のリソースにアクセスする手段は無数にありますが、
1つの手法として libcurl とそのラッパーライブラリを用いての GET 例を示します。

[SpcBaseCode.cpp] を参照ください。

プロジェクトのプロパティから参照、設定できるコンパイル、リンク周りのオプションは、
Palmi-Dev 内に配置されているライブラリを用いるにあたって重要です。
併せて参照ください。

また、システムソフトウェア ver. 4.4.1 現在、libcurl はヘッダーファイルが開発環境内に配置されていないため、
SPCプロジェクト内にヘッダーファイルを配置する必要がある点に留意ください。


## 関連リソース

* libcurl: https://curl.haxx.se/
    * https://curl.haxx.se/docs/copyright.html
    * Palmi-Dev にビルド済リソースが配置済、ヘッダファイルを同梱
* TinyCurl: https://github.com/asashnov/tinycurl
    * License: Unlicensed (Public Domain)
    * ソースコードの複製を同梱
* picojson: https://github.com/kazuho/picojson
    * https://github.com/kazuho/picojson/blob/master/LICENSE
    * ソースコードの複製を同梱
