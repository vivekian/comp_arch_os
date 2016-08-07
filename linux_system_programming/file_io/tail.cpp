#include <fstream> 
#include <vector> 
#include <string> 
#include <iostream> 

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib> 

using std::fstream; 
using std::string; 
using std::vector; 
using namespace std; 

int tail(const char *filepath, uint32_t lines) 
{ 
    struct stat buf; 

    if (stat(filepath, &buf) == -1) { 
        cerr << "error: " << strerror(errno) << endl; 
        return -1; 
    }

    ifstream infile(filepath); 
    vector<string> filecontents; 
    string line; 

    while(getline(infile, line)) { 
        filecontents.emplace_back(line); 
    } 

    if (filecontents.size() < lines) { 
        lines = filecontents.size(); 
    } 

    auto start  = filecontents.size() - lines; 
    auto end = start + lines; 

    while (start <= end) { 
        cout << filecontents[start++] << endl; 
    }

    return 0; 
} 

void usage()
{ 
    cout << "./vtail filename num_lines" << endl; 
}

int main(int argc, char** argv) 
{
    if (argc != 3) { 
       usage(); 
       return 1; 
    } 

    return tail(argv[1], atoi(argv[2])); 
}


