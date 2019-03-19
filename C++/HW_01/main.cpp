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

char* make_sieve(int max_num, int& sieve_size) {
    sieve_size = max_num + 1;
    char* sieve = new char[max_num + 1];
    sieve[0] = 0;
    sieve[1] = 0;
    int max_sqrt = sqrt(max_num);
    for (int i = 2; i <= max_num; i++) {
        sieve[i] = 1;
    }
    
    for (int i = 2; i <= max_sqrt; i++) {
        if (sieve[i]) {
            for (int j = i * 2; j <= max_num; j += i) {
                sieve[j] = 0;
            }
        }
    }

    return sieve;
}

int count_prim(const int* data, size_t data_size, char* sieve, size_t sieve_size, 
    size_t first_ind, size_t second_ind) {
    int count = 0;
    for (int j = first_ind; j <= second_ind; j++) {
        count += sieve[data[j]];
    }

    return count;
}

int main (int argc, char* argv[]) {
    if ((argc % 2 == 0) || (argc == 1)) {
        return 255;
    }

    int* int_args = new int[argc - 1];
    int max = 0;
    for (int i = 1; i < argc; i++) {
        int_args[i - 1] = std::atoi(argv[i]);
        if (int_args[i - 1] > max) {
            max = int_args[i - 1];
        }
    }

    int seive_size = 0;
    char* seive = make_sieve(max, seive_size);

    for (int i = 0; i < argc - 1; i += 2) {
        int count = 0;
        int first_num = int_args[i];
        int second_num = int_args[i + 1];
        size_t first_ind = bin_search_min(Data, Size, first_num);
        size_t second_ind = bin_search_max(Data, Size, second_num);
        count = count_prim(Data, Size, seive, seive_size, first_ind, second_ind);
        std::cout << count << "\n";
    }

    delete[] int_args;
    delete[] seive;

    return 0;
}