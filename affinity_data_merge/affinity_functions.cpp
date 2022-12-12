

void loadCsv(const string& filename) {
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    emailAddresses.push_back(line);
  }
}