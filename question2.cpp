#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Define the Rectangle struct to hold the plate properties
struct Rectangle {
    double width;
    double height;
    double density;
    char material[50]; // Assume material name fits in 50 characters

    // Constructor to initialize a Rectangle
    Rectangle(double w, double h, double d, const char* mat) 
        : width(w), height(h), density(d) {
        strncpy(material, mat, sizeof(material) - 1);  // Safe copy to avoid overflow
        material[sizeof(material) - 1] = '\0';  // Null-terminate
    }

    // Method to calculate the mass of the plate
    double mass() const {
        return width * height * density;
    }
};

// Function to print plate details
void print_plate(int index, double width, double height,
                 double density, double mass, const char* material) {
    cout << "Plate[" << index << "]: "
         << "width=" << width << ", "
         << "height=" << height << ", "
         << "density=" << density << ", "
         << "mass=" << mass << ", "
         << "material=" << material << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Error opening " << argv[1] << endl;
        return 1;
    }

    int num_plates;
    input >> num_plates;
    input.ignore(); // skip newline after number

    const int MAX_PLATES = 10;
    if (num_plates > MAX_PLATES) {
        cerr << "Error: number of plates exceeds maximum allowed (" << MAX_PLATES << ")" << endl;
        return 1;
    }

    // Create an array of Rectangle objects
    Rectangle plates[MAX_PLATES];

    // Read plate data from the input file
    for (int i = 0; i < num_plates; i++) {
        double width, height, density;
        char material[50];

        // Read the width, height, density, and material for each plate
        input >> width >> height >> density;
        input.ignore();  // Ignore the space or newline before the material
        input.getline(material, sizeof(material));  // Read the material name

        // Initialize the Rectangle object for the plate
        plates[i] = Rectangle(width, height, density, material);
    }

    // Compute mass for each plate and call print_plate
    for (int i = 0; i < num_plates; i++) {
        double mass = plates[i].mass();
        print_plate(i, plates[i].width, plates[i].height,
                    plates[i].density, mass, plates[i].material);
    }

    return 0;
}
