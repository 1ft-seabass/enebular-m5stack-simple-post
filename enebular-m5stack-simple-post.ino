#include <M5Stack.h>

// HTTP 通信を行うライブラリ
#include <HTTPClient.h>

// Wi-FiのSSID
const char *ssid = "Wi-FiのSSID";
// Wi-Fiのパスワード
const char *password = "Wi-Fiのパスワード";

// 今回送る enebular クラウド実行環境の URL
String enebularTriggerURL = "https://lcdp******.enebular.com/**********/from/m5stack";

// タイムアウト　ミリ秒
const int32_t httpTimeoutMillis = 10 * 1500;

// JSON を扱いやすくするライブラリ
#include <ArduinoJson.h>
// JSON を格納するオブジェクト DynamicJsonDocument
DynamicJsonDocument doc(255);
// 変換後の char を準備
char serializedJsonString[255];

void setup() {
  // init lcd, serial, but don't init sd card
  // LCD ディスプレイとシリアルは動かして、SDカードは動かさない設定
  M5.begin(true, false, true);

  // スタート
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // Arduino のシリアルモニタ・M5Stack LCDディスプレイ両方にメッセージを出す
  Serial.print("START");  // Arduino のシリアルモニタにメッセージを出す
  M5.Lcd.print("START");  // M5Stack LCDディスプレイにメッセージを出す（英語のみ）
   
  // WiFi 接続開始
  WiFi.begin(ssid, password);
  // 勝手に Button A が押されることを回避
  WiFi.setSleep(false);
 
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);

      // Arduino のシリアルモニタ・M5Stack LCDディスプレイ両方にメッセージを出す
      Serial.print(".");
      M5.Lcd.print(".");
  }

  // WiFi Connected
  // WiFi 接続完了
  M5.Lcd.setCursor(10, 40);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // Arduino のシリアルモニタ・M5Stack LCDディスプレイ両方にメッセージを出す
  // 前のメッセージが print で改行入っていないので println で一つ入れる
  Serial.println("");  // Arduino のシリアルモニタにメッセージを出し改行が最後に入る
  M5.Lcd.println("");  // M5Stack LCDディスプレイにメッセージを出す改行が最後に入る（英語のみ） 
  
  // Arduino のシリアルモニタ・M5Stack LCDディスプレイ両方にメッセージを出す
  Serial.println("WiFi Connected.");  // Arduino のシリアルモニタにメッセージを出す
  M5.Lcd.println("WiFi Connected.");  // M5Stack LCDディスプレイにメッセージを出す（英語のみ）
  
  // 起動時に送る
  delay(1000);
  
  // データを送る
  send_message("Launched!");
}

// HTTP でメッセージ送信部分
void send_message(String msg) {
  
  // JSON データ作成
  doc["message"] = msg;
  // JSON 変換
  serializeJson(doc,serializedJsonString);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);
  
  M5.Lcd.setTextSize(4);
  M5.Lcd.println(msg);
  Serial.println(msg);

  // 送るデータ
  String sendJsonString = serializedJsonString;
  // HTTPClient 準備
  HTTPClient httpClient;
  // URL 設定
  httpClient.begin(enebularTriggerURL);
  // Content-Type
  httpClient.addHeader("Content-Type", "application/json");
  // タイムアウト設定
  httpClient.setTimeout(httpTimeoutMillis);

  M5.Lcd.setTextSize(2);
  M5.Lcd.println("");
  Serial.println("");
  M5.Lcd.println("[send_message]");
  Serial.println("[send_message]");
  M5.Lcd.println("sendJsonString: ");
  M5.Lcd.println(sendJsonString);
  Serial.println("sendJsonString: ");
  Serial.println(sendJsonString);

  M5.Lcd.println("> send start...");
  Serial.println("> send start...");
  
  // 送信する
  int status_code = httpClient.POST(sendJsonString);
  
  M5.Lcd.println("> sended.");
  Serial.println("> sended.");
  
  if( status_code == 200 ){
    String response = httpClient.getString();

    M5.Lcd.println("> OK 200");
    Serial.println("> OK 200");
    
    M5.Lcd.println("response:");
    M5.Lcd.println(response);
  } else {
    M5.Lcd.println("> Error");
    Serial.println("> Error");

    M5.Lcd.println("status_code:");
    M5.Lcd.println(status_code);
  }
  
  httpClient.end();
}

void loop() {
  M5.update();
  
  if (M5.BtnA.wasReleased()) {
    // A ボタンを押したら JSON 形式のメッセージを飛ばす
    // データを送る
    send_message("Pushed A");
  } else if (M5.BtnB.wasReleased()) {
    // B ボタンを押したら JSON 形式のメッセージを飛ばす
    // データを送る
    send_message("Pushed B");
  } else if (M5.BtnC.wasReleased()) {
    // C ボタンを押したら JSON 形式のメッセージを飛ばす
    // データを送る
    send_message("Pushed C");
  }
}