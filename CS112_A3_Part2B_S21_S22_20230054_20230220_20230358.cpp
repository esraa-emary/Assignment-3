/*
File name   :   CS112_A3_Part1_S21_20230054_20230220_20230358.cpp
Purpose     :   Make an application that takes a photo and apply a filter to it.
Version     :   1.0

                              Authors                   |           Filters         |                   Contributions
---> 1: Esraa Emary Abd Elsalam.          ID: 20230054  |   Merge - Lighten/Darken  |   how_to_save() - Main menu - Output formatting
---> 2: Abdelrahman Yasser Ali.           ID: 20230220  |     Black/White - Flip    |            load() - Filters adjustments
---> 2: Mohamed Nabil Elsaied Ali.        ID: 20230358  |      Rotate - Invert      |                  Resizing algorithm


Professor           :   Dr.Mohamed ElRamly
Teaching Assistant  :   Eng.Rana Abdelkader
Section Number      :   S21-S22

*/
//========================================================================================================================================//

#include <iostream>
#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

// Save the effect in a new photo or the same one.
void how_to_save(Image &image, string &photo){
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Do you want to save the effect in a new photo or replace the base ?\n[1] New photo.\n[2] Replace the base.\nChoice: ";
    while (true)
    {
        string choice;
        getline(cin, choice);

        // Save the effect in a new photo.
        if(choice == "1"){
            string new_name;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Remember that:" << endl;
            cout << "The new file name must be one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the new file name:\n--> ";
            getline(cin, new_name);

            // Check the validity of the new file name.
            while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp"))){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "Remember that:" << endl;
                cout << "The new file name must be one of the following format.\n";
                cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
                cout << "Please enter a valid new file name:\n--> ";
                getline(cin, new_name);
            }
            image.saveImage(new_name);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Photo has been saved successfully." << endl;
            break;
        }
        
        // Save the effect in the same photo.
        else if(choice == "2"){
            image.saveImage(photo);
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Photo has been saved successfully." << endl;
            break;
        }
        
        // Invalid choice.
        else{
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid choice:\n-->" << endl;   
            continue;
        }
    }
}

// Save the effect in a new photo only.
void how_to_save2(Image &image){
    string new_name;
    cout << "Remember that:" << endl;
    cout << "The new file name must be one of the following format.\n";
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    cout << "Please enter the new file name:\n--> ";
    getline(cin, new_name);

    // Check the validity of the new file name.
    while(new_name.size() < 5 || ((new_name.substr(new_name.size() - 4 , 4) != "jpeg") && (new_name.substr(new_name.size() - 3 , 3) != "jpg") && (new_name.substr(new_name.size() - 3 , 3) != "png") && (new_name.substr(new_name.size() - 3 , 3) != "bmp"))){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Remember that:" << endl;
        cout << "The new file name must be one of the following format.\n";
        cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
        cout << "Please enter a valid new file name:\n--> ";
        getline(cin, new_name);
    }
    image.saveImage(new_name);
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Photo has been saved successfully." << endl;
}

// Get the image from the user to apply the filter.
string load(string &name){
    while (true) {
        cout << endl;
        try {
        Image image(name);
        cout << "----------------------------------------------------------------------" << endl << endl;
        cout << "Photo Loaded Successfuly.\n";
        return name;
        }
        catch (invalid_argument) {
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid file name:\n--> ";
            getline(cin, name);
        }
    }
}

// ========================================================== Main Functions ========================================================== //

// ========================================================== Filter 1 (Grayscale Conversion) ========================================================== //
Image Grayscale_Conversion(Image &image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0;                                                  // Initialize average value.
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);                                              // Accumulate pixel values.
            }
            avg /= 3;                                                               // Calculate average.
            image(i, j, 0) = avg;                                                   // Set all channels to the average value.
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
    return image;
}

// ========================================================== Filter 2 (Black and White) ========================================================== //
Image Black_n_White(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned  int avg = 0;                                              // Initialize average value.
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);                                          // Accumulate pixel values.
            }
            avg /= 3;                                                           // Calculate average.
            int val;
            if (avg > 127) {
                val = 255;
            }
            else {
                val = 0;
            }
            // Set all channels to either 0 or 255 (to obtain black and white only)
            image(i, j, 0) = val;
            image(i, j, 1) = val;
            image(i, j, 2) = val;
        }
    }
    return image;
}

