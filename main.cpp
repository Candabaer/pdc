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

#include <chrono>
#include <regex>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm> 
#include <map>
#include <thread>
#include <sstream>

using namespace std;

struct jobInfo {
    unsigned int id = -1;
    thread job = thread();

    jobInfo() {
    };
};

struct info {
    string word;
    unsigned int numberOfOccurences = 0;
    vector<unsigned int>lineOfOccurence;
};

vector<unsigned int> removeDuplicateOccurences(vector<unsigned int> tmp) {
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
        cout << "(";
        for (auto vecIt = tmp.lineOfOccurence.begin(); vecIt != tmp.lineOfOccurence.end(); ++vecIt) {
            cout << " " << *vecIt << " ";
        }
        cout << ") ";
    }
    cout << endl << "I terminate correctly " << endl;
}

void counterino(unsigned numberOfThreads,
        unsigned threadId, map<string, info>* result, vector<info> passedLines) {
    string word;
    info tmp;
    regex ignoreRegex(" d\\*\\.");

    for (unsigned int i = 0; i < passedLines.size(); i++) {
        stringstream stringStream(passedLines[i].word);
        while (stringStream >> word) {
            if (!regex_match(word, ignoreRegex)) {
                tmp = result->operator[](word);
                tmp.word = word;
                tmp.numberOfOccurences++;
                for (unsigned int j = 0; j < passedLines[i].lineOfOccurence.size(); j++) {
                    tmp.lineOfOccurence.push_back(passedLines[i].lineOfOccurence[j]);
                }
                //
                //           cout << "I am Thread: " << threadId << " I am saving this Values: "
                //                    << " Word: " << tmp.word << " NUMBER " << tmp.numberOfOccurences << " Example Occurence: "
                //                    << tmp.lineOfOccurence[0] << endl;

                result->operator[](word) = tmp;
            }
        }
    }
}

map<string, info> mapReduce(vector<map<string, info>> input) {
    map<string, info> result;

    for (unsigned int i = 0; i < input.size(); i++) {
        for (auto it = input[i].begin(); it != input[i].end(); it++) {
            result[it->second.word].word = it->second.word;
            result[it->second.word].numberOfOccurences += it->second.numberOfOccurences;
            for (unsigned j = 0; j < it->second.lineOfOccurence.size(); j++)
                result[it->second.word].lineOfOccurence.push_back(it->second.lineOfOccurence[j]);
        }
    }
    return result;
}

int main(int argc, char** argv) {
    char *p;
    int conv = strtol(argv[1], &p, 10);
    int numberOfThreads = conv;
    string filePath(argv[2]);
    vector<jobInfo> jobs;

    ifstream file;
    file.open(filePath);
    string line;

    map<unsigned int, string> text;
    unsigned int lineNumberKey = 0;

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    while (!file.eof()) {
        getline(file, line);
        text[lineNumberKey] = line;
        lineNumberKey++;
    }


    vector<map<string, info>> result;

    unsigned int x = text.size();

    unsigned int passedVectorSize = floor(x / numberOfThreads);
    unsigned int y = x % numberOfThreads;
    unsigned int magicNumber = 0;


    for (unsigned int j = 0; j < numberOfThreads; j++) {
        result.push_back(map<string, info>());
        result.reserve(numberOfThreads);

        jobInfo tmp;
        tmp.id = j;

        vector<info> textPart;
        textPart.clear();

        if ((j + 1) * passedVectorSize + y == text.size()) {
            magicNumber = y;
        }
        for (unsigned int i = 0 + (j * passedVectorSize); i < ((j + 1)* (passedVectorSize)) + magicNumber; i++) {
            info tmpStruct;
            tmpStruct.lineOfOccurence.push_back(i + 1);
            tmpStruct.word = text[i];
            textPart.push_back(tmpStruct);
        }

        tmp.job = thread(counterino, numberOfThreads, tmp.id, &result.at(j), textPart);

        cout << "Größe vom ergebniss Vektor: " << result.size() << endl;
        cout << "Größe von ergebniss Map: " << result.at(j).size() << endl;

        jobs.push_back(move(tmp));
    }

    for (unsigned int i = 0; i < numberOfThreads; i++) {

        if (jobs.at(i).job.joinable())
            jobs.at(i).job.join();
    }

    cout << "Number Of threads: " << numberOfThreads << endl;
    cout << "Filepath: " << filePath << endl;
    cout << "Vector size " << result.size() << endl;
    print(mapReduce(result));

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::microseconds microRunTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    double runTime = microRunTime.count() / 1000000.0;
    std::cout << "Wall clock time = " << runTime << " seconds." << std::endl << std::flush;

    return 0;
}



// THREAD DEBUGGING SHIT YOU CUNT
/* jobInfo yoCunt;
 yoCunt.id = 1;
 yoCunt.job = thread(printId,&yoCunt);
 yoCunt.job.join();
 */