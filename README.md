# enebular-m5stack-simple-post

このリポジトリは enebular と M5Stack をつなげるための M5Stack 側の Arduino のソースコード置き場です。

## バージョンや設定

- Arduino IDE
  - バージョン 1.8.16
- M5Stack Basic に書き込むボード設定ができている前提です
  - ボード設定 2.0.1
- MtStack Basic 関連の M5Stack ライブラリがインストールされている前提です
  - MtStack ライブラリ 0.4.1
- MtStack Basic に PC から書き込める USB ドライバの設定ができている前提です

## JSON を扱いやすくする ArduinoJson ライブラリインストール

この作業はインストールなので、一度だけ対応すれば OK です。

![6c191b7ead13d2d12b2a7dab334d2224](https://i.gyazo.com/6c191b7ead13d2d12b2a7dab334d2224.png)

ツール > ライブラリを管理 でライブラリマネージャを起動します。

![image](https://i.gyazo.com/b8b223beedfe7b134fe5380e1920e584.png)

`ArduinoJson` で検索して、`完全同名` のライブラリを探します。

マウスを乗せると、バージョンとインストールのボタンが右下に出るので `6.18.5` のバージョンを指定してインストールボタンをクリックします。バージョンはおそらく 6 以上なら動きます。

![image](https://i.gyazo.com/ec1d0688667c161c941eced03a1bade9.png)

インストールできたら、ひょっとすると、リストが一番上に戻ってしまうかもしれませんが、根気よく `ArduinoJson` に移動して INSTALLED になっていたら成功です。

## 実際のプログラム

enebular-m5stack-simple-post.ino をコピーして、みなさんの Arduino IDE で開いて作業を進めます。

## Wi-Fi 情報を反映

```c
// Wi-FiのSSID
const char *ssid = "Wi-FiのSSID";
// Wi-Fiのパスワード
const char *password = "Wi-Fiのパスワード";
```

自分のつなぎたい Wi-Fi の SSID とパスワードを反映します。

## 今回送る enebular クラウド実行環境の URL を反映

```c
// 今回送る enebular クラウド実行環境の URL
String enebularTriggerURL = "https://lcdp******.enebular.com/**********/from/m5stack";
```

今回送る enebular クラウド実行環境の URL に `/from/m5stack` をつけたものを反映します。




