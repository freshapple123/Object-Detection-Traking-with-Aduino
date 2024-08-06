# Object-Detection with Visual Studio and Arduino

## How to Detect Objects and Control Arduino to Track

우선 영상 처리는 Visual Studio에서 하고 정보를 Arduino로 보내어 제어할 것입니다.

<br>

먼저 Arduino를 통해 정보를 주고받을 웹서버를 만드는 작업을 합니다. 이를 위해 Arduino에 Wi-Fi 모듈이 장착되어 있는 모델을 사용해야 합니다.

필자는 **Arduino Nano RP2040**를 사용하였습니다.

Arduino 기본 설정에 대한 정보는 다음 글을 참조하길 바랍니다:

<https://jiwoojung.tistory.com/2>

<br>

그리고 필요한 소자는 서보모터 2개를 이용하여 만든 팬틸트 형식의 소자가 필요합니다.

![pentiltle](https://github.com/user-attachments/assets/0ad18c22-8ed1-470b-b0ae-613573767ab6)

---

<br>

## 1. 아두이노와 웹서버의 연결

아두이노 코드

위 파일을 참고하여 6, 7번째 줄에 "network"와 "password"에는 자신이 사용할 와이파이의 이름과 패스워드를 입력하시길 바랍니다.

코드를 입력하고 시행하면 시리얼 모니터에 IP 주소가 나올 것입니다.

IP 주소를 와이파이가 연결되어 있는 노트북의 인터넷 주소에 입력하면 제어가 가능한 웹서버가 나옵니다.

![webserver](https://github.com/user-attachments/assets/c2b04591-89f8-41b1-8301-680392d4e004)

이렇게 하면 Visual Studio - 웹서버 - Arduino의 연결에서 Arduino와 웹서버가 연결된 것입니다.

---

<br>

## 2. Visual Studio와 웹서버 연결

이제 Visual Studio에서 웹서버로 정보를 전송하면 완료됩니다.

우선 필요한 것은 와이파이 연결되는 컴퓨터와 웹캠입니다.

그리고 라이브러리는 OpenCV와 cURL이 필요합니다.

OpenCV에 관한 설치 방법은 인터넷에 많기 때문에 생략하고, 인터넷 통신을 가능하게 하는 cURL 라이브러리는 다음 글을 확인하시길 바랍니다:

<https://github.com/freshapple123/curl-library>

첨부 파일의 C++ 코드를 참조하시길 바랍니다.

필자의 코드는 특정 물체(파란 물체)를 디텍팅하여 좌표를 반환하고 웹서버로 보내는 코드입니다.

![image](https://github.com/user-attachments/assets/529fe5bf-744c-4788-9bb7-0d7e98886281)

<br>

### 참고사항
+) 49줄에 `std::string arduinoIP = "ip";` // 아두이노의 IP 주소 부분에 "ip" 대신 1부에서 설명한 것처럼 실행하여 나오는 와이파이의 IP 주소를 입력하여야 합니다.

필자는 우선 파란색의 물체를 검출하여 좌표값을 반환하고 이를 180도 기준으로 분할하여 X, Y축으로 이동해야 하는 각도를 서버에 보내는 작업을 코드로 작성하였습니다.

<br>

완성한 Arduino를 실행하여 웹서버를 개설하고, 이후 Visual Studio를 실행하여 정보를 보내면 완성입니다.

<br>

데모 결과는 아래 영상과 같은 모습입니다:

<https://youtu.be/f2TUxoaKIsA?si=X2wu3TiXFxsy7mnI>

위 영상은 파이썬으로 작동시킨 모습이고, 필자의 코드는 C++을 활용하여 작동시킨 코드입니다.
