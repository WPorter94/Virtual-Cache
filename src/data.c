#include <data.h>
#include <stdio.h>
#include <stdlib.h>

int convertCharToNumber(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }
    else if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    }
    else {
        return -1;
    }
}

char convertNumberToChar(int n) {
    if (n >= 0 && n <= 9) {
        return n + '0';
    }
    else if (n >= 10 && n <= 15) {
        return n - 10 + 'A';
    }
    else {
        return 0;
    }
}

Data convert_to_base_n(Data src, unsigned char n) {
    Data new_data;
    new_data.data = NULL;
    DataNode* curr = src.data;
    int num = 0;
    int digit = 1;
    int size = 0;
    int tempsize = src.len;
    int* arr = malloc(src.len * sizeof(char));
    for (int a = 0; a < src.len; a++) {
        arr[a] = convertCharToNumber(curr->number);
        curr = curr->next;
    }
    for (int i = src.len - 1; i >= 0; i--) {
        num += arr[i] * digit;
        digit = digit * src.base;
    }
    int copy = num;
    while (copy > 0) {
        copy /= n;
        size++;
    }
    char* newNums = malloc(size * sizeof(char));
    for (int b = 0; b < size; b++) {
        newNums[b] = convertNumberToChar(num % n);
        num /= n;
    }
    new_data.data = createLL(newNums, size-1);
    new_data.len = size;
    new_data.base = n;
    new_data.sign = src.sign;
    new_data.number_bits = src.number_bits;
    return new_data;
}

int convert_to_int(Data src) {
    // TODO
    return 0;
}

Data left_shift(Data src, int n) {
    Data new_data;
    // TODO
    return new_data;
}

Data right_shift(Data src, int n) {
    Data new_data;
    // TODO
    return new_data;
}
DataNode* createLL(char nums[], int size) {
    DataNode *temp = malloc(sizeof(DataNode));
    
    if (size > 0) {
        temp->number = nums[size];
        
        temp->next = createLL(nums, size - 1);
    }else{
        temp->number = nums[0];
        temp->next = NULL;
    }
    return temp;

}