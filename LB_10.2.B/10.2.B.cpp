#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cmath>

using namespace std;

#pragma pack(push, 1)

enum Speciality { IT, RE, KN, KI, PZ };
string speciality_str[] = { "�����������", "��������������", "����'����� �����", "����'������ ��������", "��������� ������������" };

struct Students {
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_info;

    // ����������� �� �������������
    Students() {
        surname = "";
        course = 0;
        speciality = IT;
        grade_physics = 0;
        grade_math = 0;
        grade_info = 0;
    }
};

#pragma pack(pop)

void Create(Students* S, const int N);
double student_average_evaluation(Students* S, int i);
void Print(Students* S, const int N);
void p_sort(Students* S, const int N);
int* i_sort(Students* S, const int N);
void i_print(Students* S, int* I, const int N);
bool areDoublesEqual(double a, double b, double eps = 0.01);
bool b_search(Students* S, const int N, const string surname, const int course, const double average_evaluation);

static void showMenu() {
    cout << "������ ��:" << endl;
    cout << "1 - ������ ���������� ��� ��������" << endl;
    cout << "2 - ������� ���������� ��� ��������" << endl;
    cout << "3 - Գ����� ������������ ����������" << endl;
    cout << "4 - �������� ������������ ����������" << endl;
    cout << "5 - �������� ����� ��������" << endl;
    cout << "0 - ��������� ������ ��������" << endl;
    cout << "������: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: ";
    cin >> N;
    Students* S = new Students[N];

    string f_surname;
    int f_course;
    double f_average_evaluation;

    int MenuItem;

    while (true) {
        showMenu();
        cin >> MenuItem; cout << endl;

        switch (MenuItem) {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print(S, N);
            break;
        case 3:
            p_sort(S, N);
            Print(S, N);
            break;
        case 4:
            i_print(S, i_sort(S, N), N);
            break;
        case 5:
            cout << "������ ������ ������: " << endl;
            cout << "�������: ";
            cin.ignore();
            getline(cin, f_surname);
            cout << "����: ";
            cin >> f_course;
            cout << "������� ���: ";
            cin >> f_average_evaluation;

            if (b_search(S, N, f_surname, f_course, f_average_evaluation)) {
                cout << "�������� ��������" << endl;
            }
            else {
                cout << "�������� �� ��������" << endl;
            }
            break;
        case 0:
            delete[] S;
            return 0;
        default:
            cout << "������� ����� ����, ��������� �� ���." << endl;
        }
    }
}

// ������� ��������� ������ ��������
void Create(Students* S, const int N) {
    for (int i = 0; i < N; i++) {
        S[i] = {}; // ����������� ��� ���� ��������� �� �������������

        int speciality;
        cout << "����� ��������: " << i + 1 << endl;
        cin.ignore();
        cout << "�������: ";
        getline(cin, S[i].surname);

        do {
            cout << "����: ";
            cin >> S[i].course;
        } while (S[i].course < 1 || S[i].course > 6);

        do {
            cout << "������������ (0 - �����������, 1 - ��������������, 2 - ����'����� �����, 3 - ����'������ ��������, 4 - ��������� ������������): ";
            cin >> speciality;
            S[i].speciality = static_cast<Speciality>(speciality);
        } while (S[i].speciality < 0 || S[i].speciality > 4);

        do {
            cout << "������ � ������: ";
            cin >> S[i].grade_physics;
        } while (S[i].grade_physics < 1 || S[i].grade_physics > 5);

        do {
            cout << "������ � ����������: ";
            cin >> S[i].grade_math;
        } while (S[i].grade_math < 1 || S[i].grade_math > 5);

        do {
            cout << "������ � �����������: ";
            cin >> S[i].grade_info;
        } while (S[i].grade_info < 1 || S[i].grade_info > 5);
        cout << endl;
    }
}


// ���������� ���������� ���� ��� ��������
double student_average_evaluation(Students* S, int i) {
    return (S[i].grade_math + S[i].grade_physics + S[i].grade_info) / 3.0;
}

// ��������� ������ ��������
void Print(Students* S, const int N) {
    cout << "=================================================================================================" << endl;
    cout << "|  �  |   �������   |  ����  |     ������������     |  Գ����  |  ����������  |  �����������  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(10) << left << S[i].grade_physics;
        cout << "|" << setw(14) << left << S[i].grade_math;
        cout << "|" << setw(15) << left << S[i].grade_info << "|" << endl;
    }
    cout << "=================================================================================================" << endl << endl;
}

// Գ����� ���������� ��������
void p_sort(Students* S, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (student_average_evaluation(S, j) < student_average_evaluation(S, j + 1) ||
                (student_average_evaluation(S, j) == student_average_evaluation(S, j + 1) && S[j].course > S[j + 1].course) ||
                (student_average_evaluation(S, j) == student_average_evaluation(S, j + 1) && S[j].course == S[j + 1].course && S[j].surname < S[j + 1].surname)) {
                Students temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;
            }
        }
    }
}
// �������� ���������� ��������
int* i_sort(Students* S, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) I[i] = i;

    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;
        while (j >= 0 && (
            (student_average_evaluation(S, I[j]) < student_average_evaluation(S, value)) ||
            (student_average_evaluation(S, I[j]) == student_average_evaluation(S, value) && S[I[j]].course > S[value].course) ||
            (student_average_evaluation(S, I[j]) == student_average_evaluation(S, value) && S[I[j]].course == S[value].course && S[I[j]].surname < S[value].surname)
            )) {
            I[j + 1] = I[j];
            j--;
        }
        I[j + 1] = value;
    }
    return I;
}

// ��������� ������ �������� ���� ���������� ����������
void i_print(Students* S, int* I, const int N) {
    cout << "=================================================================================================" << endl;
    cout << "|  �  |   �������   |  ����  |     ������������     |  Գ����  |  ����������  |  �����������  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        int index = I[i];
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[index].surname;
        cout << "|" << setw(8) << left << S[index].course;
        cout << "|" << setw(23) << left << speciality_str[S[index].speciality];
        cout << "|" << setw(10) << left << S[index].grade_physics;
        cout << "|" << setw(14) << left << S[index].grade_math;
        cout << "|" << setw(15) << left << S[index].grade_info << "|" << endl;
    }
    cout << "=================================================================================================" << endl << endl;
}

// �������� �� ������ ���� ����� � �������
bool areDoublesEqual(double a, double b, double eps) {
    return fabs(a - b) < eps;
}

// �������� ����� �������� �� ��������, ������ �� ������� �����
bool b_search(Students* S, const int N, const string surname, const int course, const double average_evaluation) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        double avg = student_average_evaluation(S, middle);
        if (S[middle].surname == surname && S[middle].course == course && areDoublesEqual(avg, average_evaluation)) {
            return true;
        }
        else if (S[middle].surname < surname || (S[middle].surname == surname && (S[middle].course < course || (S[middle].course == course && avg < average_evaluation)))) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return false;
}
