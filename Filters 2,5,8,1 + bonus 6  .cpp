

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

// Function to convert the image to black and white
void black_and_white(const string name)
{
    Image pic(name);
    for (int i = 0; i < pic.width; i++)
    {
        for (int j = 0; j < pic.height; j++)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++)
            {
                avg += pic(i, j, k);
            }
            avg /= 3;
            if (avg < 128)
            {
                pic(i, j, 0) = 0;
                pic(i, j, 1) = 0
                    ;
                pic(i, j, 2) = 0;
            }
            else
            {
                pic(i, j, 0) = 255;
                pic(i, j, 1) = 255;
                pic(i, j, 2) = 255;
            }
        }
    }

    Saving(name, pic);
}

// Function to flip the image horizontally or vertically
void flip_image(const string name, char direction)
{
    while (true)
    {
        Image pic(name);
        int width = pic.width;
        int height = pic.height;
        Image flipped(width, height);

        switch (direction)
        {
        case 'h': // Horizontal flip
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        flipped.setPixel(j, i, k, pic.getPixel(width - 1 - j, i, k));
                    }
                }
            }
            break;
        case 'v': // Vertical flip
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        flipped.setPixel(j, i, k, pic.getPixel(j, height - 1 - i, k));
                    }
                }
            }
            break;
        default:
            cout << "Invalid flipping direction. Enter 'h' for horizontal flip or 'v' for vertical flip: ";
            cin >> direction;
            continue; // Repeat the loop to prompt the user again
        }

        Saving(name, flipped);
        break; // Exit the loop if the direction is valid and the image is saved
    }
}

// Function to crop images with specified dimensions 
void crop_image(const string name, int x, int y, int width, int height)
{
    Image pic(name);

    // Check if the specified dimensions are within the bounds of the original image
    if (x < 0 || y < 0 || x + width > pic.width || y + height > pic.height)
    {
        cout << "Invalid dimensions. The specified area is outside the bounds of the original image." << endl;
        return;
    }

    Image cropped(width, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cropped(j, i, k) = pic(x + j, y + i, k);
            }
        }
    }

    Saving(name, cropped);
}

// Function to resize images
void resize_image(const string name, int newWidth, int newHeight)
{
    Image pic(name);

    Image resized(newWidth, newHeight);

    // Calculate the scaling factors for width and height
    int scaleX = pic.width / newWidth;
    int scaleY = pic.height / newHeight;

    // Resize the image using nearest-neighbor interpolation
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int sourceX = j * scaleX;
                int sourceY = i * scaleY;
                resized(j, i, k) = pic(sourceX, sourceY, k);
            }
        }
    }

    Saving(name, resized);
}

// Function to skew image 
void skewImage(const string name)
{
    Image pic(name);

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

    double angle;
    cout << "Enter the degree of skewness along the vertical axis: ";
    cin >> angle;
    // Convert angle from degrees to radians
    double radianAngle = angle * M_PI / 180.0;

    // Calculate the width of the resulting image after skewing
    int newWidth = static_cast<int>(pic.width + tan(radianAngle) * pic.height);

    // Create a new image with the calculated width and the same height
    Image result(newWidth, pic.height);

    // Iterate over each pixel in the result image
    for (int x = 0; x < result.width; x++)
    {
        for (int y = 0; y < result.height; y++)
        {
            // Calculate the corresponding position in the original image
            int originalX = x - tan(radianAngle) * (result.height - y);
            int originalY = y;

            // Check if the calculated position is within the bounds of the original image
            if (originalX >= 0 && originalX < pic.width && originalY >= 0 && originalY < pic.height)
            {
                // Assign the pixel value from the original image to the result image
                result(x, y, 0) = pic(originalX, originalY, 0);
                result(x, y, 1) = pic(originalX, originalY, 1);
                result(x, y, 2) = pic(originalX, originalY, 2);
            }
            else
            {
                // If the calculated position is outside the bounds, set the pixel to black
                result(x, y, 0) = 0;
                result(x, y, 1) = 0;
                result(x, y, 2) = 0;
            }
        }
    }

    Saving(name, result);
}


int main()
{
    return 0;
}
