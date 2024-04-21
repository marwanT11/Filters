/*
File name: CS112_A3_Part2B_S1,S2_20230113_20230042_20230380
Author 1: Adham Ayman Mohamed 20230042 - filters : 1 , 4 , 7 , 10 and bonus purple
Author 2: Marwan Tamer Sayed 20230380 -  filters : 3 , 6 , 9 , 12 and bonus sunlight
Author 3: Hazem Ahmed Mohamed 20230113 - filters : 2 , 5 , 8 , 11 and bonus skewed
GitHub Repo link : https://github.com/marwanT11/Filters
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

// Function to merge two images
void merge_images(const string image1_name)
{
    Image image1(image1_name);

    string image2_name;
    cout << "Enter the second image file name: ";
    cin.ignore();
    getline(cin, image2_name);

    Image image2(image2_name);

    // Get the dimensions of the two images
    int W1 = image1.width;
    int H1 = image1.height;
    int W2 = image2.width;
    int H2 = image2.height;

    cout << "Choose the merging option:\n";
    cout << "1.Resize both images to the larger dimensions.\n";
    cout << "2.Resize both images to the smaller dimensions.\n";
    cout << "Enter your choice (1/2): ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        // Resize both images to the larger dimensions
        int mergedWidth = max(W1, W2);
        int mergedHeight = max(H1, H2);

        // Create new images to store the resized versions
        Image resizedImage1(mergedWidth, mergedHeight);
        Image resizedImage2(mergedWidth, mergedHeight);

        // Resize image1
        for (int i = 0; i < mergedHeight; i++)
        {
            for (int j = 0; j < mergedWidth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int RealX = static_cast<int> (j * (W1 / static_cast<double> (mergedWidth)));
                    int Real_Y = static_cast<int> (i * (H1 / static_cast<double> (mergedHeight)));
                    resizedImage1(j, i, k) = image1(RealX, Real_Y, k);
                }
            }
        }

        // Resize image2
        for (int i = 0; i < mergedHeight; i++)
        {
            for (int j = 0; j < mergedWidth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int RealX = static_cast<int>(j * (W2 / static_cast<double> (mergedWidth)));
                    int Real_Y = static_cast<int>(i * (H2 / static_cast<double> (mergedHeight)));
                    resizedImage2(j, i, k) = image2(RealX, Real_Y, k);
                }
            }
        }

        // Merge the resized images with weighted average
        Image merged(mergedWidth, mergedHeight);
        for (int i = 0; i < mergedHeight; i++)
        {
            for (int j = 0; j < mergedWidth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(j, i, k) = (resizedImage1(j, i, k) + resizedImage2(j, i, k)) / 2;
                }
            }
        }
        Saving(image1_name, merged);
        break;
    }
    case 2:
    {

        // Resize both images to the smaller dimensions
        int mergedWidth = min(W1, W2);
        int mergedHeight = min(H1, H2);

        // Create new images to store the resized versions
        Image resizedImage1(mergedWidth, mergedHeight);
        Image resizedImage2(mergedWidth, mergedHeight);

        // Resize image1
        for (int i = 0; i < mergedHeight; i++)
        {
            for (int j = 0; j < mergedWidth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    resizedImage1(j, i, k) = image1(j, i, k);
                }
            }
        }

        // Resize image2
        for (int i = 0; i < mergedHeight; i++)
        {
            for (int j = 0; j < mergedWidth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    resizedImage2(j, i, k) = image2(j, i, k);
                }
            }
        }

        // Merge the resized images with weighted average
        Image merged(mergedWidth, mergedHeight);
        for (int i = 0; i < mergedHeight; i++)
        {
            for (int j = 0; j < mergedWidth; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    merged(j, i, k) = (resizedImage1(j, i, k) + resizedImage2(j, i, k)) / 2;
                }
            }
        }

        // Save the merged image
        Saving(image1_name, merged);
        break;
    }
    default:
        cout << "Invalid choice. Please enter 1 or 2." << endl;
        break;
    }
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

// Function to darken or lighten the image by 50%
void darken_and_lighten(const string name)
{
    while (true)
    {
        char choice;
        cout << "Choose an option:\n";
        cout << "A) Darker\n";
        cout << "B) Lighter\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (toupper(choice) == 'A')
        {
            // Darken the image
            Image pic(name);
            for (int i = 0; i < pic.width; i++)
            {
                for (int j = 0; j < pic.height; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        pic(i, j, k) = max(0, int(pic(i, j, k) * 0.5)); // Reduce each pixel value by half
                    }
                }
            }

            Saving(name, pic);
            break;
        }
        else if (toupper(choice) == 'B')
        {
            // Lighten the image
            Image pic(name);
            for (int i = 0; i < pic.width; i++)
            {
                for (int j = 0; j < pic.height; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        pic(i, j, k) = min(255, int(pic(i, j, k) * 1.5)); // Increase each pixel value by half
                    }
                }
            }

            Saving(name, pic);
            break;
        }
        else
        {
            cout << "Invalid choice. Please enter 'A' for darker or 'B' for lighter." << endl;
        }
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
        else 
        {
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

// Function to detect edges in the image
void detect_edges(const string name)
{
    Image pic(name);

    Image edges(pic.width, pic.height);

    // Define a threshold for edge detection
    int threshold = 60;

    for (int i = 1; i < pic.width - 1; i++)
    {
        for (int j = 1; j < pic.height - 1; j++)
        {
            // Calculate intensity differences in horizontal and vertical directions
            int diff_x = pic(i + 1, j, 0) - pic(i - 1, j, 0);
            int diff_y = pic(i, j + 1, 0) - pic(i, j - 1, 0);

            // -> the magnitude of the gradient
            int magnitude = sqrt(diff_x * diff_x + diff_y * diff_y);

            // Set the pixel to black if the magnitude is above the threshold and white otherwise
            if (magnitude > threshold)
            {
                // Highlight edges by setting to black
                edges(i, j, 0) = 0;
                edges(i, j, 1) = 0;
                edges(i, j, 2) = 0;
            }
            else
            {
                // Set non-edge pixels to white
                edges(i, j, 0) = 255;
                edges(i, j, 1) = 255;
                edges(i, j, 2) = 255;
            }
        }
    }
    Saving(name, edges);
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

// Purble 
void purple(const string name)
{
    Image pic(name);
    for (int i = 0; i < pic.width; i++)
    {
        for (int j = 0; j < pic.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                pic(i, j, 0) = min(255, pic(i, j, 0) + 6);
                pic(i, j, 2) = min(255, pic(i, j, 2) + 13);
                pic(i, j, 1) = max(0, pic(i, j, 1) - 13);
            }
        }

    }
    Saving(name, pic);
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
            cout << "[Filters]\nA) Gray scale\nB) Black and white.\nC) Invert image.\nD) Merge image.\nE) Flip image.\nF) Rotate image.\nG) Darken or Lighten image.\nH) Crop images.\nI) ِAdding a Frame to the Picture.\nJ) Detect edges.\nK) Resize image.\nL) Blur image.\nM) Sunlight.\nN) Purple.\nO) Skewed.\n";
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
                else if (toupper(choice) == 'D')
                {
                    merge_images(image_name);
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
                else if (toupper(choice) == 'G')
                {
                    darken_and_lighten(image_name);
                    break;
                }
                else if (toupper(choice) == 'H')
                {
                    int x, y, width, height;
                    cout << "Enter the x-coordinate of the starting point: ";
                    cin >> x;
                    cout << "Enter the y-coordinate of the starting point: ";
                    cin >> y;
                    cout << "Enter the width of the area to crop: ";
                    cin >> width;
                    cout << "Enter the height of the area to crop: ";
                    cin >> height;
                    crop_image(image_name, x, y, width, height);
                    break;
                }
                else if (toupper(choice) == 'I')
                {
                    frame_image(image_name);
                    break;
                }
                else if (toupper(choice) == 'J')
                {
                    detect_edges(image_name);
                    break;
                }
                else if (toupper(choice) == 'K')
                {
                    int newWidth, newHeight;
                    cout << "Enter the new width: ";
                    cin >> newWidth;
                    cout << "Enter the new height: ";
                    cin >> newHeight;
                    resize_image(image_name, newWidth, newHeight);
                    break;
                }
                else if (toupper(choice) == 'L')
                {
                    applyBlur(image_name);
                    break;
                }
                // Bonus ..
                else if (toupper(choice) == 'M')
                {
                    sunlight(image_name);
                    break;
                }
                else if (toupper(choice) == 'N')
                {
                    purple(image_name);
                    break;
                }
                else if (toupper(choice) == 'O')
                {
                    skewImage(image_name);
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
