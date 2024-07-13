# Object-Detection with visual studio and arduino
How to detect objects and control Arduino to trek
<br><br><br>
우선 영상처리는 visual studio에서 하고 정보를 아두이노로 보내어 제어 할것이다.

<br><br>

그렇기 때문에 먼저 아두이노를 통해 정보를 주고받을 웹서버를 만드는 작업을 한다.
이를위해 아두이노에 와이파이 모듈이 장착되어있는 모델을 사용하여야한다.

<br><br>

필자는 **Arduino Nano RP2040**를 사용하였다.

아두이노 기본 설정에 대한 정보는 다음 글을 참조하길 바란다.

<https://jiwoojung.tistory.com/2>

<br>

그리고 필요한 소자가 서보모터 2개를 이용하여 만든 팬틸트 형식의 소자가 필요하다


![pentiltle](https://github.com/user-attachments/assets/0ad18c22-8ed1-470b-b0ae-613573767ab6)

<br><br>
---
<br><br>

**1.[아두이노와 웹서버의 연결]**


<br><br>
아두이노 코드
<br><br>
위 파일을 참고하여 6,7번째줄에 "network"와 "password"에는 자신이 사용할 와이파이의 이름과, 패스워드를 입력하길 바란다.
<br><br>
코드를 입력하고 시행하면, 시리얼 모니터에 ip주소가 나올것이다.

ip주소를 와이파이가 연결되어있는 노트북의 인터넷 주소에 입력하면 제어가 가능한 웹서버가 나온다.
<br>
![webserver](https://github.com/user-attachments/assets/c2b04591-89f8-41b1-8301-680392d4e004)
<br>
이렇게 하면 visual studio - 웹서버 - 아두이노의 연결에서
아두이노와 웹서버가 연결된것이다.
<br><br><br>

---
<br><br><br>

**2.[visual studio와 웹서버 연결]**

이제 visual studio에서 웹서버로 정보를 전송하면 완료된다.

<br><br>

우선 필요한것은 와이파이 연결되는 컴퓨터와 웹캠이다.

그리고 라이브러리는 opencv와 curl이 필요하다. 

<br><br>

opencv에 관한 설치방법은 인터넷에 많기 때문에 생략하고
인터넷 통신을 가능하게 하는 curl라이브러리는 다음 글을 확인하길 바란다.

<https://jiwoojung.tistory.com/1﻿>
<br><br><br>
첨부 파일의 C++ 코드를 참조하길 바란다. 

필자의 코드는 특정물체(파란물체)를 디텍팅 하여 좌표를 반환하고 웹서버로 보내는 코드이다.

![image](https://github.com/user-attachments/assets/529fe5bf-744c-4788-9bb7-0d7e98886281)
<br><br><br>

+) 49줄에  std::string arduinoIP = "ip"; // 아두이노의 IP 주소
부분에 ip대신 1부에서 설명한듯이 실행하여 나오는 와이파이의 ip 주소를 입력하여야 한다.

<br><br>
필자는 우선 파란색의 물체를 검출하여 좌표값을 반환하고
이를 180도 기준으로 분할하여 X,Y축으로 이동해야 하는각도를 서버에 보내는 작업을 코드로 작성하였다.
<br>

완성한 아두이노를 실행하여 웹서버를 개설하고, 이후 visual studio를 실행하여 정보를 보내면 완성이다.

<br>
데모결과는 아래영상과 같은 모습이다.

<https://youtu.be/f2TUxoaKIsA?si=X2wu3TiXFxsy7mnI>
<br>
위 영상은 파이썬으로 작동시킨 모습이고 필자의 코드는 C++을 활용하여 작동시킨 코드이다.
