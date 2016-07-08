/**
* @note 本プログラムの最終行にある変数宣言は非常に重要です。
* SPCフレームワークは、「spcApp」と言う固定の変数に対して処理を行うように作られています。
*/

#include "spc/spcbase2.h"
#include "SpcBaseCode.h"

#include <sstream>
#include <iomanip>

#include <Poco/File.h>

using namespace std;
using namespace spc;
using namespace Poco;

// http://vivi.dyndns.org/tech/cpp/binHex.html
#define  hexformat(fill, wd)    std::hex<<std::setfill(fill)<<std::setw(wd)

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

void SpcDisplayCharaSample::setCharToLed(std::string& c) {
	SPC_LOG_INFO("setCharToLed = %s", c.c_str());
	string dirPath;
	getDataDirPath(dirPath);
	string filePath = dirPath + "/fonts/misaki/" + charToUtf8Hex(c) + ".led";
	long ledResult = startLED(filePath);
	SPC_LOG_INFO("setCharToLed: startLED() = %d, filePath = %s", ledResult, filePath.c_str());
}

// http://blog.sarabande.jp/post/64271702938
std::string SpcDisplayCharaSample::utf8substr(std::string& originalString, int offset, int length)
{
	int pos;
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

		{
			string userCode = "いろはにほへと。漢字感じ幹事、とてもラップ";
			for (int i = 0; i < userCode.length();) {
				string c = utf8substr(userCode, i, 1);
				i += c.length();
				SPC_LOG_INFO("i = %d, c = %s, c.length() = %d", i, c.c_str(), c.length());
				setCharToLed(c);
				speak(string("<sapieVS_speed speed=\"70\">"
					+ c
					+ "</sapieVS_speed>"
					));
				sleep(1);
			}
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