// ========================================================== Filter 3 (Invert Image) ========================================================== //
Image Invert_Image(Image &image){
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i,j,k) = 255 - image(i,j,k);                               // Change pixel values.
            }
        }  
    }
    return image;
}

// ========================================================== Filter 4 (Merge Images) ========================================================== //
Image Merge_Images(Image &photo11, Image &photo22){
    // Declare minimum width and minimum height to unify dimensions for both photos
    int width = min(photo11.width, photo22.width);
    int height = min(photo11.height, photo22.height);

    Image photo_result(width, height);                                          // Create the new photo
    Image photo1_sized(width, height);
    Image photo2_sized(width, height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < 3; z++) {
                // Resize the new photos by discarding unneeded pixels based on the ratio between dimensions
                photo1_sized(x, y, z) = photo11(x*(photo11.width/(float) width), y*(photo11.height/(float) height), z); // Resize photo 1
                photo2_sized(x, y, z) = photo22(x*(photo22.width/(float) width), y*(photo22.height/(float) height), z); // Resize photo 2
            }
        }
    }
                        
    for (int i = 0; i < photo_result.width; ++i) {                              // Applying merge
        for (int j = 0; j < photo_result.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int avrg = 0;
                avrg = (photo1_sized(i,j,k) + photo2_sized(i,j,k))/2;
                photo_result(i, j, k) = avrg;
            }
        }
    }
    return photo_result;
}

// ========================================================== Filter 5 (Flip) ========================================================== //
Image Flip_Image(Image &image) {
    while (true) {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to flip horizontally or vertically ?\n"<< "[1] Horizontally\n"
            << "[2] Vertically\n"<< "[3] Back.\n"<< "Choice: ";
        string choice;
        getline(cin, choice);

        // Flip horizontally
        if (choice == "1") {
            int width = image.width;
            int height = image.height;

            for (int i = 0; i < width/2; i++) {                                 // Loop until reaching half of the image width
                for (int j = 0; j < height; j++) {
                    int temp;

                    for (int k = 0; k < 3; k++) {
                        temp = image(i, j, k);                                  // Temp variable to store the pixel before swapping
                        image(i, j, k) = image(width - 1 - i, j, k);            // Swap the pixel with each opposite one (horizontally)
                        image(width - 1 - i, j, k) = temp;                      // Assign the old value to the opposite pixel
                    }

                }
            }
            return image;
        }

        // Flip vertically
        else if (choice == "2") {
            int width = image.width;
            int height = image.height;

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height/2; j++) {                            // Loop until reaching half of the image width
                    int temp;
                    for (int k = 0; k < 3; k++) {
                        temp = image(i, j, k);                                  // Temp variable to store the pixel before swapping
                        image(i, j, k) = image(i, height - 1 - j, k);           // Swap the pixel with each opposite one (vertically)
                        image(i, height - 1 - j, k) = temp;
                    }
                }
            }
            return image;
        }

        // Back to the main menu.
        else if (choice == "3") 
            break;
        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 6 (Rotate Image) ========================================================== //
