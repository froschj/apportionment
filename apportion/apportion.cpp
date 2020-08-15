/*
 * text interface to apportion seats specified in a csv. 
 */

#include "../src/State.hpp"
#include "../src/methods.hpp"
#include "../src/Apportionment.hpp"
#include "../src/ApportionmentFactory.hpp"

#include <iostream>
#include <string>
#include <exception>
#include <limits>
#include <stdexcept>
#include <memory>
#include <fstream>
#include <algorithm>

unsigned parseArgs(int numArgs, const char **args);
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

int main(int argc, const char** argv) {
    //verify argument
    unsigned seats;
    try {
        seats = parseArgs(argc, argv);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        usageNote(argv[0]);
        return 64;
    }

    std::unique_ptr<Apportionment> a = 
        ApportionmentFactory::createApportionment(
            ApportionmentFactory::HuntingtonHill
        );

    //fill the Apportionment object
    try {
        readStates(a, std::cin);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (const char *e) {
        std::cerr << e << std::endl;
    }
    

    //check that we have a valid setup
    if (seats < a->getNumStates()) {
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

//checks for the correct number of arguments. return number of seats to 
//apportion. throws an exception if arguments are incorrect
unsigned parseArgs(int numArgs, const char **args) {

    if (numArgs != 2) {
        throw std::invalid_argument("Invalid Syntax");
    }

    std::string s = args[1];
    unsigned long temp = std::stoul(s);
    if (temp > std::numeric_limits<unsigned>::max()) {
        throw std::out_of_range("Argument out of range");
    }

    return temp;
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