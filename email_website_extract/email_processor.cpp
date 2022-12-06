#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

// Function to parse a CSV file and extract the email addresses
vector<string> parseCsv(const string& csv) {
  vector<string> emailAddresses;

  // Split the CSV into lines
  string line;
  istringstream csvStream(csv);
  while (getline(csvStream, line)) {
    // Split each line into fields
    string field;
    istringstream lineStream(line);
    while (getline(lineStream, field, ',')) {
      // Add each email address field to the vector
      emailAddresses.push_back(field);
    }
  }

  return emailAddresses;
}

// Function to dedupe the email addresses and extract the websites
map<string, set<string>> dedupeEmailAddresses(
    const vector<string>& emailAddresses) {
  map<string, set<string>> websites;

  // Loop through the email addresses and extract the websites
  for (const string& emailAddress : emailAddresses) {
    // Split the email address into the username and domain
    string username, domain;
    tie(username, domain) = make_pair(
        emailAddress.substr(0, emailAddress.find('@')),
        emailAddress.substr(emailAddress.find('@') + 1));

    // Check if the domain is already in the map
    auto it = websites.find(domain);
    if (it == websites.end()) {
      // If not, add it to the map with an empty set of usernames
      websites.insert({domain, {}});
    }

    // Add the username to the set for the domain
    websites[domain].insert(username);
  }

  return websites;
}

// Function to generate a CSV of the deduped email addresses
string generateCsv(
    const map<string, set<string>>& websites) {
  string csv;

  // Loop through the websites and generate the CSV
  for (const auto& [domain, usernames] : websites) {
    // Add the domain to the CSV
    csv += domain + '\n';

    // Add the usernames for the domain to the CSV
    for (const string& username : usernames) {
      csv += username + '\n';
    }
  }

  return csv;
}

// Function to be called from JavaScript to process the CSV file
string processCsv(const string& csv) {
  // Parse the CSV file and extract the email addresses
  std::vector<std::string> emailAddresses = parseCsv(csv);

  // Dedupe the email addresses and extract the websites
  std::map<std::string, std::set<std::string>> websites =
      dedupeEmailAddresses(emailAddresses);

  // Generate a CSV of the deduped email addresses
  std::string csvData = generateCsv(websites);

  return csvData;
}

EMSCRIPTEN_BINDINGS(email_processor) {
  emscripten::function("processCsv", &processCsv);
}