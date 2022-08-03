#include "parser.h"
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Process {
    string command_name;
    char *read_file = nullptr, *write_file = nullptr;
    char** procCommands;

public:
    Process() {}
    Process(string command_name, char** args) {
        this->command_name = command_name;
        this->procCommands = args;
    }
    void setPipeFiles(char* fromFile, char* toFile) {
        this->read_file = fromFile;
        this->write_file = toFile;
    }
    void concurrentProcRun() {
        cout << "PROC RUN" << endl;
        int fd[2];
        if (this->read_file) {
            fd[0] = open(&(this->read_file[0]), O_RDONLY, 0666);
            dup2(fd[0], 0);
            close(fd[0]);
        }

        if (this->write_file) {
            fd[1] = open(&(this->write_file[0]), O_CREAT | O_WRONLY | O_APPEND,
                         0666);
            dup2(fd[1], 1);
            close(fd[1]);
        }
        cout << "before exec: " << endl;
        if (fork() == 0) {
            execvp(this->command_name.c_str(), this->procCommands);
            cout << "ERROR DURING EXECVP EXECUTION" << endl;
        }
    }
};

class ProcessBundle {
    string bundle_name;
    char *read_bfile, *write_bfile;
    vector<Process> bundleProcs;
    int processCount = 0;

public:
    ProcessBundle() {}
    ProcessBundle(string bundle_name) { this->bundle_name = bundle_name; }
    void setBundleName(string bundle_name) { this->bundle_name = bundle_name; }

    void addProcess(Process newProcess) {
        this->bundleProcs.push_back(newProcess);
        this->processCount++;
    }
    int getprocessCount() { return this->processCount; }
    void setPipeBFiles(char* fromBFile, char* toBFile) {
        cout << "pipe b files" << endl;
        this->read_bfile = fromBFile;
        this->write_bfile = toBFile;
        cout << "Process count: " << this->processCount << endl;

        for (int i = 0; i < this->processCount; i++) {
            this->bundleProcs[i].setPipeFiles(this->read_bfile,
                                              this->write_bfile);
        }
    }
    void concurrentBundleRun(int* fromRepeater, int* toRepeater) {
        int c = 0, statusCode, id1;
        cout << this->bundle_name << endl;
        for ( int i = 0; i < this->processCount; i++) {
            cout << "proc number: " << i + 1 << endl;
            id1 = fork();
            if (id1 == -1)
                cout << "CANNOT FORK" << endl;
            else if (id1) {
                // parent process
                c++;
            } else {
                if (fromRepeater) {
                    // input from prev bundle
                    cout << "from repeater" << endl;
                    dup2(*(fromRepeater), 1);
                    close(*(fromRepeater));
                }

                // child process
                if (toRepeater) {
                    // output to next bundle
                    cout << "to repeater" << endl;
                    dup2(*(toRepeater + 2 * i + 1), 0);
                    close(*(toRepeater + 2 * i + 1));
                    // parent process

                }
                cout << "start proc run: " << i + 1 << endl;
                this->bundleProcs[i].concurrentProcRun();
                cout << "cont. proc run: " << i + 1 << endl;
                exit(0);
            }
        }
        for (; c--; wait(&statusCode))
            cout<< "wait: "<<c <<endl;
    }
};

