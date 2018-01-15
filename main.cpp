/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dazzle
 *
 * Created on 12. Januar 2018, 17:08
 */

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm> 
#include <map>
#include <thread>

using namespace std;

struct jobInfo {
    int id = -1;
    thread job = thread();

    jobInfo() {
    };
};

struct info {
    string word;
    int numberOfOccurences = 0;
    vector<int>lineOfOccurence;
};

vector<int> removeDuplicateOccurences(vector<int> tmp) {
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    return tmp;
}

void printId(jobInfo* first) {
    cout << "ID of the Thread is fuck yo mom: " << first->id << endl;
}

void print(map<string, info> wordCount) {
    info tmp;

    for (auto it = wordCount.begin(); it != wordCount.end(); ++it) {
        tmp.lineOfOccurence = removeDuplicateOccurences(tmp.lineOfOccurence);
        tmp = it->second;
        cout << endl << it->first << ": " << tmp.numberOfOccurences << "\t Occured at: ";
        for (auto vecIt = tmp.lineOfOccurence.begin(); vecIt != tmp.lineOfOccurence.end(); ++vecIt) {
            cout << "(" << *vecIt << ") ";
        }
    }
    cout << endl <<"I terminate correctly " << endl;
}

void counterino(string filePath, int numberOfThreads,
        int threadId, map<string, info>* input) {
    
    string word;
    info tmp;
    int line = 0;
    ifstream file;
    file.open(filePath);
    
    while (file >> word) {
        //cout << word << "   " << threadId << endl;
        if (file.peek() == '\n'){
            line++;
        }
        tmp = input->operator[](word);
        tmp.word = word;
        tmp.numberOfOccurences += 1;

        tmp.lineOfOccurence.push_back(line);

        input->operator[](word) = tmp;
    }
    
    if(threadId == 0){
        //cout << "Hi" << endl;
        for (auto it = input->end(); it != input->end(); ++it ){
            cout << endl << it->first << " : " << it->second.numberOfOccurences << endl;
        }
    }
    file.close();
}

int main(int argc, char** argv) {
    char *p;
    int conv = strtol(argv[1], &p, 10);
    string filePath(argv[2]);
    map<string, info> empty;
    vector<map<string, info>> input;
    //ifstream file;
    //file.open(filePath);

    vector<jobInfo> jobs;

    int numberOfThreads = conv;
    jobInfo tmp;
    for (int i = 0; i < numberOfThreads; i++) {
        //map<string, info> empty;
        input.push_back(map<string, info>()) ;
        tmp.id = i;
        tmp.job = thread(counterino, filePath, numberOfThreads, tmp.id, &input[i]);
        jobs.push_back(std::move(tmp));
    }


    for (int i = 0; i < numberOfThreads; i++) {
        if (jobs.at(i).job.joinable())
            jobs.at(i).job.join();
    }
    cout << "Number Of threads: " << numberOfThreads << endl;
    cout << "Filepath: " << filePath << endl;
    map<string, info> check = input[0];
    
    print(check);

    return 0;
}



// THREAD DEBUGGING SHIT YOU CUNT
/* jobInfo yoCunt;
 yoCunt.id = 1;
 yoCunt.job = thread(printId,&yoCunt);
 yoCunt.job.join();
 * 
 * 
 * 
   
 */