#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <Windows.h>
#include <thread>

using namespace cv;
using namespace std;

#define CURL_STATICLIB
#pragma comment(lib, "libcurld.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")

void sendDataToArduino(const std::string& ip, const std::string& command) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        std::string url = "http://" + ip + "/" + command;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void sendDataToArduinoAsync(const std::string& ip, const std::string& command) {
    std::thread([ip, command]() {
        sendDataToArduino(ip, command);
        }).detach();
}

int main() {
    VideoCapture cap(0); // 첫 번째 카메라 사용
    if (!cap.isOpened()) {
        cout << "Error: Could not open the camera." << endl;
        return -1;
    }

    std::string arduinoIP = "ip"; // 아두이노의 IP 주소
    Mat frame, hsv, mask;

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cout << "Error: Could not capture frame." << endl;
            break;
        }

        cvtColor(frame, hsv, COLOR_BGR2HSV);

        Scalar lower_blue(100, 150, 50);
        Scalar upper_blue(140, 255, 255);

        inRange(hsv, lower_blue, upper_blue, mask);

        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        Point2f center;
        float radius;
        float max_area = 0;
        Point2f max_center;
        float max_radius;

        for (size_t i = 0; i < contours.size(); i++) {
            float area = contourArea(contours[i]);
            if (area < 300) {
                continue;
            }

            if (area > max_area) {
                max_area = area;
                minEnclosingCircle(contours[i], max_center, max_radius);
            }
        }

        if (max_area > 0) {
            circle(frame, max_center, (int)max_radius, Scalar(0, 255, 0), 2);
            circle(frame, max_center, 5, Scalar(0, 0, 255), -1);

            int posx = (max_center.x / frame_width) * 180;
            int posy = (max_center.y / frame_height) * 180;

            std::string command = "X" + std::to_string(posx) + "Y" + std::to_string(posy);
            sendDataToArduinoAsync(arduinoIP, command);
        }

        imshow("Frame", frame);
        imshow("Mask", mask);

        if (waitKey(30) >= 0) break;
    }

    return 0;
}
