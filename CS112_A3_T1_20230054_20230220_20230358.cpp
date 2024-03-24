/*
File name: CS112_A3_T1_20230054_20230220_20230358.cpp
Purpose: Make an application that takes a photo and apply a filter to it.
Version: 1.0

---> Author 1: Esraa Emary Abd Elsalam.          ID: 20230054
---> Author 2: Abdelrahman Yasser Ali.           ID: 20230220
---> Author 2: Mohamed Nabil Elsaied Ali.        ID: 20230358

*/
//========================================================================================================================================//
#include <iostream>
#include <bits/stdc++.h>
#include "Image_Class\Image_Class.h"
using namespace std;

// Save the effect in a new photo or the same one.
void how_to_save(){
    cout << "Do you want to save the effect in a new photo or replace the base ?\n[1] New photo.\n[2] Replace the base.\nChoice: ";
    while (true)
    {
        string choice;
        getline(cin, choice);
        cin.ignore(0,'\n');
        if(choice == "1"){
            
        }
        
        else if(choice == "2")
            break;
        
        else{
            cout << "Please enter a valid choice." << endl << endl;   
            continue;
        }
    }
}

//============================================================================================================================================//


// Save the image after applying the filter.
void save(Image image){
    string new_name;
    cout << "- Please enter the new filename\n-->";
    getline(cin, new_name);
    image.saveImage(new_name);
    cout << "- Photo has been saved successfully";
}

// Get the image from the user to apply the filter.
string load(string name){
    while (true) {
        try {
        Image image(name);
        cout << "- Photo Loaded Successfuly!\n";
        return name;
        }
        catch (invalid_argument) {
            cout << "- Filename cannot be found!\nPlease enter a valid filename\n--> ";
            getline(cin, name);
        }
    }

}

//================================================================= Main Program ==============================================================//

int main(){
    // Welcome message and brief lines about our application.
    cout << "#==================== Welcome to our application ====================#" << endl << endl;
    cout << "---> This application takes any photo and applies some filters to it." << endl;
    cout << "---> Insert any image to apply filters to it in any of these formats:" << endl;
    cout << "[1] photo.jpeg [2] photo.jpg [3] photo.png [4] photo.bmp" << endl;
    while (true)
    {
        // Print the menu for choosing what the user want to do.
        cout << "\n----------------------------------------------------------------------" << endl << endl;
        cout << "What do you want to do ?\n[1] Apply a filter to a photo.\n[2] Exit.\nChoice: ";
        string choice;
        getline(cin, choice);
        cin.ignore(0);  

        // Applying a filter to the entered photo.
        if(choice == "1"){
            while (true){
                cout << "\n----------------------------------------------------------------------" << endl << endl;
                cout << "What filter do you want to apply ?\n[1] Grayscale Conversion.\n[2] .\n[3] .\n[4] .\n[5] .\n[6] Back.\nChoice: ";
                string choice1;
                getline(cin, choice1);
                cin.ignore(0);

                // Applying filter1 (Grayscale Conversion).
                if (choice1 == "1")
                {
                    string photo;
                    cout << "Please enter the photo name: ";
                    getline(cin, photo);
                    cin.ignore(0);
                    photo = load(photo);
                    Image image(photo);
                    for (int i = 0; i < image.width; ++i) {
                        for (int j = 0; j < image.height; ++j) {
                            unsigned  int avg = 0; // Initialize average value

                            for (int k = 0; k < 3; ++k) {
                                avg += image(i, j, k); // Accumulate pixel values
                            }

                            avg /= 3; // Calculate average

                            // Set all channels to the average value
                            image(i, j, 0) = avg;
                            image(i, j, 1) = avg;
                            image(i, j, 2) = avg;
                        }
                    }
                    image.saveImage("nice.jpg");

                    cout << "Please enter the new filename and extension (or press enter to save changes to the same file): ";
                    break;
                }

                // else if (choice1 == "2")
                // {
                    
                // }

                // Back to the main menu.
                else if (choice1 =="6")
                {
                    break;
                }

                // Invalid choice.
                else{
                    cout << "Please enter a valid choice." << endl;   
                    continue;
                }
            }
        }
        // Exit the program.
        else if(choice == "2")
            break;
        
        // Invalid choice for the menu.
        else{
            cout << "Please enter a valid choice." << endl;   
            continue;
        }
    }

    cout << "\n#===== Thanks for using our application =====#" << endl;
    return 0;
}
    
   
