/**
* @note 本プログラムの最終行にある変数宣言は非常に重要です。
* SPCフレームワークは、「spcApp」と言う固定の変数に対して処理を行うように作られています。
*/

#include "spc/spcbase2.h"
#include "SpcBaseCode.h"

#include <sstream>
#include <Poco/Exception.h>
#include <Poco/Util/XMLConfiguration.h>
#include <Poco/Util/AbstractConfiguration.h>

using namespace std;
using namespace spc;
using namespace Poco;
using namespace Poco::Util;

/**
* @brief アプリケーション初期化イベント。
*
* アプリケーションの実行開始時に呼び出されます。
*/
void SpcPocoConfigurationSample::onInitialize()
{
	SPC_LOG_INFO("onInitialize");
	// 頭をタッチした際にアプリを終了せず、イベントの通知を行うように設定します。
	setActionPOTFluctuation(SPC_ONLY_NOTYFY_POT_FLUCTUATION);

	try {
		// microSDカードが挿入されている場合はそちらのファイルを参照するようにしています。
		// SPC毎に読み書きできるディレクトリが異なります。
		// それらは所定のメソッドで取得します。
		bool sdCardEnable = mountMicroSD() == 0;
		std::string configDirPath;
		std::string configFilePath;
		if (sdCardEnable) {
			// SDカード上のSPC向けディレクトリは「/_PALMI_/{SPC名}」です。
			// あらかじめファイルを配置しておくようなことが可能です。
			// このサンプルでは「/_PALMI_/SpcPocoConfigurationSample」に「config.xml」を配置することで読み込まれます。
			getMicroSDDirPath(configDirPath);
		}
		else {
			getDataDirPath(configDirPath);
		}
		configFilePath = configDirPath + "/config.xml";

		// ここでは XML 形式の設定ファイルを読み込むクラスを用います。
		// 他にも各種形式が AbstractConfiguration を実装しています。
		// http://www.appinf.com/docs/poco/Poco.Util.XMLConfiguration.html
		// http://www.appinf.com/docs/poco/Poco.Util.AbstractConfiguration.html
		// インスタンス化するだけで読み込みが終わります。
		AutoPtr<AbstractConfiguration> settings(new XMLConfiguration(configFilePath));

		// 読み込み結果の取得方法は AbstractConfiguration として標準化されています。
		singleValue = settings->getString("single", "default-single-value");
		SPC_LOG_INFO(singleValue.c_str());
		speak(singleValue);

		// ネストした値は要素名の「.」区切りで取得できます。
		nestedValue = settings->getString("parent.child");
		SPC_LOG_INFO(nestedValue.c_str());
		speak(nestedValue);

		// 同一の要素名が複数ある場合は、配列の添え字のように要素を指定します。
		stringstream ss;
		int i;
		i = 0;
		while (true) {
			ss.str("");
			ss << "message" << "[" << i << "]";
			if (!settings->hasProperty(ss.str())) {
				break;
			}
			string message = settings->getString(ss.str());
			messages.push_back(message);
			i++;
		}
	}
	catch (Poco::Exception& ex) {
		SPC_LOG_ERROR(ex.displayText().c_str());
		speak(ex.displayText().c_str());
	}
	catch (...) {
		SPC_LOG_ERROR("handle error.");
		speak("handle error.");
	}
	umountMicroSD();

	currentMessageIndex = -1;
}

/**
* @brief 顔認識イベント
*
* Palmiが顔を見つけた場合に呼び出されます。
*
* @param [in] name 認識した個人の登録名(全角カタカナ)。個人未確定の場合は空白文字列。
*/
void SpcPocoConfigurationSample::onFaceCatch(std::string name)
{
}


/**
* @brief 顔認識イベント
*
* Palmiが顔を見失った場合に呼び出されます。
*/
void SpcPocoConfigurationSample::onFaceDrop()
{
}


/**
* @brief POTセンサーイベント
*
* Palmiの頭部をさわった時に呼び出されます。
*/
void SpcPocoConfigurationSample::onPOTFluctuationCatch()
{
	SPC_LOG_INFO("onPOTFluctuationCatch");
	if (messages.size() == 0) {
		speak("メッセージがありません。");
		return;
	}
	// 読み込んだ要素の数だけ順番に発話させます。
	currentMessageIndex++;
	if ((long)messages.size() <= currentMessageIndex) {
		speak("先頭に戻ります。");
		currentMessageIndex = 0;
	}
	speak(messages[currentMessageIndex]);
}


/**
* @brief タイマーイベント
*
* startTimer関数で設定した時間が経過した場合に呼び出されます。
*
* @param [in] timerId startTimer関数で取得したタイマーID
*/
void SpcPocoConfigurationSample::onTimer(long timerId)
{
}

/**
* @brief アプリケーション終了イベント。
*
* アプリケーションの終了時に呼び出されます。
*/
void SpcPocoConfigurationSample::onFinalize() {
	SPC_LOG_INFO("onFinalize");
}



// SPCアプリケーションインスタンス生成
SpcPocoConfigurationSample	spcApp;

