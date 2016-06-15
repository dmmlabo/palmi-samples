/**
* @note 本プログラムの最終行にある変数宣言は非常に重要です。
* SPCフレームワークは、「spcApp」と言う固定の変数に対して処理を行うように作られています。
*/

#include "spc/spcbase2.h"
#include "SpcBaseCode.h"

#include "tinycurl.h"
#include <curl/curl.h>
#include "picojson.h"

using namespace std;
using namespace spc;

// Palmi の SPC の基本は、起動したら Palmi が何かして、終了する、です。
// なので、onInitialize() で何か処理して、終了してしまえばいいのです。
/**
* @brief アプリケーション初期化イベント。
*
* アプリケーションの実行開始時に呼び出されます。
*/
void spc_libcurl_sample::onInitialize()
{
	SPC_LOG_INFO("onInitialize");

	long callResult;

	// おまじない
	// アプリケーションでネットワーク機能を使えるようにします。
	callResult = enableNetwork();
	SPC_LOG_INFO("enableNetwork: %d", callResult);

	try
	{
		// https://rti-giken.jp/fhc/api/train_tetsudo/
		string url = "https://rti-giken.jp/fhc/api/train_tetsudo/delay.json";

		SPC_LOG_INFO("url: %s", url.c_str());
		speak("鉄道遅延情報のジェイソンにアクセスします。");

		// libcurl を直接使うと相当量のコードが必要ですが、ラッパーを使えば GET は2行です。
		// https://github.com/asashnov/tinycurl
		TinyCurl ob(url);
		string result = ob.fetch();

		// JSONのパーシングはとても書けないので、実績あるライブラリを使わせてもらいます。
		// https://github.com/kazuho/picojson
		picojson::value v;
		string err = picojson::parse(v, result);
		if (!err.empty()) {
			speak(err);
		}
		else {
			picojson::value::array resultList = v.get<picojson::value::array>();
			int count = 0;

			// GET結果をループさせながら発話させます。
			// フィルタや加工するような場合は、1度構造体やクラスにパーシングしたほうが良いと思います。
			for (picojson::value::array::const_iterator it = resultList.begin(); it != resultList.end(); ++it) {
				//{"name":"池袋線", "company" : "西武鉄道", "lastupdate_gmt" : 1456225502, "source" : "鉄道com RSS"},
				picojson::value::object resultRecord = it->get<picojson::object>();
				speak(resultRecord["company"].get<string>() + " の " + resultRecord["name"].get<string>());
				count++;
			}
			// GET結果を処理し終わった後には気の利いたことを発話させます。
			// Palmiは気配りを忘れません。
			if (count == 0) {
				speak("遅延情報はありませんでした。");
			}
			else {
				speak("が遅れているようです。大丈夫でしたか？");
			}
		}
	}
	catch (const TinyCurl::Exception &e)
	{
		// 例外を処理しなかった場合、SPCが無言で終了します。
		SPC_LOG_ERROR("Exception thrown: %s", e.what());
		speak(string("エラー。") + e.what() + "です。");
	}

	// おまじない
	// ネットワークの有効化、SDカードのマウントなど、リソースを確保した後は確実に開放するようにしてください。
	callResult = disableNetwork();
	SPC_LOG_INFO("disableNetwork: %d", callResult);

	// アプリケーションを終了します。
	exitComponent();
}

/**
* @brief 顔認識イベント
*
* Palmiが顔を見つけた場合に呼び出されます。
*
* @param [in] name 認識した個人の登録名(全角カタカナ)。個人未確定の場合は空白文字列。
*/
void spc_libcurl_sample::onFaceCatch(std::string name)
{
}


/**
* @brief 顔認識イベント
*
* Palmiが顔を見失った場合に呼び出されます。
*/
void spc_libcurl_sample::onFaceDrop()
{
}


/**
* @brief POTセンサーイベント
*
* Palmiの頭部をさわった時に呼び出されます。
*/
void spc_libcurl_sample::onPOTFluctuationCatch()
{
}


/**
* @brief タイマーイベント
*
* startTimer関数で設定した時間が経過した場合に呼び出されます。
*
* @param [in] timerId startTimer関数で取得したタイマーID
*/
void spc_libcurl_sample::onTimer(long timerId)
{
}

/**
* @brief アプリケーション終了イベント。
*
* アプリケーションの終了時に呼び出されます。
*/
void spc_libcurl_sample::onFinalize() {
	SPC_LOG_INFO("onFinalize");
}



// SPCアプリケーションインスタンス生成
spc_libcurl_sample	spcApp;

