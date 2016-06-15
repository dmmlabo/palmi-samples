class SpcLibcurlSample : spc::SPCBase
{

public:

	/**
	* @brief アプリケーション初期化イベント。
	*
	* アプリケーションの実行開始時に呼び出されます。
	*/
	void onInitialize();

	/**
	* @brief 顔認識イベント
	*
	* Palmiが顔を見つけた場合に呼び出されます。
	*
	* @param [in] name 認識した個人の登録名(全角カタカナ)。個人未確定の場合は空白文字列。
	*/
	void onFaceCatch(std::string name);

	/**
	* @brief 顔認識イベント
	*
	* Palmiが顔を見失った場合に呼び出されます。
	*/
	void onFaceDrop();

	/**
	* @brief POTセンサーイベント
	*
	* Palmiの頭部をさわった時に呼び出されます。
	*/
	void onPOTFluctuationCatch();

	/**
	* @brief タイマーイベント
	*
	* startTimer関数で設定した時間が経過した場合に呼び出されます。
	*
	* @param [in] timerId startTimer関数で取得したタイマーID
	*/
	void onTimer(long timerId);

	/**
	* @brief アプリケーション終了イベント。
	*
	* アプリケーションの終了時に呼び出されます。
	*/
	void onFinalize();

};
