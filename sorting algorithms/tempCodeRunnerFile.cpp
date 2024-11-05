// Function to read input from a file
vector<float> readInputFile(const string& filename) {
    vector<float> array;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return array;
    }

    float number;
    char comma;
    while (file >> number) {
        if (number == -1) break;  // Stop if -1 is encountered
        array.push_back(number);
        file >> comma;  // Read the comma delimiter
    }
    file.close();
    return array;
}
