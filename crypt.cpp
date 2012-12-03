//мне помогали=(
#include <stdio.h> 
#include <iostream>
#include <string.h>
#include <stdlib.h>

typedef unsigned int    uint;
typedef unsigned char   uchar;

using namespace std;

enum mode {encode,decode};
// charChange()
int mod(int num,int abs) // <=> num % abs, для отрицательных чисел, (-1 % 55 получалось 31, нужно  54, прибавляем к -1 55, пока не получится положительное число, а потом уже % это число на 55, где 55 - длина алфавита)
{
    while(num < 0) num+=abs;
    return num%abs; 
}


void showHelp(){
    cout << "$ crypt [options] <key> <source> [<dest>]\n\n";
    cout << "options:\n";
    cout << "\t-a, --alphabet=<alphabet>  alphabet — алфавит для работы алгоритма (по умолчанию\n";
    cout << "\t                                      содержит буквы из латниского алфавита и цифры: AaBbCc..Zz0..9)\n"; 
    cout << "\t-t, --type=<type>                     type может быть 'encode' или 'decode', по умолчанию — encode\n";
    cout << "\t-h, --help                            выводит эту справку\n\n";
    cout << "key:\n";
    cout << "\tключ для шифрования/дешифрования\n\n";
    cout << "source:\n";
    cout << "\tисходный файл для шифрования/дешифрования\n\n";
    cout << "dest:\n";
    cout << "\tфайл, куда будет записан новый, зашифрованный текст. Если не указан, то переписывает source\n\n";
}
int main(int argc, char*argv[]){
    char key;
    char symbol;
    int keyIndex,index;
    bool files=false;
    mode type; 
    string alphabet="AaBbCcDdEeFfGgHhIiKkLlMmNnOoPpQqRrSsTtVvXxYyZz0123456789";//алфавит
    string tmp;
    FILE *inputFile; //переменная для хранения входного файла
    FILE *outputFile; // храниться выходные данные
    if(argc == 2)//если число аргументов равно 2
        if((!(strcmp(argv[1],"-h"))) or (!(strcmp(argv[1],"--help")))){
            showHelp();
            return 0;
        }
        else{
            cout << "Ошибка!" << endl;
            return -1;
        }
    if(argc > 2)
        for(int i=1; i<argc; i++){ //проходим по всем параметрам  
    if((strcmp(argv[i],"-a"))){
        alphabet=argv[i+1];
        i++;
    }
    if((strstr(argv[i],"--alphabet"))){
        string a=argv[i];
        for(int t=11;t<a.length();t++){
          alphabet+=a[t];  
        }
    }
    if((strcmp(argv[i],"-t"))){
        if(strcmp(argv[i+1],"encode")){
            type=encode;
        }
        else if(strcmp(argv[i+1],"decode")){  
            type=decode;
        }
        i++;
    }
    if((strstr(argv[i],"--type"))){
        string f=argv[i];
        string n=f.erase(0,7);
        if(n == "encode"){
            type=encode;
        }
        else if(n == "decode"){  
            type=decode;
        }
    }
    if(key = atoi(argv[i]))
    {
        if (key < 1)
        {
            cout << "Неправильно заданы аргументы " << endl;
             return -1;                
        }
        keyIndex = i;
        break;
    }
    else
    {
        cout << "Неправильно заданы аргументы " << endl;
        return -1;
    }


    if (!(inputFile = fopen(argv[keyIndex+1],"r+"))) //если не окрыли файл для чтения и перезаписи
        {
            printf("%s\n", "Bad file. Does it exist?");
            return -1;
        }
    else 
    {
        if (keyIndex == (argc-3))              //если ключ argv[argc-3]
        {                           //then source in argv[argc-2]
           if (!(outputFile = fopen(argv[keyIndex+2],"w")))
            {
                printf("%s\n", "Bad file. Does it exist?");
                return -1;
            }
            files=true;                 //flag. файлы не совпадают
        }
        else
        {
            outputFile = inputFile;//входной и выходной файл совпадают
        }
    }
    
    // если декодирование мы меняем ключ на противоположный
    if(type == decode) key *= -1;
    while((symbol=fgetc(inputFile)) != EOF)            //читаем символы до когца файла
        if(!(files)) fseek ( outputFile , -1 , SEEK_CUR );    //если файлы не совпадают, то перемещаем указатель для обновления символа
        if((index = alphabet.find(symbol)) +1)      //ищем символ в алфавите изаписываем в индекс
        {
            //change it! mod(a,b) <=> a % b
            symbol=alphabet[mod((index + key),alphabet.length())];
        }
        fputc(symbol,outputFile);
    }
    
    fclose(inputFile);
    if(files) fclose(outputFile); //if the files does not match, then close second file
    return 0;
}

}