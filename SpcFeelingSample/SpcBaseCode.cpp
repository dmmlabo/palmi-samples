/**
* @note 本プログラムの最終行にある変数宣言は非常に重要です。
* SPCフレームワークは、「spcApp」と言う固定の変数に対して処理を行うように作られています。
*/

#include "spc/spcbase2.h"
#include "SpcBaseCode.h"

using namespace spc;
using namespace std;

/**
* @brief アプリケーション初期化イベント。
*
* アプリケーションの実行開始時に呼び出されます。
*/
void SpcFeelingSample::onInitialize()
{
	FeelingSetting settings[] = {
		{ SPC_FEELING_JOY, "喜び" },
		{ SPC_FEELING_LITTLESMILE, "はにかみ" },
		{ SPC_FEELING_SORROW, "悲しみ" },
		{ SPC_FEELING_SORRY, "謝る" },
		{ SPC_FEELING_BRAG, "自慢する" },
		{ SPC_FEELING_PERPLEXITY, "困惑" },
		{ SPC_FEELING_REGRET, "残念" },
		{ SPC_FEELING_AGREE, "同意" },
		{ SPC_FEELING_UNDERSTAND, "承知" },
		{ SPC_FEELING_CONCERN, "関心" },
		{ SPC_FEELING_SHY, "照れる" },
		{ SPC_FEELING_SURPRISE, "驚く" },
		{ SPC_FEELING_FAILURE, "失敗した" },
		{ SPC_FEELING_SUCCESS, "成功した" },
		{ SPC_FEELING_TELLCORRECT, "正解を伝える" },
		{ SPC_FEELING_TELLINCORRECT, "失敗を伝える" },
		{ SPC_FEELING_TELLATTENTION, "注意をひく" },
		{ SPC_FEELING_BIGJOY, "大きな喜び" }
	};
	int length = sizeof(settings) / sizeof(FeelingSetting);

	speak("ボクの感情表現を順番にお見せします。");

	for (unsigned int i = 0; i < length; i++) {
		FeelingSetting* setting = &settings[i];
		speak(setting->feelingName + " 表現です。");
		expressFeeling(setting->feelingType);
	}

	speak("以上です。");

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
void SpcFeelingSample::onFaceCatch(std::string name)
{
}


/**
* @brief 顔認識イベント
*
* Palmiが顔を見失った場合に呼び出されます。
*/
void SpcFeelingSample::onFaceDrop()
{
}


/**
* @brief POTセンサーイベント
*
* Palmiの頭部をさわった時に呼び出されます。
*/
void SpcFeelingSample::onPOTFluctuationCatch()
{
}


/**
* @brief タイマーイベント
*
* startTimer関数で設定した時間が経過した場合に呼び出されます。
*
* @param [in] timerId startTimer関数で取得したタイマーID
*/
void SpcFeelingSample::onTimer(long timerId)
{
}

/**
* @brief アプリケーション終了イベント。
*
* アプリケーションの終了時に呼び出されます。
*/
void SpcFeelingSample::onFinalize() {
}



// SPCアプリケーションインスタンス生成
SpcFeelingSample	spcApp;

