

#include <iostream>
#include "Image_Class.h"
#include <string>
using namespace std;

// Function to check if the file name has a JPEG extension
bool isJPEG(const string filename)
{
    string reversed_name = filename;
    reverse(reversed_name.begin(), reversed_name.end());
    return reversed_name.find("gpj.") == 0 || reversed_name.find("gepj.") == 0; // Check if the reversed filename starts with "jpg" or "jpeg"
}

// Function to check if the file name has a PNG extension
bool isPNG(const string filename)
{
    string reversed_name = filename;
    reverse(reversed_name.begin(), reversed_name.end());
    return reversed_name.find("gnp.") == 0; // Check if the reversed filename starts with "png"
}

// Function to check if the file name has a BMP extension
bool isBMP(const string filename)
{
    string reversed_name = filename;
    reverse(reversed_name.begin(), reversed_name.end());
    return reversed_name.find("pmb.") == 0; // Check if the reversed filename starts with "bmp"
}

// Function prototype for main menu
void main_menu();

// Function to prompt the user to input another image or exit the program
void TryAgain()
{
    char choice;
    cout << "Do you want to input another image? [y/n]: ";
    cin >> choice;
    if (tolower(choice) == 'n')
    {
        exit(0); // Exit the program
    }
    else if (tolower(choice) != 'y')
    {
        cout << "Invalid input. Enter 'y' to input another image or 'n' to exit." << endl;
        TryAgain(); // Prompt again if the input is invalid
    }
    else
    {
        cin.ignore(); // Clear the newline character from the input buffer
        main_menu(); // Go back to the main menu to input another image
    }
}

// Function to save or edit the image
void Saving(const string name, Image effect)
{
    cout << "Do you want to make an edit on the image or save a new one ? [e --> edit/s --> save]" << endl;
    while (true)
    {
        char choice;
        cin >> choice;
        if (tolower(choice) == 'e')
        {
            effect.saveImage(name);
            cout << "Image edited Successfully" << endl;
            TryAgain(); // Prompt the user to input another image or exit
            break;
        }
        else if (tolower(choice) == 's')
        {
            while (true)
            {
                string file_name;
                cout << "Enter the filename to save the image :";
                cin >> file_name;
                if (isJPEG(file_name) || isPNG(file_name) || isBMP(file_name))
                {
                    effect.saveImage(file_name);
                    cout << "Image saved Successfully" << endl;
                    TryAgain(); // Prompt the user to input another image or exit
                    break;
                }
                else
                {
                    cout << "Wrong extension. The valid extension [jpg, jpeg, png, bmp]" << endl;
                }
            }
        }
        else
        {
            cout << "Invalid input. [e/s]" << endl << "Enter again: ";
        }
    }
}


int main()
{
    return 0;
}
