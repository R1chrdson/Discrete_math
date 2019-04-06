#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

vector<int> variant = {1, 2, 5, 6, 9, 10, 11, 12};

vector<array<int, 4>> getImplicant(vector<int> input)
{
    vector<array<int, 4>> output;
    for(int i = 0; i < input.size(); i++)
    {
        array<int, 4> binaryNumber;
        binaryNumber.fill(0);
        int j = 3;
        if(input[i] > 16)
        {
            fprintf(stderr, "This digit have more than 4 variables\nUse digits <= 16\n");
            exit(1);
        }
        while(input[i] != 0)
        {
            (input[i] % 2 == 0)?binaryNumber[j] = 0:binaryNumber[j] = 1;
            input[i] /= 2;
            j--;
        }   
        output.push_back(binaryNumber);
    }
    return output;
}

bool simplifyed(array<int, 4> first, array<int, 4> second, array<int, 4> container)
{
    // TODO

    /*
    * SENCE OF THIS FUNCTION
    * This function have 2 arrays, and counts difference of arrays
    * if we have 1 different element then return true
    * else return false;
    */
    return false;
}

void reduceImplicant(vector<array<int, 4>> container, vector<int> elements)
{
    for(int i = 0; i < elements.size(); i++)
    {
        container.erase(remove(container.begin(), container.end(), elements[i]), container.end());
    }
}

vector<array<int, 4>> simplify(vector<array<int, 4>> input)
{
    int size = input.size();
    vector<array<int, 4>> output;
    vector<int> toDelete;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            array<int, 4> element;
            if(simplifyed(input[i], input[j], element))
            {
                if(!element.empty())
                {
                    output.push_back(element);
                }
                else
                {
                    break;
                }
            }
            toDelete.push_back(i); toDelete.push_back(j);
        }
    }
    reduceImplicant(input, toDelete);
    output.insert(output.end(), input.begin(), input.end());
    return output;

}


int main(void)
{
    vector<array<int, 4>> implicant, simple;
    implicant = getImplicant(variant);
    simple = implicant;
    int prevSize;
    while(prevSize != simple.size()) 
    {
        prevSize = simple.size();
        simple = simplify(implicant);
    }
    /*
    * TODO LIST
    * 1) Todo simlifyed function
    * 2) Implement table of covers where rows are simlifyer and cols are implicant
    * 3) Calculate cover
    * 4) Print out result in DNF form (create new function to convert binary to func.form indside result func)
    */
}