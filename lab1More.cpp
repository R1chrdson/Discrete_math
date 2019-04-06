#include <iostream>
#include <stdio.h>
#include <list>
#include <math.h>

using namespace std;

int variant[7][10] = 
{
    {1, 0, 0, 0, 0, 1, 1, 0, 1, 3},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 2},
    {0, 1, 1, 0, 1, 0, 0, 1, 0, 3},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 2},
    {0, 0, 1, 1, 0, 0, 0, 0, 1, 1}
};

string prefix[7] = {"А", "Б", "В", "Г", "Д", "Е", "Ж"};
int counterFull = 0;
bool isWrong = true;
bool isMethod = true;
list<int> minPriceFull;
list<int> minRepeatsFull;
list<int> minPriceLimit;
list<int> minRepeatsLimit;
list<list<int>> uniqueLimit;
int mPriceF = INT16_MAX;
int mRepeatsF = INT16_MAX;
int mPriceL = INT16_MAX;
int mRepeatsL = INT16_MAX;

bool isCover(list<int> args)
{
    list<int> argsCopy = args;
    int tmp[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    string rowPrefix = "";
    int repeats = 0, price = 0;
    while (!args.empty())
    {
        int index = args.front();
        rowPrefix += prefix[index];
        price += variant[index][9];
        for (int i = 0; i < 9; i++)
        {
            if (tmp[i] == 1 && tmp[i] == variant[index][i])
            {
                repeats++;
            }
            else if (variant[index][i] == 1)
            {
                tmp[i] = 1;
            }
        }
        args.pop_front();    
    }
    for (int i = 0; i < 9; i++)
    {
        if (tmp[i] == 0)
        {
            return false;
        }
    }
    if (isMethod)
    {
        if (price < mPriceF)
        {
            mPriceF = price;
            minPriceFull = argsCopy;
        }
        if (repeats < mRepeatsF)
        {
            mRepeatsF = repeats;
            minRepeatsFull = argsCopy;
        }
    }
    else
    {
        if (price < mPriceL)
        {
            mPriceL = price;
            minPriceLimit = argsCopy;
        }
        if (repeats < mRepeatsL)
        {
            mRepeatsL = repeats;
            minRepeatsLimit = argsCopy;
        }
    }
    printf("%s(%i; %i)\n", rowPrefix.c_str(), price, repeats);
    return true;
}

bool isSimilar(list<int> toCompare, list<int> combination)
{
    int sComp = toCompare.size();
    toCompare.merge(combination);
    int sCompComb = toCompare.size();
    toCompare.unique();
    int sUnique = toCompare.size();

    if (abs(sComp - sCompComb) == sUnique)
    {
        return true;
    }
    return false;
}

void isUnique(list<int> combination)
{
    bool unique = true;
    for (const auto& iterator : uniqueLimit)
    {
        if (isSimilar(iterator, combination) == true)
        {
            unique = false;
        }
    }
    if (unique == true)
    {
        uniqueLimit.push_back(combination);
    }
}

void getCombination(int size, int dataIndex, int data[], int rowIndex)
{
    if (dataIndex == size)
    {
        list<int> combination;
        for (int i = 0; i < size; i++)
        {
            combination.push_back(data[i]);
        }
        if (isCover(combination) == true)
        {
            isUnique(combination);
            counterFull++;
            isWrong = false;
        }
        combination.clear();
        return;
    }

    if (rowIndex >= 7)
    {
        return;
    }

    data[dataIndex] = rowIndex;
    getCombination(size, dataIndex + 1, data, rowIndex + 1);
    getCombination(size, dataIndex, data, rowIndex + 1);
}

void getList(int size)
{
    int data[size];
    getCombination(size, 0, data, 0);
}

void printResult(bool fg, list<int> minPrice, list<int> minRepeats, int counter)
{
    string method = (fg == true)?" повного ":" граничного ";
    cout << endl;
    cout << "Покриття з найменшою ціною (за методом" << method << "перебору) - ";
    isCover(minPrice);
    cout << "Найкоротше покриття (за методом" << method << "перебору) - ";
    isCover(minRepeats);
    cout << "Кількість покриттів методом" << method << "перебору: " << counter << endl;
}

int main()
{
    for (int i = 1; i <= 7; i++)
    {
        getList(i);
    }
    if (isWrong)
    {
    cout << "Не існує покриття множини" << endl;
    }
    else
    {
        isMethod = false;
        cout << endl;
        for (auto& iterator : uniqueLimit)
        {
            isCover(iterator);
        }
        cout << endl << "Висновок: " << endl;
        printResult(true, minPriceFull, minRepeatsFull, counterFull);
        printResult(false, minPriceLimit, minRepeatsLimit, uniqueLimit.size());
    }
}Л