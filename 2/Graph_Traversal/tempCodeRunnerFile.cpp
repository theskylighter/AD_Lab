void readAdjMatrix(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        file >> V; // Read number of vertices
        
        // Read adjacency matrix
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                int value;
                file >> value;
                if(j < V-1) {
                    char comma;
                    file >> comma; // Read and discard the comma
                }
                if(value == 1) {
                    addEdge(i, j);
                }
            }
        }
        file.close();
    }