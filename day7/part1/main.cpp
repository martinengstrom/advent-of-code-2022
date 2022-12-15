#include <iostream>
#include <vector>
#include "file.h"
#include "directory.h"
#include "split.h"

using namespace std;

directory* root;
directory* current_dir;

directory* create_directory(string name) {
    directory *dir = new directory(name, current_dir);
    if (current_dir != NULL) {
        current_dir->add_directory(dir);
    }
    return dir;
}

void change_directory(string name) {
    auto dirs = current_dir->get_subdirectories();
    for (auto& dir: dirs) {
        if (dir->get_name().compare(name) == 0) {
            current_dir = dir;
        }
    }
}

void handle_list(vector<string> output) {
    for (string item : output) {
        vector<string> splits = split(item, " ");
        if (splits[0].compare("dir") == 0) {
            create_directory(splits[1]);
        } else {
            long size = stoi(splits[0]);
            string name = splits[1];
            file* f = new file(name, size);
            current_dir->add_file(f);
        }
    }
}

void execute_command(string command, vector<string> output) {
    if (command.compare("cd ..") == 0) {
        current_dir = current_dir->get_parent();
    } else if (command.rfind("cd ", 0) == 0) {
        change_directory(command.substr(3));
    } else if (command.compare("ls") == 0) {
        handle_list(output);
    }
}

long get_size(directory* dir, long limit) {
    long total = 0;
    for (auto& subdir : dir->get_subdirectories()) {
        long size = subdir->calculate_size();
        if (subdir->calculate_size() <= limit)
            total += size;
        
        total += get_size(subdir, limit);
    }
    return total;
}

int main(int argc, char *argv[]) {
    vector<string> output_buffer; 
    string cmd;

    for (string line; getline(cin, line); ) {
        if (line.compare("$ cd /") == 0) {
            root = create_directory("/");
            current_dir = root;
            continue;
        }

        if (line.rfind("$ ", 0) == 0) {
            if (!cmd.empty()) {
                execute_command(cmd, output_buffer);
                cmd.clear();
                output_buffer.clear();
            }
            cmd = line.substr(2);
        } else {
            output_buffer.push_back(line);
        }
    }

    // There may be a pending command once output is done. Execute it
    execute_command(cmd, output_buffer);

    // And finally.. Iterate all of the directories
    // And find the ones with a size less than 100k
    long limit = 100000;
    long total = get_size(root, limit);

    cout << total << endl;

    delete root;
    return 0;
}
