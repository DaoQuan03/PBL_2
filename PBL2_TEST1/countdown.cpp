#include "countdown.h"

CountdownTimer::CountdownTimer(int seconds) : seconds(seconds) {}

void CountdownTimer::start() {
    while (seconds > 0) {
        cout << "Thoi gian con lai: " << seconds << " giay." << endl;

        auto start = chrono::steady_clock::now();
        while (chrono::steady_clock::now() - start < chrono::seconds(1)) {
        }

        --seconds;
    }
    cout << "Thoi gian da het!" << endl;
}
