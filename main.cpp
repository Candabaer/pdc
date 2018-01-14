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
};

struct info {
    string word;
    int numberOfOccurences = 0;
    vector<int>lineOfOccurence;
};

void removeDuplicateOccurences (vector<int>* tmp){
    sort(tmp->begin(), tmp->end());
    tmp->erase(unique(tmp->begin(), tmp->end()), tmp->end());
}

void printId(jobInfo* first){
    cout << "ID of the Thread is fuck yo mom: " <<  first->id << endl;
}

void print(map<string, info> wordCount) {
    info tmp;
    map<string, info>::iterator it;

    for (it = wordCount.begin(); it != wordCount.end(); ++it) {
        tmp = it->second;
        int tmpint = tmp.numberOfOccurences;
        cout << endl << tmp.word << ": " << tmp.numberOfOccurences << "\t Occured at: ";
        
        removeDuplicateOccurences (&tmp.lineOfOccurence);
            
        
        vector<int>::iterator vecIt;
        for (vecIt = tmp.lineOfOccurence.begin(); vecIt != tmp.lineOfOccurence.end(); ++vecIt) {
            cout << "( " << *vecIt << " ) ";
        }
    }

}

/*map<string, info>*/ void fuck(ifstream& file/*, int numberOfThreads, int threadId*/) {
    string word;
    info tmp;
    int count;
    int line = 1;
    //bla bla bla bla

    map<string, info> input;

    while (file >> word) {
        if (file.peek() == '\n')
            line++;
        //if(line % numberOfThreads == thread.id){

            tmp = input[word];
            tmp.word = word;
            tmp.numberOfOccurences += 1;

            tmp.lineOfOccurence.push_back(line);

            input[word] = tmp;
        //}
    }
    //return input;
}

int main(int argc, char** argv) {
    char *p;
    int conv = strtol(argv[1], &p, 10);
    string filePath(argv[2]);
    ifstream file;
    file.open(filePath);
    
    vector<jobInfo> jobs;

    int numberOfThreads = conv;
    
    jobInfo tmp;
    tmp.id = 0;
    tmp.job = thread (fuck, file/*, numberOfThreads, tmp.id*/);
    tmp.job.join();
    //jobs.push_back(tmp);
    //jobs[0].join();
    /*for (int i = 0; i < numberOfThreads; i++){
        tmp.id = i;
        tmp.job = thread (count, file, tmp.id);
        jobs.push_back(tmp);
    }*/
    
    // THREAD DEBUGGING SHIT YOU CUNT
    jobInfo yoCunt;
    yoCunt.id = 1;
    yoCunt.job = thread(printId,&yoCunt);
    yoCunt.job.join();
    
    cout << "Number Of threads: " << numberOfThreads << endl;
    cout << "Filepath: " << filePath << endl;
    
    //map<string, info> result = jobs[0].job.join();
    file.close();
    
    //print(result);
    
    return 0;
}

