#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Servo.h>


#define SerialCom_TX D3
#define SerialCom_RX D4
const char* ssid = "isbAP";
const char* password = "isb770rom";

WiFiServer server(80);

SoftwareSerial SerialCom ( SerialCom_TX, SerialCom_RX);

int value = LOW;
int Open=0;
int Close=1;
int pos=100;

Servo myservo;

void setup() {
  
  Serial.begin(9600);
  SerialCom.begin(9600);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
  
  myservo.attach(D1);


  
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  
  //Serial.println("new client");
  
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  //Serial.println(request);
  client.flush();

  // Match the request
  
  if (request.indexOf("/PORTRAIT") != -1)  {
   
    value = HIGH;
    Serial.println(Open);
    myservo.write(92);
    //digitalWrite(BUILTIN_LED, value);
  }
  if (request.indexOf("/LANDSCAPE") != -1)  {
   
    value = LOW;
    Serial.println(Close);
    myservo.write(10);
    //digitalWrite(BUILTIN_LED, value);
  }


  //return the response
  client.println("<!DOCTYPE html>\r\n<html lang=\"en\">\r\n  <head>\r\n    <meta charset=\"utf-8\">\r\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\r\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->\r\n    <title>Devices<\/title>\r\n    <!-- Bootstrap -->\r\n    <link href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.7\/css\/bootstrap.min.css\" rel=\"stylesheet\">\r\n    <style>\r\n\tbody {\r\n  padding-top: 50px;\r\n}\r\n.starter-template {\r\n  padding: 40px 15px;\r\n  text-align: center;\r\n}\r\nbody {\r\n  padding-top: 40px;\r\n  padding-bottom: 40px;\r\n  background-color: #eee;\r\n}\r\n\r\n.form-signin {\r\n  max-width: 330px;\r\n  padding: 15px;\r\n  margin: 0 auto;\r\n}\r\n.form-signin .form-signin-heading,\r\n.form-signin .checkbox {\r\n  margin-bottom: 10px;\r\n}\r\n.form-signin .checkbox {\r\n  font-weight: normal;\r\n}\r\n.form-signin .form-control {\r\n  position: relative;\r\n  height: auto;\r\n  -webkit-box-sizing: border-box;\r\n     -moz-box-sizing: border-box;\r\n          box-sizing: border-box;\r\n  padding: 10px;\r\n  font-size: 16px;\r\n}\r\n.form-signin .form-control:focus {\r\n  z-index: 2;\r\n}\r\n.form-signin input[type=\"email\"] {\r\n  margin-bottom: -1px;\r\n  border-bottom-right-radius: 0;\r\n  border-bottom-left-radius: 0;\r\n}\r\n.form-signin input[type=\"password\"] {\r\n  margin-bottom: 10px;\r\n  border-top-left-radius: 0;\r\n  border-top-right-radius: 0;\r\n}\r\n.error{\r\n  border-color: red;\r\n}\r\n\t<\/style>\r\n    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->\r\n    <!-- WARNING: Respond.js doesn\'t work if you view the page via file:\/\/ -->\r\n    <!--[if lt IE 9]>\r\n    <script src=\"https:\/\/oss.maxcdn.com\/html5shiv\/3.7.3\/html5shiv.min.js\"><\/script>\r\n    <script src=\"https:\/\/oss.maxcdn.com\/respond\/1.4.2\/respond.min.js\"><\/script>\r\n    <![endif]-->\r\n  <\/head>\r\n  <body shm_addon_injected=\"1.0.12.1\">\r\n    <nav class=\"navbar navbar-inverse navbar-fixed-top\">\r\n      <div class=\"container\">\r\n        <div class=\"navbar-header\">\r\n          <button type=\"button\" class=\"navbar-toggle collapsed\" data-toggle=\"collapse\" data-target=\"#navbar\" aria-expanded=\"false\" aria-controls=\"navbar\">\r\n          <span class=\"sr-only\">Toggle navigation<\/span>\r\n          <span class=\"icon-bar\"><\/span>\r\n          <span class=\"icon-bar\"><\/span>\r\n          <span class=\"icon-bar\"><\/span>\r\n          <\/button>\r\n          <a class=\"navbar-brand\" href=\"#\">Devices<\/a>\r\n        <\/div>\r\n      <\/nav>\r\n      <div class=\"container\">\r\n        <div class=\"starter-template\">\r\n          <a href=\"\/PORTRAIT\" id=\"portrait\" type=\"button\" class=\"btn btn-success btn-sm  btn-block\">PORTRAIT<\/a>\r\n          <a href=\"\/LANDSCAPE\" id = \"landscape\" type=\"button\" class=\"btn btn-danger btn-sm btn-block\">LANDSCAPE<\/a>\r\n          \r\n        <\/div>\r\n        <\/div><!-- \/.container -->\r\n        <!-- Bootstrap core JavaScript\r\n        ================================================== -->\r\n        <!-- Placed at the end of the document so the pages load faster -->\r\n        <!-- jQuery (necessary for Bootstrap\'s JavaScript plugins) -->\r\n        \r\n      <\/html>");

  delay(1);
  //Serial.println("Client disonnected");
  //Serial.println("");
}
