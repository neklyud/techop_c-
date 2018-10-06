//Runid = 1016
//Задача A-9. Задача об отображении темы письма
// Чтобы показать информацию о пришедшем письме, нужно сначала её найти.
// Для этого в файле письма необходимо найти специальные заголовки.
// Составить программу построчной фильтрации текста.
// Суть фильтра — отбор строк, начинающихся с одного из следующих выражений:
// «Date:», «From:»,«To:», «Subject:».
// Текстовые строки подаются на стандартный ввод программы, результат программы
// должен подаваться на стандартный вывод.
// Процедура фильтрации должна быть оформлена в виде отдельной функции, которой
// подается на вход массив строк, выделенных в динамической памяти и его длина.
// На выходе функция возвращает указатель на NULL-терминированный массив с
//найденными строками (последним элементом массива добавлен NULL для
//обозначения, что данных больше нет).
// Программа должна уметь обрабатывать возникающие ошибки (например, ошибки
// выделения памяти).
// В случае возникновения ошибки нужно вывести в поток стандартного вывода
// сообщение "[error]" и завершить выполнение программы.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DATE "Date"
#define SUBJECT "Subject"
#define TO "To"
#define FROM "From"

void print(char **strings, size_t length) {
    int i = 0;
    for (i = 0; strings[i][0] != '\0'; i++) {
        int strLength = strlen(strings[i]);
        for (int j = 0; j < strLength; j++)
            printf("%c", (char)strings[i][j]);
        printf("\n");
    }
}

char *reallocing(char *string, size_t size) {
    char *swipe;
    swipe = NULL;
    swipe = (char *)realloc(string, sizeof(char) * size);
    if (swipe != NULL)
        string = swipe;
    else
        return NULL;
    return string;
}

char **fullReallocing(char **strings, size_t columnSize, size_t stringSize) {
    strings = (char **)realloc(strings, sizeof(char *) * columnSize);
    for (int i = 0; i < columnSize; i++) {
        strings[i] = reallocing(strings[i], stringSize * sizeof(char));
        if (strings[i] == NULL)
            return NULL;
    }
    return strings;
}

char *writeString(char *string, size_t columnSize, size_t stringSize) {
    int i = 0;
    for (i = 0; i < stringSize; i++) {
        string[i] = 0;
        scanf("%c", &string[i]);
        if (i == stringSize - 1 && string[i] != '\0' && string[i] != '\n' && string[i] != EOF) {
            string = reallocing(string, stringSize * 2);
            if (string == NULL)
                return NULL;
            stringSize = stringSize * 2;
        }
        else if (i < stringSize && (string[i] == EOF || string[i] == '\0' || string[i] == '\n'))
            break;
    }
    string[i] = '\0';
    return string;
}

int input(char **strings, size_t columnSize, size_t stringSize) {
    int i = 0;
    for (i = 0; i < columnSize; i++) {
        if (feof(stdin))
            break;
        if (i == columnSize - 1 && !feof(stdin)) {
            strings = fullReallocing(strings, columnSize * 2, stringSize);
            if (strings == NULL)
                return -1;
            columnSize = columnSize * 2;
        }
        strings[i] = writeString(strings[i], columnSize, stringSize);
    }
    return columnSize;
}

char **allocing(char **string, size_t columnSize, size_t stringSize) {
    /*Data alloced*/
    int i = 0;
    char **swipe;
    char *swipe_string = NULL;
    string = NULL;
    swipe = NULL;
    swipe = (char **)calloc(columnSize, sizeof(char *));
    if (swipe == NULL) {
        return NULL;
    }
    string = swipe;
    for (i = 0; i < columnSize; i++) {
        string[i] = NULL;
        swipe_string = NULL;
        swipe_string = (char *)calloc(stringSize + 1, sizeof(char));
        if (swipe_string == NULL)
            return NULL;
        string[i] = swipe_string;
    }
    return string;
}

int isValidKeyWord(char *keyWordMassive) {
    if (!strcmp(keyWordMassive, FROM) || !strcmp(keyWordMassive, TO) || !strcmp(keyWordMassive, SUBJECT) || !strcmp(keyWordMassive, DATE))
        return 1;
    return 0;
}

int checkString(const char *string) {
    int i = 0;
    int MAX_SIZE_OF_KEY_WORD = 9;
    char keyWordMassive[MAX_SIZE_OF_KEY_WORD];
    while (string[i] && string[i] != ':') {
        if (i == 9)
            break;
        keyWordMassive[i] = string[i];
        i++;
    }
    keyWordMassive[i] = '\0';
    return isValidKeyWord(keyWordMassive);
}

char **filterStrings(char **strings, char **filteredStrings, size_t columnSize, size_t stringSize, int *allocated_mem) {
    int i = 0;
    int j = 0;
    int n = 0;
    while (strings[i]) {
        if (*allocated_mem == columnSize - 1 && strings[i][0])
            *allocated_mem = *allocated_mem * 2;
        if (j == columnSize - 1 && strings[i][0] != '\0') {
            filteredStrings = fullReallocing(filteredStrings, columnSize * 2, stringSize);
            if (filteredStrings == NULL)
                return NULL;
            columnSize = columnSize * 2;
        }
        if (checkString(strings[i])) {
            n = strlen(strings[i]);
            filteredStrings[j] = reallocing(filteredStrings[j], n + 1);
            if (filteredStrings[i] == NULL)
                return NULL;
            strncpy(filteredStrings[j++], strings[i], n);
            filteredStrings[j - 1][n] = '\0';
        }
        if (!strcmp(strings[i], "\0"))
            break;
        i++;
    }
    filteredStrings[j][0] = '\0';
    return filteredStrings;
}

void freeMem(char **string, size_t size) {
    for (int i = 0; i < size; i++)
        free(string[i]);
    free(string);
}

int main() {
    /*main function*/
    size_t stringSize = 16, columnSize = 16;
    char **strings = NULL;
    char **filteredStrings = NULL;
    int stringsLength = 0;
    int filteredStringsLength = 0;
    int allocatedForFilter = columnSize;
    if ((strings = allocing(strings, columnSize, stringSize)) == NULL) {
        printf("[error]\n");
        return 0;
    }
    if ((filteredStrings = allocing(strings, columnSize, stringSize)) == NULL) {
        printf("[error]\n");
        return 0;
    }
    if ((stringsLength = input(strings, columnSize, stringSize)) == -1) {
        freeMem(strings, stringsLength);
        printf("[error]\n");
        return 0;
    }
    if ((filteredStrings = filterStrings(strings, filteredStrings, columnSize, stringSize, &allocatedForFilter)) == NULL) {
        freeMem(strings, stringsLength);
        freeMem(filteredStrings, allocatedForFilter);
        printf("[error]\n");
        return 0;
    }
    print(filteredStrings, filteredStringsLength);
    freeMem(strings, stringsLength);
    freeMem(filteredStrings, allocatedForFilter);
    return 0;
}
