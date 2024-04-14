/*
File name: CS112_A3_Part1_S1,S2_20230042_20230113_20230380
Author 1: Adham Ayman Mohamed 20230042 - GrayScale
Author 2: Marwan Tamer Sayed 20230380 - invert_image & Rotate_image
Author 3: Hazem Ahmed Mohamed 20230113 - flip_image & Black and White
*/

#include <iostream>
#include "Image_Class.h"
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
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





// Function to invert the colors of the image
void invert_image(const string name)
{
    Image pic(name);
    for (int i = 0; i < pic.width; i++)
    {
        for (int j = 0; j < pic.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                pic(i, j, k) = 255 - pic(i, j, k);
            }
        }
    }

    Saving(name, pic);
}





// Function to rotate the image by a specified angle
void Rotate_image(const string name)
{
    Image pic(name);
    int angle;
    int new_width, new_height;

    while (true)
    {
        cout << "Enter degree of rotation [90, 180, 270]: ";
        cin >> angle;
        if (angle == 90 || angle == 270)
        {
            new_width = pic.height;
            new_height = pic.width;
            break;
        }
        else if (angle == 180)
        {
            new_width = pic.width;
            new_height = pic.height;
            break;
        }
        else
        {
            cout << "Invalid angle. Please choose 90, 180, or 270 degrees." << endl;
        }
    }

    Image rotatedImage(new_width, new_height);

    for (int i = 0; i < new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int original_i, original_j;
                if (angle == 90)
                {
                    original_i = pic.height - 1 - j;
                    original_j = i;
                }
                else if (angle == 180)
                {
                    original_i = pic.height - 1 - i;
                    original_j = pic.width - 1 - j;
                }
                else if (angle == 270)
                {
                    original_i = j;
                    original_j = pic.width - 1 - i;
                }

                rotatedImage(j, i, k) = pic(original_j, original_i, k);
            }
        }
    }

    Saving(name, rotatedImage);
}





// Function to add a frame to the image 
void frame_image(const string name)
{
    Image pic(name);
    int frameSize;
    int frameColor;
    char frameType;
    while (true)
    {
        cout << "Enter the frame color (0-255): ";
        cin >> frameColor;

        if (!(frameColor < 0 || frameColor > 255))
        {
            break;
        }
        else {
            cout << "Invalid frame color!\n";
        }
    }

    while (true)
    {
        cout << "Enter the frame size: ";
        cin >> frameSize;
        if (!(frameSize <= 0 || frameSize >= min(pic.width, pic.height) / 2))
        {
            break;
        }
        else
        {
            cout << "Invalid frame size!\n";
        }
    }
    while (true)
    {
        cout << "Choose the frame type:\n";
        cout << "A) Simple Frame\n";
        cout << "B) Fancy Frame\n";
        cin >> frameType;
        if (toupper(frameType) == 'A')
        {   // Frame with a simple color
            for (int i = 0; i < pic.width; i++)
            {
                for (int j = 0; j < pic.height; j++)
                {
                    if (i < frameSize || i >= pic.width - frameSize || j < frameSize || j >= pic.height - frameSize)
                    {
                        for (int k = 0; k < 3; k++)
                        {
                            pic(i, j, k) = frameColor;
                        }
                    }
                }
            }
            break;
        }
        else if (toupper(frameType) == 'B')
        {    // Frame with a fancy gradient effect
            for (int i = 0; i < pic.width; i++) 
            {
                for (int j = 0; j < pic.height; j++)
                {
                    if (i < frameSize || i >= pic.width - frameSize || j < frameSize || j >= pic.height - frameSize)
                    {
                        int dist = min(min(i, pic.width - i - 1), min(j, pic.height - j - 1));
                        for (int k = 0; k < 3; k++)
                        {
                            pic(i, j, k) = (255 - frameColor) * dist / frameSize + frameColor;
                        }
                    }
                }
            }
            break;
        }
        else
        {
            cout << "Invalid choice .\n";
        }
    }
    Saving(name, pic);
}





// Function to Blur images 
void applyBlur(const string& name)
{
    Image pic(name);
    int radius;
    cout << "Enter the blur radius (suggesting values between 1 and 10): ";
    cin >> radius;
    // Temporary storage for blurred pixel values
    vector<vector<vector<int>>> blurred(pic.width, vector<vector<int>>(pic.height, vector<int>(pic.channels, 0)));

    // Apply blur
    for (int x = 0; x < pic.width; ++x)
    {
        for (int y = 0; y < pic.height; ++y)
        {
            for (int c = 0; c < pic.channels; ++c)
            {
                int count = 0;
                int sum = 0;

                // Iterate over the pixels in the radius
                for (int i = max(0, x - radius); i < min(pic.width, x + radius + 1); ++i)
                {
                    for (int j = max(0, y - radius); j < min(pic.height, y + radius + 1); ++j)
                    {
                        sum += pic(i, j, c);
                        ++count;
                    }
                }

                // Compute the average and assign to the blurred pixel
                blurred[x][y][c] = sum / count;
            }
        }
    }

    // Copy the blurred pixels back to the original image
    for (int x = 0; x < pic.width; ++x)
    {
        for (int y = 0; y < pic.height; ++y)
        {
            for (int c = 0; c < pic.channels; ++c)
            {
                pic(x, y, c) = blurred[x][y][c];
            }
        }
    }

    Saving(name, pic);
}

// Sunlight 
void sunlight(const string name)
{
    Image pic(name);
    for (int i = 0; i < pic.width; i++) 
    {
        for (int j = 0; j < pic.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                pic(i, j, 0) = min(255, pic(i, j, 0) + 10); // Increase Red 
                pic(i, j, 1) = min(255, pic(i, j, 1) + 10); // Increase Green 
                pic(i, j, 2) = max(0, pic(i, j, 2) - 5);   // Decrease Blue 
            }
        }

    }
    Saving(name, pic);
}






int main()
{
    
    return 0;
}
