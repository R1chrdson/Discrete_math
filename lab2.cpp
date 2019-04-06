#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

/*int variant[7][10] = 
{
    {1, 0, 0, 1, 0, 1, 1, 0, 1, 3},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 2},
    {0, 1, 1, 0, 1, 0, 0, 1, 0, 3},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 2},
    {0, 0, 1, 1, 0, 0, 0, 0, 1, 1}
};*/
    int variant[10][10] = 
{
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 1, 0, 1, 1, 0, 1},
    {0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
    {1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
};
string prefix[10] = {"А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "Й", "К"};

pair<int, vector<int>> maxRow(vector<int> RowIndex, vector<int> Cols)
{
    int maxRow = 0, rIndex;
    vector<int> ColsToDelete;
    for(int i = 0; i < RowIndex.size(); i++)
    {
        int rowCounter = 0;
        vector<int> ColsIndex;
        for(int j = 0; j < Cols.size(); j++)
        {
            if(variant[RowIndex[i]][Cols[j]] == 1)
            {
                rowCounter++;
                ColsIndex.push_back(Cols[j]);
            }
        }
        if(rowCounter > maxRow)
        {
            maxRow = rowCounter;
            ColsToDelete = ColsIndex;
            rIndex = RowIndex[i];
        }
    }
    pair<int, vector<int>> RowData(rIndex, ColsToDelete);
    return RowData;
}

int reduce(pair<int, vector<int>> RowData, vector<int>& Cols, vector<int>& Rows)
{
    for(int i = 0; i < RowData.second.size(); i++)
    {
        Cols.erase(remove(Cols.begin(), Cols.end(), RowData.second[i]), Cols.end());
    }
    if(RowData.first != -1)
    {
    Rows.erase(remove(Rows.begin(), Rows.end(), RowData.first), Rows.end());
    }
    return RowData.first;
}

vector<int> minColMaxRow(vector<int> Cols, vector<int> Rows)
{
    vector<int> coverIndex;
    while(!Cols.empty())
    {
        int minCols = INT16_MAX;
        vector<int> minRowIndex;
        for(int i = 0; i < Cols.size(); i++)
        {
            int ColsCounter = 0;
            vector<int> RowIndex;
            for(int j = 0; j < Rows.size(); j++)
            {
                if(variant[Rows[j]][Cols[i]] == 1)
                {
                ColsCounter++;
                RowIndex.push_back(Rows[j]);
                }
            }
            if(ColsCounter < minCols)
            {
                minCols = ColsCounter;
                minRowIndex = RowIndex;
            }
        }
        coverIndex.push_back(reduce(maxRow(minRowIndex, Cols), Cols, Rows));
    }
    return coverIndex;
}

bool isEmbrace(bool isRow, int indexFirst, int indexSecond, vector<int> Cols, vector<int> Rows)
{
    if(isRow)
    {
        for(int i = 0; i < Cols.size(); i++)
        {
            if(variant[indexFirst][Cols[i]] == 0 && variant[indexSecond][Cols[i]] == 1)
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        for(int i = 0; i < Rows.size(); i++)
        {
            if(variant[Rows[i]][indexFirst] == 0 && variant[Rows[i]][indexSecond] == 1)
            {
                return false;
            }
        }
        return true;
    }
}

vector<int> getN(vector<int>& Cols, vector<int>& Rows)
{
    vector<int> coreRows;
    pair<int, vector<int>> RowData;
    for(int i = 0; i < Cols.size(); i++)
    {
        int counter = 0, MarkedRow;
        for(int j = 0; j < Rows.size(); j++)
        {   
            if(variant[Rows[j]][Cols[i]] == 1)
            {
                if(counter == 0)
                {
                    counter++;
                    MarkedRow = Rows[j];
                }
                else
                {
                    counter = -1;
                    break;
                }
            }
        }
        if(counter == 1)
        {
            coreRows.push_back(Rows[MarkedRow]);
        }
    }
    for(int i = 0; i < coreRows.size(); i++)
    {
        RowData.first = coreRows[i];
        for(int j = 0; j < Cols.size(); j++)
        {
            if(variant[Rows[RowData.first]][Cols[j]] == 1)
            {
                RowData.second.push_back(Cols[j]);
            }
        }
        reduce(RowData, Cols, Rows);
        RowData.second.clear();
    }
    return coreRows;
}

vector<int> core(vector<int> Cols, vector<int> Rows)
{
    int rSizeF, rSizeL, cSizeF, cSizeL;
    vector<int> coreRows;
        do
        {
        vector<int> skip;
        rSizeF = Rows.size(); cSizeF = Cols.size();
        vector<int> getCoreRows = getN(Cols, Rows);
        coreRows.insert(coreRows.end(), getCoreRows.begin(), getCoreRows.end());
        vector<int> Anti;
        pair<int, vector<int>> RowData;
        for(int i = 0; i < Rows.size(); i++)
        {
            bool isAnti = true;
            for(int j = 0; j < Cols.size(); j++)
            {
                if(variant[Rows[i]][Cols[j]] == 1)
                {
                    isAnti = false;
                    break;
                }
            }
            if(isAnti)
            {
                Anti.push_back(Rows[i]);
            }
        }
        for(int i = 0; i < Anti.size(); i++)
        {
            RowData.first = Anti[i];
            reduce(RowData, Cols, Rows);
        }
        vector<int> embracingCols;
        for(int i = 0; i < Cols.size(); i++)
        {
            for(int j = 0; j < Cols.size(); j++)
            {
                if((j != i) && !(find(skip.begin(), skip.end(), Cols[i]) != skip.end()) && !(find(skip.begin(), skip.end(), Cols[j]) != skip.end()))
                {
                    if(isEmbrace(0, Cols[i], Cols[j], Cols, Rows))
                    {
                        skip.push_back(Cols[i]);
                        embracingCols.push_back(Cols[i]);
                    }
                }
            }
        }
        RowData.first = -1; skip.clear();
        RowData.second = embracingCols;
        reduce(RowData, Cols, Rows);
        RowData.second.clear();
        vector<int> embracedRows;
        for(int i = 0; i < Rows.size(); i++)
        {
            for(int j = 0; j < Rows.size(); j++)
            {
                if((j != i) && !(find(skip.begin(), skip.end(), Rows[j]) != skip.end()) && !(find(skip.begin(), skip.end(), Rows[i]) != skip.end()))
                {
                    if(isEmbrace(1, Rows[j], Rows[i], Cols, Rows))
                    {
                        skip.push_back(Rows[i]);
                        embracedRows.push_back(Rows[i]);
                    }
                }
            }
        }
        for(int i = 0; i < embracedRows.size(); i++)
        {
            RowData.first = embracedRows[i];
            reduce(RowData, Cols, Rows);
        }
        rSizeL = Rows.size(); 
        cSizeL = Cols.size();
    } while((rSizeL != rSizeF) && (cSizeL != cSizeF));
    if(Cols.size() == 0)
    {
        return coreRows;
    }
    else
    {
        vector<int> cycle = minColMaxRow(Cols, Rows);
        coreRows.insert(coreRows.end(), cycle.begin(),  cycle.end());
        return coreRows;
    }
}

void result(bool method, vector<int> coverVector)
{
    string cover = "";
    for(int i = 0; i < coverVector.size(); i++)
    {
        cover += prefix[coverVector[i]];
    }
    printf("Покриття знайдене за методом %s: %s\n", (method)?"ядерних рядків":"мінімального стовпчика - максимального рядка", cover.c_str());
}

int main(void)
{
    vector<int> Cols = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> Rows = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    result(0, minColMaxRow(Cols, Rows));
    result(1, core(Cols, Rows));
}