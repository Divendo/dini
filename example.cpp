/************************************************** Info: ***************************************************
* Author:     Divendo                                                                                       *
* Version:    1.1                                                                                           *
* Website:    http://divendo-webs.com                                                                       *
*                                                                                                           *
* Example program on how to use dini                                                                        *
************************************************************************************************************/

#include <iostream>
#include <ctime>
#include "dini.h"

using namespace std;

// Functions to print the contents of a dini::iniFile to the screen
void printFile(const dini::iniFile& file);
void printSection(const dini::iniSection& section);

int main()
{
    try
    {
        // Create an ini file, and a string to temporary store the user's input
        dini::iniFile ini;
        string tmp;

        // Ask some questions to fill the ini with information
        cout<<"Please enter your name: ";
        getline(cin, tmp);
        ini["personal"]["name"]=tmp;

        cout<<"Please enter your age: ";
        getline(cin, tmp);
        ini["personal"]["age"]=tmp;

        cout<<"Please enter your favourite number: ";
        getline(cin, tmp);
        ini["personal"]["fav_nr"]=tmp;

        // Store some other information in another section
        ini["record"]["time_of_recording"]=static_cast<double>(time(0));    // The cast is needed because time(0) returns a time_t value
        ini["record"]["number_of_questions"]=3;
        ini["record"]["few_lines_of_text"]="line1\nline2\nline3";

        ini.saveToFile("test.ini");
        cout<<"\nThe ini file has been saved to 'test.ini'.\n";

        // Create another ini file
        dini::iniFile loaded;
        // Load the settings from the previous ini
        loaded.loadFromFile("test.ini");
        cout<<"\nThe ini file ('test.ini'), has been loaded again, this is what it contains:\n\n";
        printFile(loaded);
    }
    // Catch and handle any corruption errors
    catch(dini::errorCorrupted& e)
    {
        cerr<<"The file is corrupted!\n";
        switch(e.type)
        {
            case dini::errorCorrupted::typeSection:
                cerr<<"Corruption found while parsing a section...\n";
            break;
            case dini::errorCorrupted::typeValue:
                cerr<<"Corruption found while parsing a value...\n";
            break;
            case dini::errorCorrupted::typeNoSection:
                cerr<<"A value was found while no section has been found yet!\n";
            break;
        }
        cerr<<"At line: "<<e.line<<", raw data at that line:\n"<<e.lineData<<endl;
    }
    // Catch and handle any file errors
    catch(dini::fileError& e)
    {
        cerr<<"An error occurred while processing the file '"<<e.filename<<"'!\n";
        switch(e.type)
        {
            case dini::fileError::writeError:
                cerr<<"The error occurred while writing to the file..."<<endl;
            break;
            case dini::fileError::readError:
                cerr<<"The error occurred while reading the file..."<<endl;
            break;
            case dini::fileError::openForReadingError:
                cerr<<"The error occurred while trying to open the file for reading..."<<endl;
            break;
            case dini::fileError::openForWritingError:
                cerr<<"The error occurred while trying to open the file for writing..."<<endl;
            break;
        }
    }
    // Catch and handle any unknown name errors
    catch(dini::unknownName& e)
    {
        cerr<<"An unknown name of a section or value was requested, the name was: "<<e.name<<endl;
    }
    // Catch and handle any valuetype errors
    catch(dini::valueType& e)
    {
        cerr<<"An error occurred while trying to convert an ini value to a ";
        switch(e)
        {
            case dini::typeBool:    cerr<<"bool";   break;
            case dini::typeChar:    cerr<<"char";   break;
            case dini::typeDouble:  cerr<<"double"; break;
            case dini::typeInt:     cerr<<"int";    break;
            // dini::typeString is not necessary, because it will never be thrown
        }
        cerr<<'!'<<endl;
    }

    cin.get();
    return 0;
}

void printFile(const dini::iniFile& file)
{
    // Loop through all sections and print each section
    for(dini::iniFile::const_iterator pos=file.begin(); pos!=file.end(); pos++)
        printSection(*pos);
}

void printSection(const dini::iniSection& section)
{
    // Print the section name
    cout<<'['<<section.name()<<"]\n";
    // Loop through all values in the section and print them, note that the values are printed directly now,
    // so no escape sequences will be used for for example newlines.
    for(dini::iniSection::const_iterator pos=section.begin(); pos!=section.end(); pos++)
        cout<<pos->name()<<'='<<pos->toString()<<'\n';
    cout<<endl;
}
