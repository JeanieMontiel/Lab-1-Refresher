/* #1 Refresher - Menu Driven
Student: Jeanie Montiel
Date: Feb. 25, 2026
Course: CS216


-Read numbers from input file ONCE (may be empty).
-Store:
* divisible by 3  -> arr3
* else if divisible by 7 -> arr7
* else -> arrOther

- Switch:
1. Print each array + sum/avg/med
2. Printer each array decending
3. Quit and write array + stats to output file

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// GLOBAL CONSTANTS (allowed by specification)
// File names must be hard-coded and global const (per assignment)
const string INPUT_FILE_NAME  = "inputFile";
const string OUTPUT_FILE_NAME = "outputFile";

// Fixed maximum array size (can be changed in ONE place)
const int MAX_SIZE = 200;

// FUNCTION PROTOTYPES
void printMenu();
int  getMenuChoice();
void clearInputError(const string& message);

void readInputFile(int arr3[], int& size3,
                   int arr7[], int& size7,
                   int arrRest[], int& sizeRest);

long long computeSum(const int arr[], int size);
double computeAverage(const int arr[], int size);
void copyArray(const int source[], int destination[], int size);
void bubbleSort(int arr[], int size, bool descending);
double computeMedianSorted(const int sortedArr[], int size);

void printApprovedFormat(ostream& out,
                         const int arr[],
                         int size,
                         const string& label);

void optionPrintAll(const int arr3[], int size3,
                    const int arr7[], int size7,
                    const int arrRest[], int sizeRest);

void writeOutputFile(const int arr3[], int size3,
                     const int arr7[], int size7,
                     const int arrRest[], int sizeRest);

// MAIN FUNCTION

int main()
{
    // Arrays are statically allocated (no dynamic memory allowed)
    int arrDiv3[MAX_SIZE];
    int arrDiv7[MAX_SIZE];
    int arrRest[MAX_SIZE];

    // Track how many elements were actually stored
    int size3 = 0;
    int size7 = 0;
    int sizeRest = 0;

    // Read the file ONCE at program start
    readInputFile(arrDiv3, size3, arrDiv7, size7, arrRest, sizeRest);

    int choice = 0;

    // Menu loop continues until user selects Quit (3)
    while (choice != 3)
    {
        printMenu();
        choice = getMenuChoice();

        switch (choice)
        {
            case 1:
                optionPrintAll(arrDiv3, size3,
                               arrDiv7, size7,
                               arrRest, sizeRest);
                break;

            case 2:
                // Just reuse same function but it prints descending as well
                optionPrintAll(arrDiv3, size3,
                               arrDiv7, size7,
                               arrRest, sizeRest);
                break;

            case 3:
                writeOutputFile(arrDiv3, size3,
                                arrDiv7, size7,
                                arrRest, sizeRest);
                cout << "\nQuitting and writing to file...\n";
                break;

            default:
                cout << "Invalid input. Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}


// MENU FUNCTIONS

void printMenu()
{
    // Displays user options
    cout << "\n========== Menu ==========\n";
    cout << "1) Print and Find Average, Median, and Sum\n";
    cout << "2) Print Values in Decreasing Order\n";
    cout << "3) Quit and Exit\n";
}

int getMenuChoice()
{
    int choice;
    cin >> choice;

    // Validate numeric input
    while (cin.fail())
    {
        clearInputError("Menu choice must be a number.");
        cin >> choice;
    }

    return choice;
}

void clearInputError(const string& message)
{
    // Clears error state and removes invalid input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << message << endl;
}


// FILE READING FUNCTION

void readInputFile(int arr3[], int& size3,
                   int arr7[], int& size7,
                   int arrRest[], int& sizeRest)
{
    ifstream fin(INPUT_FILE_NAME);

    // Initialize sizes
    size3 = size7 = sizeRest = 0;

    if (!fin.is_open())
    {
        cout << "Error opening input file.\n";
        return;
    }

    int value;

    // Read until EOF (only once)
    while (fin >> value)
    {
        // Negative numbers and zero work correctly with modulus
        if (value % 3 == 0)
        {
            if (size3 < MAX_SIZE)
                arr3[size3++] = value;
        }
        else if (value % 7 == 0)
        {
            if (size7 < MAX_SIZE)
                arr7[size7++] = value;
        }
        else
        {
            if (sizeRest < MAX_SIZE)
                arrRest[sizeRest++] = value;
        }
    }

    fin.close();
}


// STATISTICAL FUNCTIONS

long long computeSum(const int arr[], int size)
{
    long long sum = 0;

    // Accumulate total safely using long long
    for (int i = 0; i < size; i++)
        sum += arr[i];

    return sum;
}

double computeAverage(const int arr[], int size)
{
    // Precondition: size > 0 (caller must check)
    return static_cast<double>(computeSum(arr, size)) / size;
}

void copyArray(const int source[], int destination[], int size)
{
    // Used so sorting does not destroy original order
    for (int i = 0; i < size; i++)
        destination[i] = source[i];
}

void bubbleSort(int arr[], int size, bool descending)
{
    // Bubble sort required by assignment
    for (int pass = 0; pass < size - 1; pass++)
    {
        for (int i = 0; i < size - pass - 1; i++)
        {
            bool outOfOrder;

            if (descending)
                outOfOrder = arr[i] < arr[i + 1];
            else
                outOfOrder = arr[i] > arr[i + 1];

            if (outOfOrder)
            {
                // Inline swap (no swap() function allowed)
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}

double computeMedianSorted(const int sortedArr[], int size)
{
    // Precondition: array is already sorted ascending

    if (size % 2 == 1)
        return sortedArr[size / 2];

    return (sortedArr[size / 2 - 1] + sortedArr[size / 2]) / 2.0;
}

// PRINTING FUNCTIONS 

void printApprovedFormat(ostream& out,
                         const int arr[],
                         int size,
                         const string& label)
{
    out << label << "'s outputs:" << endl;

    // Print original values
    out << label << "'s values are: ";
    for (int i = 0; i < size; i++)
    {
        out << arr[i];
        if (i < size - 1)
            out << ", ";
    }
    out << endl;

    if (size > 0)
    {
        long long sum = computeSum(arr, size);
        double avg = computeAverage(arr, size);

        int temp[MAX_SIZE];
        copyArray(arr, temp, size);
        bubbleSort(temp, size, false);  // ascending for median
        double median = computeMedianSorted(temp, size);

        out << "Sum for the array '" << label << "' is " << sum << endl;
        out << "Average for the array '" << label << "' is " << avg << endl;
        out << "Median for '" << label << "' is " << median << endl;

        // Print descending order
        bubbleSort(temp, size, true);
        out << label << "'s values in descending order:" << endl;

        for (int i = 0; i < size; i++)
        {
            out << temp[i];
            if (i < size - 1)
                out << ", ";
        }
        out << endl << endl;
    }
}

// OPTION WRAPPERS

void optionPrintAll(const int arr3[], int size3,
                    const int arr7[], int size7,
                    const int arrRest[], int sizeRest)
{
    printApprovedFormat(cout, arr3, size3, "Div3");
    printApprovedFormat(cout, arr7, size7, "Div7");
    printApprovedFormat(cout, arrRest, sizeRest, "Rest");
}

void writeOutputFile(const int arr3[], int size3,
                     const int arr7[], int size7,
                     const int arrRest[], int sizeRest)
{
    ofstream fout(OUTPUT_FILE_NAME);

    printApprovedFormat(fout, arr3, size3, "Div3");
    printApprovedFormat(fout, arr7, size7, "Div7");
    printApprovedFormat(fout, arrRest, sizeRest, "Rest");

    fout.close();
}