Image Rotate_Image(Image &image){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What rotation do you want ?\n[1] Rotate 90.\n[2] Rotate 180.\n[3] Rotate 270.\n[4] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Rotate 90°.
        if (choice2 ==  "1"){
            int width,height;                                                   // Initialize values of width and height.                                 
            width = image.width;
            height = image.height;

            Image rotate(height,width);                                         // Make new image rotate that have swaped dimensions of the image.
            for(int x=1;x<image.width;x++){
                for(int y=1; y<image.height;y++){
                    for(int z=0; z<3;z++){
                        rotate(y ,x ,z) = image(x, image.height - y, z);        // Change pixel values.
                    }
                }
            }
            return rotate;
            break;
        }

        // Rotate 180°.
        else if(choice2 == "2"){
            int width,height;                                                   // Initialize values of width and height.    
            width = image.width;
            height = image.height;

            Image rotate (height,width);                                        // Make new image rotate that have swaped dimensions of the image.
            Image rotate180 (width,height);                                     // Make new image rotate180 that have same dimensions of the image.
            for(int x = 1;x < width;x++){
                for(int y=1; y<height;y++){
                    for(int z=0; z<3;z++){
                        rotate180(x, y, z) = image(width - x,height - y, z);    // Change pixel values.
                    }
                }
            }
            rotate = rotate180;
            return rotate;
        }

        // Rotate 270°.
        else if(choice2 == "3"){
            int width,height;                                                   // Initialize values of width and height.    
            width = image.width;
            height = image.height;

            Image rotate(height,width);                                         // Make new image rotate that have swaped dimensions of the image.
            for(int x = 0 ; x < rotate.width ; x++){
                for(int y = 0 ; y < rotate.height ; y++){
                    for(int z = 0 ; z < 3 ; z++){
                        rotate(x,y,z)=image(rotate.height - y, x, z);           // Change pixel values.
                    }
                }
            }
            return rotate;
        }

        // Back to the main menu.
        else if (choice2 =="4")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 7 (Darken and Lighten Image) ========================================================== //
Image Darken_and_Lighten(Image &image){
    while (true)
    {
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "Do you want to darken or lighten the image ?\n[1] Darken The Image.\n[2] Lighten The Image.\n[3] Back.\nChoice: ";
        string choice2;
        getline(cin, choice2);

        // Darken The Image.
        if (choice2 ==  "1"){
            float darken = 0.5;                                                   // Initialize darken value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        image(i, j, k) *= darken;                                 // Change pixel values.
                    }
                }
            }
            return image;
        }

        // Lighten The Image.
        else if(choice2 == "2"){
            float lighten = 1.5;                                                // Initialize lighten value.
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        int val = image(i, j, k) * lighten;                     // Change pixel values.
                        if (val > 255)                                          // Check if channel value exceeds 255 
                            (image(i, j, k) = 255);
                        else
                            image(i, j, k) = val;
                    }
                }
            }
            return image;
        }

        // Back to the main menu.
        else if (choice2 =="3")
            break;

        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    return image;
}

// ========================================================== Filter 10 (Detect_Image_Edges) ========================================================== //
Image Detect_Image_Edges(Image &image){
    for (int i = 1; i < image.width-1 ; i++){
        for (int j = 0; j < image.height; j++){
            if (!((image(i,j,0) <= (image(i+1 , j , 0)+10 )||image(i,j,0) >= (image(i-1 , j , 0)-10  ) ))) {
                if (!((image(i,j,1) <= (image(i+1 , j , 1)+10 )||image(i,j,1) >= (image(i-1 , j , 1)-10  ) ))) {
                    if (!((image(i,j,2) <= (image(i+1 , j , 2)+10  )||image(i,j,2) >= (image(i-1 , j , 2)-10  ) ))) {
                        image(i,j,0) =0;
                        image(i,j,1) =0;           
                        image(i,j,2) =0;
                    }
                }
            }

            else if (!((image(i,j,0) <= (image(i , j+1, 0)+10 )||image(i,j,0) >= (image(i , j-1 , 0)-10  ) ))) {
                if (!((image(i,j,1) <= (image(i , j+1 , 1)+10 )||image(i,j,1) >= (image(i , j-1 , 1)-10  ) ))) {
                    if (!((image(i,j,2) <= (image(i , j+1 , 2)+10  )||image(i,j,2) >= (image(i , j-1 , 2)-10  ) ))) {
                        image(i,j,0) =0;
                        image(i,j,1) =0;           
                        image(i,j,2) =0;
                    }
                }
            }

            else{
                image(i,j,0) =255;
                image(i,j,1) =255;           
                image(i,j,2) =255;
            }
        }
    }
    return image;
}

// ========================================================== Filter 11 (Resizing Images) ========================================================== //
Image Resizing_Image(Image &image){
    float width, height;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Please enter the width you want:\n--> ";                               // Read the width.
    cin >>  width;
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "Please enter the height you want:\n--> ";                              // Read the height.
    cin >> height;
    cin.ignore();

    Image image_result(width,height);
    float step_width1 = image.width/width;
    float step_height1 = image.height/height;
    
    for(int i =0 ;i<width;i++){
        for(int j=0;j<height;j++){
            for(int k=0;k<3;k++){
                image_result(i,j,k) = image((i*step_width1) , (j*step_height1),k);   // Change pixel values. 
            }
        }
    }
    image = image_result;
    return image;
}

// ========================================================== Filter 17 (Infrared) ========================================================== //
Image Infrared_Photography(Image &image){
    for(int i=0; i<image.width; i++){
        for(int j=0; j<image.height; j++){
            for(int k=0; k<3; k++){
                image(i, j, k) = 255 - image(i, j, k);                          // Change pixel values.
                image(i, j, 0) = 255;
            }
        }  
    }
    return image;
}

//================================================================= Main Program ==============================================================//

