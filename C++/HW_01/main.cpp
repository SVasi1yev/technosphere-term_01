#include <iostream>
#include <cmath>
#include "numbers.dat"

int bin_search_min (const int* arr, int size, int value) {
    int low_board = 0, high_board = Size - 1;
    int mid = high_board / 2;

    while (low_board < high_board) {
        if (value <= arr[mid]) {
            high_board = mid;
        } else {
            low_board = mid + 1;
        }
        mid = (high_board + low_board) / 2;
    }

    if (arr[mid] == value) {
        return mid;
    }

    return -1;
}

int bin_search_max (const int* arr, int size, int value) {
    int low_board = 0, high_board = Size - 1;
    int mid = ceil((double)high_board / 2);

    while (low_board < high_board) {
        if (value >= arr[mid]) {
            low_board = mid;
        } else {
            high_board = mid - 1;
        }
        mid = ceil(((double)high_board + low_board) / 2);
    }
    
    if (arr[mid] == value) {
        return mid;
    }

    return -1;
}

int count_prim(const int* data, size_t data_size, char* mask, size_t mask_size, 
    size_t first_ind, size_t second_ind) {
    if (mask_size - 1 < data[data_size - 1]) {
        return -1;
    }
    
    int count = 0;
    int high_board = data[second_ind];
    int high_board_sqrt = sqrt(high_board);
    for (int j = 2; j <= high_board; j++) {
        mask[j] = 1;
    }
    for (int j = 2; j <= high_board_sqrt; j++) {
        if(mask[j]) {
            for (int k = j * 2; k <= high_board; k += j) {
                mask[k] = 0;
            }
        }
    }
    for (int j = first_ind; j <= second_ind; j++) {
        count += mask[Data[j]];
    }

    return count;
}

int main (int argc, char* argv[]) {
    if ((argc % 2 == 0) || (argc == 1)) {
        return 255;
    }

    int mask_size = Data[Size - 1] + 1;
    char* mask = new char[mask_size];
    mask[0] = 0;
    mask[1] = 0;

    for (int i = 1; i < argc; i += 2) {
        int count = 0;
        int first_num = std::atoi(argv[i]);
        int second_num = std::atoi(argv[i + 1]);
        size_t first_ind = bin_search_min(Data, Size, first_num);
        size_t second_ind = bin_search_max(Data, Size, second_num);
        count = count_prim(Data, Size, mask, mask_size, first_ind, second_ind);
        std::cout << count << "\n";
    }

    delete[] mask;

    return 0;
}
