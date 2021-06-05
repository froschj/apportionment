/*
 * text interface to apportion seats specified in a csv. 
 */

#include "../src/State.hpp"
#include "../src/methods.hpp"
#include "../src/Apportionment.hpp"
#include "../src/ApportionmentFactory.hpp"

#ifdef WINDOWS
#define TCLAP_NAMESTARTSTRING "~~"
#define TCLAP_FLAGSTARTSTRING "/"
#endif
#include "../src/tclap/CmdLine.h"

#include <iostream>
#include <string>
#include <exception>
#include <limits>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>


#define VERSION "0.1"
#define DEFAULT_SEATS 435
#define DEFAULT_METHOD ApportionmentFactory::HuntingtonHill
#define DEFAULT_METHOD_STRING "huntingtonhill"

struct Parameters {
    unsigned seats = DEFAULT_SEATS;
    ApportionmentFactory::AppMethod useMethod = DEFAULT_METHOD;
    bool isFileInput = false;
    std::string inputFileName = "";
    bool isFileOutput = false;
    std::string outputFileName = "";
    bool isPriorityOutput = false;
    std::string priorityFileName = "";
};

State parseLine(const std::string &record);
void usageNote(const char *progName);
void readStates(
    std::unique_ptr<Apportionment> const &dest, std::istream &input
);
void writePriorityList(
    std::ostream &dest, 
    unsigned numSeats, 
    std::unique_ptr<Apportionment> const &src
);

std::unique_ptr<struct Parameters> parseArguments();

