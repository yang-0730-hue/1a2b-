#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <windows.h> // �Ω�]�m����x��r�C��

using namespace std;

// �]�m����x��r�C��
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// �p������ A �M B ���C��аO
void displayColoredGuess(const string& secret, const string& guess) {
    // �аO�w�g�ǰt�� A �M B�A�H�קK���ƭp��
    bool matched_secret[4] = { false };
    bool matched_guess[4] = { false };

    // �����B�z A�]��m�M�Ʀr�����T�^
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == secret[i]) {
            setConsoleColor(12); // ����
            cout << guess[i];
            setConsoleColor(7);  // ���m�C��
            matched_secret[i] = true;
            matched_guess[i] = true;
        }
        else {
            cout << " "; // �e��A�H�O���榡���
        }
    }
    cout << " ";

    // �B�z B�]�Ʀr���T����m���~�^
    for (int i = 0; i < 4; ++i) {
        if (!matched_guess[i]) { // �p�G�Ӧ�m���O A
            bool is_b = false;
            for (int j = 0; j < 4; ++j) {
                if (!matched_secret[j] && guess[i] == secret[j]) {
                    setConsoleColor(14); // ����
                    cout << guess[i];
                    setConsoleColor(7);  // ���m�C��
                    matched_secret[j] = true;
                    is_b = true;
                    break;
                }
            }
            if (!is_b) cout << " "; // �Y�D B ��m�A�h�d��
        }
    }
    cout << endl;
}

// �ͦ� 4 �줣���ƪ��H���Ʀr�r��
string generateSecret() {
    string digits = "0123456789";
    shuffle(digits.begin(), digits.end(), mt19937(random_device()()));
    return digits.substr(0, 4); // ���e�|�Ӧr���@�����K�Ʀr
}

int main() {
    string secret = generateSecret(); // �H���ͦ� 4 �줣���ƪ����K�Ʀr
    string guess;
    cout << "�w��Ө� 1A2B �q�Ʀr�C���I\n";

    while (true) {
        cout << "�п�J�A�q�� 4 �줣���ƪ��Ʀr�G";
        cin >> guess;

        // �ˬd��J���榡
        if (guess.length() != 4 || !all_of(guess.begin(), guess.end(), ::isdigit)) {
            cout << "�L�Ŀ�J�I�п�J 4 �줣���ƪ��Ʀr�C\n";
            continue;
        }

        // �ˬd�Ʀr�O�_������
        string sorted_guess = guess;
        sort(sorted_guess.begin(), sorted_guess.end());
        if (unique(sorted_guess.begin(), sorted_guess.end()) != sorted_guess.end()) {
            cout << "�L�Ŀ�J�I�п�J 4 �줣���ƪ��Ʀr�C\n";
            continue;
        }

        // ��ܦ��C�⪺��J�Ʀr
        displayColoredGuess(secret, guess);

        // �ˬd�O�_�q��
        if (guess == secret) {
            cout << "���ߧA�q��F�I���׬O�G" << secret << "\n";
            break;
        }
    }

    return 0;
}
