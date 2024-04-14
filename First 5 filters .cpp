

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

// Function to convert the image to grayscale
void gray_scale(const string name)
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

            pic(i, j, 0) = avg;
            pic(i, j, 1) = avg;
            pic(i, j, 2) = avg;
        }
    }

    Saving(name, pic);
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


// Function to display the main menu
void main_menu()
{
    while (true)
    {
        string image_name;
        cout << "Enter the image file name: ";
        getline(cin, image_name);
        cin.clear();
        if (isJPEG(image_name) || isPNG(image_name) || isBMP(image_name))
        {
            cout << "[Filters]\nA) Gray scale\nB) Black and white.\nC) Invert image.\nE) Flip image.\nF) Rotate image.\n";
            cout << "Enter your choice: ";
            while (true)
            {
                char choice;
                cin >> choice;
                if (toupper(choice) == 'A')
                {
                    gray_scale(image_name);
                    break;
                }
                else if (toupper(choice) == 'B')
                {
                    black_and_white(image_name);
                    break;
                }
                else if (toupper(choice) == 'C')
                {
                    invert_image(image_name);
                    break;
                }
                else if (toupper(choice) == 'E')
                {
                    char direction;
                    cout << "Enter 'h' for horizontal flip or 'v' for vertical flip: ";
                    cin >> direction;
                    flip_image(image_name, direction);
                    break;
                }
                else if (toupper(choice) == 'F')
                {
                    Rotate_image(image_name);
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    cout << "Enter your choice: ";
                }
            }
            break;
        }
        else
        {
            cout << "Wrong extension. The valid extension [jpg, jpeg, png, bmp]" << endl;
        }
    }
}

int main()
{
    main_menu(); 
    return 0;
}
