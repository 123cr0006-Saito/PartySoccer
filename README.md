# PartySoccer  

個人で制作したパーティゲームです。

制作期間　2024/05/28～2024/06/28

**概要説明**  
2人から4人で遊べるサッカーゲームです。
Aボタンで力をためてシュートを打とう！　　

# 開発環境
[DXライブラリ](https://dxlib.xsrv.jp/)  
[nlomann-json](https://github.com/nlohmann/json)  

# プロジェクト構成  
```
.
|── AppFrame(ゲームを作成する際に必要となる機能や便利な機能をまとめたライブラリ)
|   |
|   └── source(ソースファイル)
|       |
|       |── Application(実行に必要となる機能や、汎用性が高い機能をまとめたファイルを格納)
|       |   |
|       |   |── ApplicationBase(DxLibの初期化や全体のループを管理するクラス)
|       |   |
|       |   |── Global(グローバル変数で持っておきたいものを作成するクラス)
|       |   |
|       |   |── UtilMacro(よく使う機能をマクロとしてまとめたもの)
|       |   |
|       |   └── WinMain(ゲーム全体の処理を行うもの)
|       |
|       |── CFile(ファイルの入出力機能をまとめたもの)
|       |   |
|       |   └── CFile(ファイルの入出力機能をまとめたファイル)
|       |
|       |── Mode(ゲームを作成する際に必要なフレームワークをまとめたもの)
|       |   |
|       |   |── ModeBase(ゲームのシーンを作成する際の基底クラス)
|       |   |
|       |   └── ModeServer(Mode関連のクラスを管理するクラス)
|       |
|       |── System(様々な機能を種類別に分けたもの)
|       |   |
|       |   └── Source ・ Header(Systemとして使用するクラスのソースとヘッダーファイルをまとめたもの　フォルダは分かれているが中身としては同じ)
|       |       |
|       |       |── Animation(アニメーションに必要なクラスや便利にする機能などをまとめたファイル)
|       |       |   |
|       |       |   |── AnimationItem(キャラクターのアニメーション情報を保持するクラス)
|       |       |   |
|       |       |   |── AnimationManager(キャラクターのアニメーションを管理するクラス)
|       |       |   |
|       |       |   |── FrameData(ファイルから読み込んだキャラクターのモーションに合わせて行う処理)
|       |       |   |
|       |       |   └── MotionList(各キャラクターのモーションリストを管理するクラス)
|       |       |
|       |       |── Collision(2Dや3Dの当たり判定に関する関数をまとめたフォルダ)
|       |       |   |
|       |       |   |── 2DCollision(2Dで使用する当たり判定関数をまとめたファイル)
|       |       |   |
|       |       |   |── 3DCollision(3Dで使用する当たり判定関数をまとめたファイル)
|       |       |   |
|       |       |   └── MyStructure(当たり判定用の構造体やクラスをまとめたファイル)
|       |       |
|       |       |── Effect(汎用性の高いエフェクトをまとめたフォルダ)
|       |       |   |
|       |       |   |── Afterglow(鉄球の目に残光を発生させるクラス)
|       |       |   |
|       |       |   |── AfterImage(半透明にしたモデルを複数体表示することで残像を表現するクラス)
|       |       |   |
|       |       |   |── Effect(汎用性の高いエフェクトをまとめたクラス)
|       |       |   |
|       |       |   └── ScreenVibration(画面上でのカメラが見ている映像の中心座標をずらす処理行うクラス)
|       |       |
|       |       |── Function(計算系クラスや描画系クラスをまとめたフォルダ)
|       |       |   |
|       |       |   |── 3DDraw(3Dの当たり判定を描画する関数をまとめたファイル)
|       |       |   |
|       |       |   |── bone(キャラクターの髪の毛やリボンなどをboneを物理演算で動かすためのクラス)
|       |       |   |
|       |       |   |── DrawGauge(指定した場所から時計回りに消えていく円形のゲージを描画するためのクラス)
|       |       |   |
|       |       |   |── Easing(イージング関連の機能をまとめたファイル)
|       |       |   |
|       |       |   |── Fog(プレイヤーが決められた範囲外に出るとフォグが発生するクラス)
|       |       |   |
|       |       |   |── Fps(FPSを60フレームで安定させるためのクラス)
|       |       |   |
|       |       |   |── Light(ファイルからデータを読み込みライトを設定するクラス)
|       |       |   |
|       |       |   |── ModelColor(モデルの白点滅処理を行うクラス)
|       |       |   |
|       |       |   |── mydraw(2Dで使用する描画関連の関数をまとめたクラス)
|       |       |   |
|       |       |   |── mymath(汎用性の高い計算系関数をまとめたクラス)
|       |       |   |
|       |       |   |── Timer(ゲームループの1周をマイクロ秒単位で取得するためのクラス)
|       |       |   |
|       |       |   |── Vector3D(自作のベクトルクラス)
|       |       |   |
|       |       |   └── Vibration(コントローラーの振動を管理するためのクラス)
|       |       |
|       |       |── Input(入力関連のクラスをまとめたフォルダ)
|       |       |   |
|       |       |   └── XInput(XInputのコントローラーを使用するために必要なクラス)
|       |       |
|       |       |── Resource(画像やモデルなどを管理するクラス)
|       |       |   |
|       |       |   └── ResourceServer(画像やモデルなどを管理するクラス)
|       |       |
|       |       └── Sound(SEやBGM、ボイスなどを一括で管理するクラス)
|       |           |
|       |           |── SoundItem(SEやBGMなどのサウンドアイテムのクラス集)
|       |           |
|       |           └── SoundServer(サウンドアイテムを再生や削除など管理するクラス)
|       |
|       └── appframe.h(AppFrame内のファイルのヘッダーを一つにまとめたもの)
|
|── DxLib(ライブラリ用ディレクトリ)
|
|── Game(ゲーム本体の Project)
|   |
|   |── Game
|   |   |
|   |   |── Shader(シェーダーに関するファイルが入っているフォルダ)
|   |   |   |
|   |   |   |── HLSL(VertexShaderやPixelShaderをコンパイルする前のファイルを保存)
|   |   |   |   |
|   |   |   |   |── MV1_Rim_PS(リムライトの処理が書いてあるピクセルシェーダー)
|   |   |   |   |
|   |   |   |   └── MV1_VS(基本的なバーテックスシェーダーに書かれてあるファイル)
|   |   |   |
|   |   |   |── PS(PixelShader)
|   |   |   |   |
|   |   |   |   └── MV1_Rim_PS(リムライトの処理が書いてあるピクセルシェーダー)
|   |   |   |
|   |   |   └── VS(VertexShader)
|   |   |       |
|   |   |       └── MV1_VS(基本的なバーテックスシェーダーに書かれてあるファイル)
|   |   |
|   |   |── include(インクルードフォルダ)
|   |   |   |
|   |   |   └── nlohmann(nlohmann-jsonのインクルードファイル)
|   |   |
|   |   └── source(ソースファイル)
|   |       |
|   |       |── Application(実行に必要となる機能や、汎用性が高い機能をまとめたファイルを格納)
|   |       |   |
|   |       |   └── ApplicationMain(ApplicationBaseを継承し、ModeServerなどの処理を行うクラス)
|   |       |
|   |       |── Manager(処理を一括して管理を行うクラス)
|   |       |   |
|   |       |   |── CollisionManager(当たり判定を管理するクラス)
|   |       |   |
|   |       |   |── ManagerBase(マネージャークラスの基底クラス)
|   |       |   |
|   |       |   |── ObjectManager(プレイヤー以外の当たり判定のあるものを管理するクラス)
|   |       |   |
|   |       |   |── PlayerManager(プレイヤーを管理するクラス)
|   |       |   |
|   |       |   |── RenderManager(3Dモデルの描画を管理するクラス)
|   |       |   |
|   |       |   |── SuperManager(マネージャークラスをレイヤー順に並び変え管理・処理をするクラス)
|   |       |   |
|   |       |   └── UIManager(UIを管理するクラス)
|   |       |
|   |       |── Mode(ModeBaseクラスを継承したシーンクラス)
|   |       |   |
|   |       |   |── ModeFade(ステージ遷移時にフェードイン、フェードアウトを行うためのクラス)
|   |       |   |
|   |       |   |── ModeFadeComeBack(ステージ遷移時にフェードインしてからフェードアウトを行うためのクラス)
|   |       |   |
|   |       |   |── ModeGame(ゲーム本編を管理するクラス)
|   |       |   |
|   |       |   |── ModeGameEnd(ゲーム本編が終了した際の演出を行うクラス)
|   |       |   |
|   |       |   |── ModeGoal(シュートが決まった際の演出や得点管理をするクラス)
|   |       |   |
|   |       |   |── ModeResult(ゲーム本編が終了した後、勝ったチームを演出するクラス)
|   |       |   |
|   |       |   |── ModeSelectPlayer(プレイヤーキャラクターの見た目を選択するクラス)
|   |       |   |
|   |       |   └── ModeTitle(ゲームのタイトルを管理するクラス)
|   |       |
|   |       |── Model(モデルに関するフォルダ)
|   |       |   |
|   |       |   |── Base(基底クラス)
|   |       |   |   |
|   |       |   |   └── ModelBase(3Dモデルを管理する基底クラス)
|   |       |   |
|   |       |   └── RimLightModel(モデル描画にリムライトを使用するクラス)
|   |       |
|   |       |── Object(プレイヤーやボールなどのオブジェクトに関するフォルダ)
|   |       |   |
|   |       |   |── Base(基底クラス)
|   |       |   |   |
|   |       |   |   └── ObjectBase(オブジェクトの基底クラス)
|   |       |   |
|   |       |   |── Player(プレイヤー関連)
|   |       |   |   |
|   |       |   |   └── Player(プレイヤークラス)
|   |       |   |
|   |       |   └── Stage(ステージ関連)
|   |       |       |
|   |       |       |── Ball(ボールクラス)
|   |       |       |
|   |       |       |── Goal(ゴールクラス)
|   |       |       |
|   |       |       |── Stage(ステージクラス)
|   |       |       |
|   |       |       └── Wall(押し出し処理を行うための当たり判定用オブジェクトクラス)
|   |       |
|   |       |── Other(その他)
|   |       |   |
|   |       |   |── Camera(カメラに関するクラス)
|   |       |   |   |
|   |       |   |   └── Camera(カメラを制御するクラス)
|   |       |   |
|   |       |   |── Score(得点を管理するクラス)
|   |       |   |
|   |       |   └── TimeLimit(ゲーム内の試合の時間を管理するクラス)
|   |       |
|   |       └── UI(UIに関するフォルダ)
|   |           |
|   |           |── Animation(UIにアニメーション付与するクラスフォルダ)
|   |           |   |
|   |           |   |── AnimationBase(UIアニメーションの基底クラス)
|   |           |   |
|   |           |   |── IterationAnim(sin波を使ったxとyが移動するアニメーションを行うクラス)
|   |           |   |
|   |           |   └── LocationAnim(指定のパラメーターの値を変更するアニメーションクラス)
|   |           |
|   |           |── Base(基底クラス)
|   |           |   |
|   |           |   |── UIBase(UIの基底クラス)
|   |           |   |
|   |           |   └── UIRotaBase(DrawRotaGraph関数を使用する際に用いるUIの基底クラス)
|   |           |
|   |           |── Score(得点に関するフォルダ)
|   |           |   |
|   |           |   |── UIScore(スコアを描画するUIクラス)
|   |           |   |
|   |           |   └── UIScoreBoard(スコアボードを描画するUIクラス)
|   |           |
|   |           |── UIFade(Fadeを行うクラス)
|   |           |
|   |           |── UIGameEnd(試合が終了したことを教えるUI)
|   |           |
|   |           |── UIPlayerParam(プレイヤーのスタミナやシュート力を表示するUI)
|   |           |
|   |           |── UIStartCount(ゲーム開始時のカウントダウンを行うUI)
|   |           |
|   |           └── UITimer(ゲーム内の残り時間を描画するクラス)
|   |
|   └── Game.sln(コードを見る際は、こちらを起動して下さい)
|
|── .gitattributes
|
|── .gitignore
|
└── README.md
```

# 起動方法  
上記のプロジェクトをダウンロードし、解凍後「Game/Game.sln」を起動  

# AppFrameについて  
ゲームを作成する上で定形的に必要となる機能また今までの制作で汎用的に使える機能をまとめたフレームワーク  
Static Library の形式で提供(Project 設定)  

***ApplicationBase***  

DX ライブラリを用いた Windows アプリケーションを作成する基底クラス  
本クラスを継承したクラスを作成すれば最小のコードでアプリのメイン部分を記述出来る  

***ModeBase / ModeServer***  

本フレームワークはモードと呼ぶ単位でプログラミング可能になっており、モードを切り替える機能も提供します。  
これによりアプリ作成者は、モード単位の実装をする事でゲームのフローを構築出来ます。  

ModeBase を継承したクラス単位でタイトルやインゲーム、設定画面など好きな単位で構築できModeServer が各モードを切り替える機能を提供します。  
