#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>



void niz(wchar_t words[][100], int size) {
    for (int i = 0; i < size; i++) {
        wchar_t result[200];  
        wcscpy(result, L"");  
        wcscat(result, L"_");  
        wcscat(result, words[i]); 
        wcscat(result, L"_");  
        wcscpy(words[i], result); 
    }
}

int main() {
    system("chcp 65001");
    setlocale(LC_ALL, "en_US.UTF-8"); 

    int size;
    printf("Введите количество слов в массиве: ");
    scanf("%d", &size);

    wchar_t words[size][100];

    
    printf("Введите слова в массив:\n");
    for (int i = 0; i < size; i++) {
        wscanf(L"%ls", words[i]);
    }

    niz(words, size);

    
    printf("Измененный массив:\n");
    for (int i = 0; i < size; i++) {
        wprintf(L"%ls\n", words[i]);
    }

    return 0;
}