int main(int argc, const char** argv) {
    // get the parameters
    std::unique_ptr<struct Parameters> parameters = parseArguments(argc, argv);
    if (parameters == nullptr) {
        return 1;
    }

    // create an apportinment object
    std::unique_ptr<Apportionment> a = 
        ApportionmentFactory::createApportionment(
            parameters->useMethod;
        );

    //fill the Apportionment object
    try {
        // select correct input
        if (parameters->isFileInput) {
            // open file 
            std::ifstream inputFile;
            inputFile.exceptions (ifstream::badbit);
            inputFile.open(parameters->inputFileName);
            readStates(a, inputFile);
        } else {
            readStates(a, std::cin);
        }
    }
    catch (const ifstream::failure& e) {
        std::cerr << e.what() <<std::endl;
        return 1;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (const char *e) {
        std::cerr << e << std::endl;
        return 1;
    }
    
    //check that we have a valid setup
    if (parameters->seats < a->getNumStates()) {
        std::cerr << "Number of seats to apportion must be larger than " 
        << "number of states" << std::endl;
        return 1;
    }

    //open a file to store the priority list
    std::string fileName = argv[1];
    fileName += "_priorities.csv"; 
    std::ofstream priorityList;
    priorityList.open(fileName);
    if (priorityList.fail()) {
        std::cerr << "could not open output file" << std::endl;
        return 1;
    }
    //write priority list to a file
    writePriorityList(priorityList, seats, a);
    priorityList.close();

    //write apportioned seats to stdout
    std::vector<State> apportioned = a->getStates();
    std::sort(apportioned.begin(), apportioned.end(), StateAlpha(true));
    for (auto it = apportioned.cbegin(); it != apportioned.cend(); ++it) {
        std::cout << it->getName() << ',' << it->getSeats() <<std::endl;
    }

    return 0;
}


State parseLine(const std::string &record) {
    std::size_t fieldSep = record.find_first_of(',');
    if (fieldSep == std::string::npos) {
        throw "Malformed input";
    }
    std::string name = record.substr(0, fieldSep);
    ++fieldSep;
    std::size_t recordSep = record.find_last_of('\n', fieldSep);
    recordSep -= fieldSep;
    unsigned long pop = stoul(record.substr(fieldSep, recordSep));
    return State(name, pop);
}

void usageNote(const char *progName) {
    std::cerr << "USAGE: " << progName << " $seats" << std::endl 
        << "$seats must be a positive integer less than "
        << std::numeric_limits<unsigned>::max() << std::endl
        << "CSV StateName,StatePop\\n accepted on stdin" << std::endl
        << "CSV input terminated with EOF" << std::endl;
}

void readStates(
    std::unique_ptr<Apportionment> const &dest, std::istream &input
) {
    std::string record;
    while(std::getline(input,record)) {
        dest->addState(parseLine(record));
    }
}

void writePriorityList(
    std::ostream &dest, 
    unsigned numSeats, 
    std::unique_ptr<Apportionment> const &src
) {
    for (int i = src->getSeatsApportioned() + 1; i <= numSeats; ++i) {
    dest << i << ',';
    dest << src->topStatePriority() << ',';
    dest << src->topStateName() << ',';
    dest << src->topStateSeats() + 1 << std::endl;
    src->addSeat();
    }
}

std::unique_ptr<struct Parameters> parseArguments(int argv, const char **argc) {
    std::unique_ptr<struct Parameters> params = 
    std::make_unique<struct Parameters>;
    try {
        // get the parser
        TCLAP::CmdLine cmd("Apportionment Calculator", ' ', VERSION);

        // define positional argument for number of seats
        TCLAP::UnlabeledValueArg<unsigned> seatsArg(
            "seats", 
            "Number of seats to apportion",
            false,
            DEFAULT_SEATS,
            "Positive Number > number of states"
        );

        // define switch to change method
        std::vector<std::string> allowed;
        std::map<std::string,ApportionmentFactory::AppMethod> methodMap;
        methodMap["adams"] = ApportionmentFactory::Adams;
        methodMap["dean"] = ApportionmentFactory::Dean;
        methodMap[DEFAULT_METHOD_STRING] = ApportionmentFactory::HuntingtonHill;
        methodMap["webster"] = ApportionmentFactory::Webster;
        methodMap["jefferson"] = ApportionmentFactory::Jefferson;
        for (auto it = methodMap.begin(); it != methodMap.end(); ++it) {
            allowed.push_back(it->first);
        }
        TCLAP::ValuesConstraint<std::string> allowedVals( allowed );
        TCLAP::ValueArg<std::string> methodArg(
            "m",
            "method",
            "Apportionment Method",
            false,
            DEFAULT_METHOD_STRING,
            allowedVals
        );

        // define switch to specify input file
        TCLAP::ValueArg<std::string> inputArg(
            "f",
            "file",
            "Input File Name (CSV <state>,<population>)",
            false,
            "input.csv",
            "filename"
        );

        // define switch to specify output file
        TCLAP::ValueArg<std::string> outputArg(
            "o",
            "output",
            "Output File Name (CSV <state>,<seats>)",
            false,
            "output.csv",
            "filename"
        );

        // define switch to export priority list
        TCLAP::ValueArg<std::string> priorityArg(
            "p",
            "priority",
            "Priority List File Name (CSV <seat number>,<priority value>,<state>,<state seats>)",
            false,
            "priority.csv",
            "filename"
        );

        // add arguments to the parser
        cmd.add(seatsArg);
        cmd.add(methodArg);
        cmd.add(inputArg);
        cmd.add(outputArg);
        cmd.add(priorityArg);

        // parse
        cmd.parse(argc,argv);

        // build the return struct
        params->seats = seatsArg.getValue();
        if (methodArg.isSet()) {
            params->useMethod = methodMap[methodArg.getValue()];
        }
        params->isFileInput = inputArg.isSet();
        if (params->isFileInput) {
            params->inputFileName = inputArg.getValue();
        }
        params->isFileOutput = outputArg.isSet();
        if (params->isFileOutput) {
            params->outputFileName = outputArg.getValue();
        }
        params->isPriorityOutput = priorityArg.isSet();
        if (params->isPriorityOutput) {
            params->priorityFileName = priorityArg.getValue();
        }
    } catch (TCLAP::ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() 
            << std::endl; 
        return nullptr;
    }

    return params
}