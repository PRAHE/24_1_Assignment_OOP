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

//pivot을 중심으로 나눔.
int separate(int* ran, int low, int high) {
    int pivot = ran[high];  //pivot 임의 설정
    int i = low - 1;        // i를 low-1로 설정

    for (int j = low; j < high; j++) {
        if (ran[j] < pivot) { //pivot보다 작으면
            i++;
            Swap(&ran[i], &ran[j]);  // swap으로 이동
        }
    }
    Swap(&ran[i + 1], &ran[high]); //swap으로 이동
    return i + 1;  //pivot위치 반환
}

//quickSort
void quickSort(int* ran, int low, int high) {
    if (low < high) {
        int site = separate(ran, low, high);  // 배열을 분할하고 pivot의 위치를 가져옵니다.

        quickSort(ran, low, site - 1);  // 왼쪽 부분 배열을 재귀적으로 정렬합니다.
        quickSort(ran, site + 1, high);  // 오른쪽 부분 배열을 재귀적으로 정렬합니다.
    }
}

//병합함수
void merge(int* ran, int left, int mid, int right) {
    int n1 = mid - left + 1;  //첫 번째 배열의 크기
    int n2 = right - mid;     //두 번째 배열의 크기

    //임시 배열들 생성
    int tempL[10];
    int tempR[10];

    //임시 배열에 데이터 복사
    for (int i = 0; i < n1; i++) {
        tempL[i] = ran[left + i];
    }
    for (int j = 0; j < n2; j++) {
        tempR[j] = ran[mid + 1 + j];
    }

    //임시 배열 병합
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

    //나머지 복사
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
        int mid = left + (right - left) / 2;  // 중간 지점 계산

        // 두 부분 배열을 재귀적으로 정렬
        mergeSort(ran, left, mid);
        mergeSort(ran, mid + 1, right);

        //merge로 이동
        merge(ran, left, mid, right);
    }
}

//swap
void Swap(int* low, int* high) {
    int temp = *low; //임시 주소 저장
    *low = *high; 
    *high = temp; //주소 swap
}

