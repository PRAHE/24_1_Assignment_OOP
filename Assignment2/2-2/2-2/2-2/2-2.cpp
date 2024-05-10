#include <iostream>
#include <ctime>
using namespace std;

int separate(int* ran, int low, int high);
void quickSort(int* ran, int low, int high);
void Swap(int* low, int* high);
void merge(int* ran, int left, int mid, int right);
void mergeSort(int* ran, int left, int right);

int main() {
    int ran[11];
    int select;
    int search;
    bool found = 0;

    srand((unsigned)time(NULL));

    //fill random integers(0~100)
    for (int i = 0; i < 10; i++) {
        ran[i] = rand() % 101;
        for (int j = 0; j < i; j++) {
            if (ran[i] == ran[j])
                i--;
        }
    }

    cout << "Random values: ";
    for (int i = 0; i < 10; i++)
        cout << ran[i] << ' ';
    cout << endl;

    cout << "Select sorting method (1: Quick Sort, 2: Merge Sort): ";
    cin >> select;

    if (select == 1) {
        quickSort(ran, 0, 9);
        cout << "Sorted numbers (Quick Sort): ";
        for (int i = 0; i < 10; i++) {
            cout << ran[i] << ' ';
        }
        cout << endl;
    }
    else if (select == 2) {
        cout << "Sorted numbers (Merge Sort): ";
        mergeSort(ran, 0, 9);
        for (int i = 0; i < 10; i++) {
            cout << ran[i] << ' ';
        }
        cout << endl;
    }
    cout << "Enter a value to search: ";
    cin >> search;

    for (int i = 0; i < 10; i++) {
        if (ran[i] == search) {
            cout << "Searched number index: " << i << endl;
            found = 1;
            break;
        }
    }

    if (found == 0) {
        ran[10] = search;
        quickSort(ran, 0, 10);
        cout << "Updated numbers: ";
        for (int i = 0; i < 11; i++) {
            cout << ran[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}

//pivot�� �߽����� ����.
int separate(int* ran, int low, int high) {
    int pivot = ran[high];  //pivot ���� ����
    int i = low - 1;        // i�� low-1�� ����

    for (int j = low; j < high; j++) {
        if (ran[j] < pivot) { //pivot���� ������
            i++;
            Swap(&ran[i], &ran[j]);  // swap���� �̵�
        }
    }
    Swap(&ran[i + 1], &ran[high]); //swap���� �̵�
    return i + 1;  //pivot��ġ ��ȯ
}

//quickSort
void quickSort(int* ran, int low, int high) {
    if (low < high) {
        int site = separate(ran, low, high);  // �迭�� �����ϰ� pivot�� ��ġ�� �����ɴϴ�.

        quickSort(ran, low, site - 1);  // ���� �κ� �迭�� ��������� �����մϴ�.
        quickSort(ran, site + 1, high);  // ������ �κ� �迭�� ��������� �����մϴ�.
    }
}

//�����Լ�
void merge(int* ran, int left, int mid, int right) {
    int n1 = mid - left + 1;  //ù ��° �迭�� ũ��
    int n2 = right - mid;     //�� ��° �迭�� ũ��

    //�ӽ� �迭�� ����
    int tempL[10];
    int tempR[10];

    //�ӽ� �迭�� ������ ����
    for (int i = 0; i < n1; i++) {
        tempL[i] = ran[left + i];
    }
    for (int j = 0; j < n2; j++) {
        tempR[j] = ran[mid + 1 + j];
    }

    //�ӽ� �迭 ����
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (tempL[i] <= tempR[j]) {
            ran[k] = tempL[i];
            i++;
        }
        else {
            ran[k] = tempR[j];
            j++;
        }
        k++;
    }

    //������ ����
    while (i < n1) {
        ran[k] = tempL[i];
        i++;
        k++;
    }

    while (j < n2) {
        ran[k] = tempR[j];
        j++;
        k++;
    }
}

// MergeSort
void mergeSort(int* ran, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // �߰� ���� ���

        // �� �κ� �迭�� ��������� ����
        mergeSort(ran, left, mid);
        mergeSort(ran, mid + 1, right);

        //merge�� �̵�
        merge(ran, left, mid, right);
    }
}

//swap
void Swap(int* low, int* high) {
    int temp = *low; //�ӽ� �ּ� ����
    *low = *high; 
    *high = temp; //�ּ� swap
}