int main(){
    // Welcome message and brief lines about our application.
    cout << "#==================== Welcome to our application ====================#" << endl << endl;
    cout << "---> This application takes any photo and applies some filters in it." << endl;
    cout << "---> To apply filters in a photo it must be in one of these formats:" << endl;
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    
    int count = 0;
    string name;
    Image image;
    bool flag = false;
    while (true){
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What do you want to do ?\n"<< "[1] Load a new image.\n" << "[2] Grayscale Conversion.\n" << "[3] Black and White.\n" << "[4] Invert Image.\n" << "[5] Merge Images.\n" 
             << "[6] Flip Image.\n" << "[7] Rotate Image.\n" << "[8] Darken and Lighten Image.\n" << "[9] \n" << "[10] \n" << "[11] Detect Image Edges.\n" 
             << "[12] Resizing Image.\n" << "[13] \n" << "[14] \n" << "[15] \n" << "[16] Infrared Photography.\n" <<"[17] Save the image.\n" << "[18] Exit.\n"<< "Choice: ";
        string choice1;
        getline(cin, choice1);

        // Check that the user enrered an image at first.
        if (count == 0 && (choice1 == "2" || choice1 == "3" || choice1 == "4" || choice1  == "5" || choice1  == "6" || choice1  == "7" || 
            choice1  == "8" || choice1  == "9" || choice1  == "10" || choice1  == "11" || choice1  == "12" || choice1  == "13" || 
            choice1  == "14" || choice1  == "15" || choice1  == "16" || choice1  == "17")){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please load an image at first.\n";
            continue;
        }

        // Loading the image.
        if (choice1 == "1"){
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Remember that:" << endl;
            cout << "The file name must be at one of the following format.\n";
            cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
            cout << "Please enter the file name:\n--> ";
            string photo_name;
            getline(cin, photo_name);
            name = photo_name;
            name = load(name);
            Image image1 (name);
            image = image1;
            count ++;
        }

        // Applying filter 1 (Grayscale Conversion).
        else if (choice1 == "2"){
            image = Grayscale_Conversion(image);
        }

        // Applying filter 2 (Black and White Image).
        else if (choice1 == "3"){
            image = Black_n_White(image);
        }

        // Applying filter 3 (Invert Image).
        else if (choice1 == "4"){
            image = Invert_Image(image);
        }

        // Applying filter 4 (Merge Images).
        else if (choice1 == "5"){
            flag = true;
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Enter the second image to merge with:\n--> ";
            string name2;
            getline(cin, name2);
            name2 = load(name2);
            Image image2(name2);
            image = Merge_Images(image, image2);
        }

        // Applying filter 5 (Flip Image).
        else if (choice1 == "6"){
            image = Flip_Image(image);
        }

        // Applying filter 6 (Rotate Image).
        else if (choice1 == "7"){
            image = Rotate_Image(image);
        }

        // Applying filter 7 (Darken and Lighten Image).
        else if (choice1 == "8"){
            image = Darken_and_Lighten(image);
        }

        // Applying filter 8 ().
        // else if (choice1 == "9"){
        //     image = ;
        // }

        // Applying filter 9 ().
        // else if (choice1 == "10"){
        //     image = ;
        // }

        // Applying filter 10 (Detect Image Edges).
        else if (choice1 == "11"){
            image = Detect_Image_Edges(image);
        }

        // Applying filter 11 (Resizing Images).
        else if (choice1 == "12"){
            image = Resizing_Image(image);
        }

        // Applying filter 12 ().
        // else if (choice1 == "13"){
        //     image = ;
        // }
       
        // Applying filter 13 ().
        // else if (choice1 == "14"){
        //     image = ;
        // }

        // Applying filter 14 ().
        // else if (choice1 == "15"){
        //     image = ;
        // }

        // Applying filter 15 (Infrared Photography).
        else if (choice1 == "16"){
            image = Infrared_Photography(image);
        }

        // Save the image.
        else if (choice1 == "17"){
            if (flag){
                how_to_save2(image);
                flag = false;
            }
            else
                how_to_save(image, name);
        }

        // Exit the application.
        else if (choice1 =="18")
            break;

        // Invalid choice.
        else{
            cout << "\n----------------------------------------------------------------------" << endl << endl;
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }
    cout << "\n----------------------------------------------------------------------" << endl << endl;
    cout << "#===== Thanks for using our application =====#" << endl;
    return 0;
}
