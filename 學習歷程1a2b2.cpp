#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <windows.h> // 用於設置控制台文字顏色

using namespace std;

// 設置控制台文字顏色
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 計算並顯示 A 和 B 的顏色標記
void displayColoredGuess(const string& secret, const string& guess) {
    // 標記已經匹配的 A 和 B，以避免重複計算
    bool matched_secret[4] = { false };
    bool matched_guess[4] = { false };

    // 首先處理 A（位置和數字都正確）
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == secret[i]) {
            setConsoleColor(12); // 紅色
            cout << guess[i];
            setConsoleColor(7);  // 重置顏色
            matched_secret[i] = true;
            matched_guess[i] = true;
        }
        else {
            cout << " "; // 占位，以保持格式對齊
        }
    }
    cout << " ";

    // 處理 B（數字正確但位置錯誤）
    for (int i = 0; i < 4; ++i) {
        if (!matched_guess[i]) { // 如果該位置不是 A
            bool is_b = false;
            for (int j = 0; j < 4; ++j) {
                if (!matched_secret[j] && guess[i] == secret[j]) {
                    setConsoleColor(14); // 黃色
                    cout << guess[i];
                    setConsoleColor(7);  // 重置顏色
                    matched_secret[j] = true;
                    is_b = true;
                    break;
                }
            }
            if (!is_b) cout << " "; // 若非 B 位置，則留空
        }
    }
    cout << endl;
}

// 生成 4 位不重複的隨機數字字串
string generateSecret() {
    string digits = "0123456789";
    shuffle(digits.begin(), digits.end(), mt19937(random_device()()));
    return digits.substr(0, 4); // 取前四個字元作為秘密數字
}

int main() {
    string secret = generateSecret(); // 隨機生成 4 位不重複的秘密數字
    string guess;
    cout << "歡迎來到 1A2B 猜數字遊戲！\n";

    while (true) {
        cout << "請輸入你猜的 4 位不重複的數字：";
        cin >> guess;

        // 檢查輸入的格式
        if (guess.length() != 4 || !all_of(guess.begin(), guess.end(), ::isdigit)) {
            cout << "無效輸入！請輸入 4 位不重複的數字。\n";
            continue;
        }

        // 檢查數字是否不重複
        string sorted_guess = guess;
        sort(sorted_guess.begin(), sorted_guess.end());
        if (unique(sorted_guess.begin(), sorted_guess.end()) != sorted_guess.end()) {
            cout << "無效輸入！請輸入 4 位不重複的數字。\n";
            continue;
        }

        // 顯示有顏色的輸入數字
        displayColoredGuess(secret, guess);

        // 檢查是否猜對
        if (guess == secret) {
            cout << "恭喜你猜對了！答案是：" << secret << "\n";
            break;
        }
    }

    return 0;
}
