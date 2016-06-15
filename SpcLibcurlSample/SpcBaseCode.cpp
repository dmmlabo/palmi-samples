/**
* @note 本プログラムの最終行にある変数宣言は非常に重要です。
* SPCフレームワークは、「spcApp」と言う固定の変数に対して処理を行うように作られています。
*/

#include "spc/spcbase2.h"
#include "SpcBaseCode.h"

/**
* @brief アプリケーション初期化イベント。
*
* アプリケーションの実行開始時に呼び出されます。
*/
void SpcLibcurlSample::onInitialize()
{
	// アプリケーションを終了する場合は、以下の関数「exitComponent()」を呼び出してください。
	exitComponent();
}

/**
* @brief 顔認識イベント
*
* Palmiが顔を見つけた場合に呼び出されます。
*
* @param [in] name 認識した個人の登録名(全角カタカナ)。個人未確定の場合は空白文字列。
*/
void SpcLibcurlSample::onFaceCatch(std::string name)
{
}


/**
* @brief 顔認識イベント
*
* Palmiが顔を見失った場合に呼び出されます。
*/
void SpcLibcurlSample::onFaceDrop()
{
}


/**
* @brief POTセンサーイベント
*
* Palmiの頭部をさわった時に呼び出されます。
*/
void SpcLibcurlSample::onPOTFluctuationCatch()
{
}


/**
* @brief タイマーイベント
*
* startTimer関数で設定した時間が経過した場合に呼び出されます。
*
* @param [in] timerId startTimer関数で取得したタイマーID
*/
void SpcLibcurlSample::onTimer(long timerId)
{
}

/**
* @brief アプリケーション終了イベント。
*
* アプリケーションの終了時に呼び出されます。
*/
void SpcLibcurlSample::onFinalize() {
}



// SPCアプリケーションインスタンス生成
SpcLibcurlSample	spcApp;