int main() {
    bool continue_flag = true;
    int is_create = 0, holder = 0, statusCode;
    parsed_input parsedInput;

    vector<ProcessBundle> all_bundles;
    unordered_map<string, int> bundle_ref;

    Process newProcess;
    ProcessBundle newBundle;

    while (continue_flag) {
        char buffer[257];
        cin.getline(buffer, 256);
        int size = strlen(buffer);
        buffer[size] = '\n';
        buffer[size + 1] = '\0';

        holder = parse(buffer, is_create, &parsedInput);
        if (is_create) {
            if (holder) {
                cout << "PBS :: RECEIVED" << endl;
                all_bundles.push_back(newBundle);
                bundle_ref[parsedInput.command.bundle_name] =
                    all_bundles.size() - 1;
                is_create = 0;
            } else {
                char** arg = parsedInput.argv;
                newProcess = Process(string(*(arg)), arg);
                newBundle.addProcess(newProcess);
            }
        } else {
            if (parsedInput.command.type == PROCESS_BUNDLE_CREATE) {
                cout << "BUNDLE CREATION STARTED :: BUNDLE NAME: "
                     << parsedInput.command.bundle_name << endl;
                newBundle = ProcessBundle(parsedInput.command.bundle_name);
                is_create = 1;
            } else if (parsedInput.command.type == PROCESS_BUNDLE_EXECUTION) {
                vector<ProcessBundle> execs;
                cout << "BUNDLE EXECUTION :: BUNDLES TO EXECUTE : " << endl;
                for (int i = 0; i < parsedInput.command.bundle_count; i++) {
                    cout << "[" << parsedInput.command.bundles[i].name << "]"
                         << endl;
                    ProcessBundle newExec = all_bundles
                        [bundle_ref[parsedInput.command.bundles[i].name]];
                    //
                    newExec.setPipeBFiles(
                        parsedInput.command.bundles[i].input,
                        parsedInput.command.bundles[i].output);
                    execs.push_back(newExec);
                }
                cout << "bundle count: " << parsedInput.command.bundle_count
                     << endl;
                // first bundle run (at least one bundle to execute)
                if (parsedInput.command.bundle_count == 1) {
                    cout << "1 bundle  total" << endl;
                    execs[0].concurrentBundleRun(nullptr, nullptr);
                }
                cout << "bundle count: " << parsedInput.command.bundle_count
                     << endl;
                int total_count_repeaters=0;
                int fromRepeater[2];
                for (int i = 0; i < parsedInput.command.bundle_count - 1; i++) {
                    if (i == 0) {
                      cout << "FIRST BUNDLE" << endl;
                    }else{
                      cout << "INTER-BUNDLE" << endl;
                    }
                    cout << "Repeater part: " << i << endl;

                    pipe(fromRepeater);
                    int next_bundle_size = execs[i + 1].getprocessCount();
                    total_count_repeaters += next_bundle_size;
                    cout << "Next bundle size: " << next_bundle_size << endl;
                    int* toRepeater = new int[next_bundle_size * 2];
                    for (int j = 0; j < next_bundle_size; j++) {
                        pipe(toRepeater + 2 * j);
                    }
                    int repeater_id1 = fork();
                    if (repeater_id1 == -1)
                        cout << "CANNOT FORK" << endl;
                    else if (repeater_id1) {
                        // parent process
                        cout << "PARENT"<<endl;
                        for (int j = 0; j < next_bundle_size; j++) {
                            close(*(toRepeater + 2 * j + 1));
                        }
                        // todo
                        execs[i + 1].concurrentBundleRun(fromRepeater,
                                                         toRepeater);
                    } else {
                        // child process
                        // repeater will be held here
                        // burada stdin input ayarlamak lazım
                        cout << "CHILD" <<endl;
                        if(fromRepeater == nullptr){
                          exit(0);
                        }
                        char repeater_buffer[256];
                        int readbyte_count;
                        for (int j = 0; j < next_bundle_size ;j++) {
                            close(toRepeater[2*j]);
                        }
                        close(fromRepeater[1]);
                        cout << "BEFORE WHILE" <<endl;
                        while ((readbyte_count = read(
                                    *fromRepeater, repeater_buffer, 256)) > 0) {
                            for (int j = 0; j < next_bundle_size; j++) {

                                write(toRepeater[2 * j + 1], repeater_buffer,
                                      readbyte_count);
                            }
                        }
                        cout << "AFTER WHILE" <<endl;
                        exit(0);
                    }
                    close(fromRepeater[0]);
                    close(fromRepeater[1]);
                }
                // run the last bundle here
                if (parsedInput.command.bundle_count > 1) {
                    cout << "LAST BUNDLE" << endl;
                    pipe(fromRepeater);
                    execs[parsedInput.command.bundle_count - 1]
                        .concurrentBundleRun(fromRepeater, nullptr);
                    cout << "END LAST BUNDLE" << endl;
                    close(fromRepeater[0]);
                    close(fromRepeater[1]);
                }
                // wait for repeaters
                cout << "TOTAL REPEATER: " << total_count_repeaters-- << endl;
                for (; total_count_repeaters--; wait(&statusCode))
                    cout << "WAIT - REPEATER: " << total_count_repeaters << endl;
            } else if (parsedInput.command.type == QUIT) {
                continue_flag = false;
            }
        }
    }
    return 0;
}
