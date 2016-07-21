/**
* @note 本プログラムの最終行にある変数宣言は非常に重要です。
* SPCフレームワークは、「spcApp」と言う固定の変数に対して処理を行うように作られています。
*/

#include "spc/spcbase2.h"
#include "SpcBaseCode.h"

#include <sstream>
#include <iomanip>

#include <Poco/File.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Crypto/DigestEngine.h>
#include <Poco/MD5Engine.h>

using namespace std;
using namespace spc;
using namespace Poco;

// http://vivi.dyndns.org/tech/cpp/binHex.html
// ゼロパディングありの16進文字列化マクロです。
#define  hexformat(fill, wd)    std::hex<<std::setfill(fill)<<std::setw(wd)

// 文字列を16進数表現に変換します。
std::string SpcDisplayCharaSample::charToUtf8Hex(std::string& c) {
	stringstream ss;
	ss << "x";
	const char* cp = c.c_str();
	while (*cp) {
		ss << hexformat('0', 2) << ((int)*cp & 0xff);
		cp++;
	}
	SPC_LOG_INFO("charToUtf8Hex = %s", ss.str().c_str());
	return ss.str();
}

// 指定した1文字をLEDに表示します。
void SpcDisplayCharaSample::setCharToLed(std::string& c) {
	SPC_LOG_INFO("setCharToLed = %s", c.c_str());
	string dirPath;
	getDataDirPath(dirPath);
	// {UTF-8の16進表現}.led という規則でファイルを配置することで対応する文字のファイルパスを構築、表示しています。
	string filePath = dirPath + "/fonts/misaki/" + charToUtf8Hex(c) + ".led";
	long ledResult = startLED(filePath);
	SPC_LOG_INFO("setCharToLed: startLED() = %d, filePath = %s", ledResult, filePath.c_str());
}

// http://blog.sarabande.jp/post/64271702938
// UTF-8のsubstrです。
std::string SpcDisplayCharaSample::utf8substr(std::string& originalString, int offset, int length)
{
	unsigned int pos;
	unsigned char lead;
	int char_size;
	int char_count = 0;

	for (pos = offset;
		pos < originalString.size() && char_count < length;
		pos += char_size) {
		lead = originalString[pos];

		if (lead < 0x80) {
			char_size = 1;
		}
		else if (lead < 0xe0) {
			char_size = 2;
		}
		else if (lead < 0xf0) {
			char_size = 3;
		}
		else {
			char_size = 4;
		}
		char_count++;
	}

	return originalString.substr(offset, pos - offset);
}

/**
* @brief アプリケーション初期化イベント。
*
* アプリケーションの実行開始時に呼び出されます。
*/
void SpcDisplayCharaSample::onInitialize()
{
	try {
		// LED表示のためのネタとしてハッシュを得ています。
		Poco::DateTime dateTime;
		std::string dateTimeString = Poco::DateTimeFormatter::format(dateTime, "%Y%m%d%H%M");
		std::string dateTimeMessage = Poco::DateTimeFormatter::format(dateTime, "%Y年%m月%d日%H字%M分の数字部分をつないだ文字列のエムディー5ハッシュをお知らせします。");

		Poco::MD5Engine engine;
		engine.update(dateTimeString.c_str(), dateTimeString.size());
		std::string hash = Poco::DigestEngine::digestToHex(engine.digest());

		SPC_LOG_INFO(dateTimeString.c_str());
		SPC_LOG_INFO(hash.c_str());

		speak(dateTimeMessage);

		// 全文字を処理します。
		for (unsigned int i = 0; i < hash.length();) {
			// (ソースコードがUTF-8なので)UTF-8としての1文字を得ています。
			string c = utf8substr(hash, i, 1);
			i += c.length();
			SPC_LOG_INFO("i = %d, c = %s, c.length() = %d", i, c.c_str(), c.length());
			// LEDに表示した後文字を発話します。
			setCharToLed(c);
			speak(string("<sapieVS_speed speed=\"70\">"
				+ c
				+ "</sapieVS_speed>"
			));
			sleep(1);
		}
	}
	catch (...) {
		speak("エラーです。");
	}

	exitComponent();
}

/**
* @brief 顔認識イベント
*
* Palmiが顔を見つけた場合に呼び出されます。
*
* @param [in] name 認識した個人の登録名(全角カタカナ)。個人未確定の場合は空白文字列。
*/
void SpcDisplayCharaSample::onFaceCatch(std::string name)
{
}


/**
* @brief 顔認識イベント
*
* Palmiが顔を見失った場合に呼び出されます。
*/
void SpcDisplayCharaSample::onFaceDrop()
{
}


/**
* @brief POTセンサーイベント
*
* Palmiの頭部をさわった時に呼び出されます。
*/
void SpcDisplayCharaSample::onPOTFluctuationCatch()
{
}


/**
* @brief タイマーイベント
*
* startTimer関数で設定した時間が経過した場合に呼び出されます。
*
* @param [in] timerId startTimer関数で取得したタイマーID
*/
void SpcDisplayCharaSample::onTimer(long timerId)
{
}

/**
* @brief アプリケーション終了イベント。
*
* アプリケーションの終了時に呼び出されます。
*/
void SpcDisplayCharaSample::onFinalize() {
}



// SPCアプリケーションインスタンス生成
SpcDisplayCharaSample	spcApp;

