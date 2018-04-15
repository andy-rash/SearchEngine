/*!
 * \file SearchEngine.cpp
 * \brief Contains the implementation for SearchEngine objects.
 */

#include "SearchEngine.hpp"

SearchEngine::SearchEngine() {

    indexer = new HashTableIndex();
    
    numDocs = 0;
    numTokens = 0;
    
    indexer->loadIndex();
    numDocs = indexer->getNumDocs();
    numTokens = indexer->getNumTokens();
    
}

SearchEngine::~SearchEngine() {
    
    delete indexer;
    indexer = nullptr;
    
}

void SearchEngine::addDocument(const std::string& path) { indexer->addDocument(path); }

void SearchEngine::clearIndex() { indexer->clearIndex(); }

void SearchEngine::interactive() {
    
    int choice = 0;
    int documentID = 0;
    std::string file = "";
    bool persist = true;
    std::string queryString = "";
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed;
    
restart:
    
    std::system("clear");
    
    std::cout << std::endl;
    std::cout << "*************************" << std::endl;
    std::cout << "**   INTERACTIVE MENU  **" << std::endl;
    std::cout << "*************************" << std::endl << std::endl;
    
    std::cout << "1. Use an AVL tree for the index" << std::endl;
    std::cout << "2. Use a hash table for the index" << std::endl;
    std::cout << "3. Make the index" << std::endl;
    std::cout << "4. Search" << std::endl;
    std::cout << "5. Persist the index" << std::endl;
    std::cout << "6. Display statistics" << std::endl;
    std::cout << "7. Back" << std::endl << std::endl;
    
    while(persist) {
        
        std::cout << ">> ";
        std::cin >> choice;
        
        while(std::cin.fail()) {
            
            std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            
            std::cout << ">> ";
            std::cin >> choice;
            
        }
        
        switch(choice) {
                
            case 1:
                
                // make AVLIndex object
                
                std::cout << std::endl;
                std::cout << "Working..." << std::endl;
                
                if(!indexer->emptyIndex()) { indexer->clearIndex(); numDocs = 0; numTokens = 0; }
                
                delete indexer;
                
                indexer = new AVLTreeIndex();
                
                std::cout << std::endl;
                std::cout << "Done." << std::endl;
                
                usleep(250 * 1000);
                
                goto restart;
                
                break;
                
            case 2:
                
                // make HashIndex object
                
                std::cout << std::endl;
                std::cout << "Working..." << std::endl;
                
                if(!indexer->emptyIndex()) { indexer->clearIndex(); numDocs = 0; numTokens = 0; }
                
                delete indexer;
                
                indexer = new HashTableIndex();
                
                std::cout << std::endl;
                std::cout << "Done." << std::endl;
                
                usleep(250 * 1000);
                
                goto restart;
                
                break;
                
            case 3:
                
                std::cout << std::endl;
                std::cout << "Provide the path to a directory containing properly formatted documents: " << std::endl;
                
                std::cout << std::endl;
                std::cout << "path >> ";
                
                std::cin >> file;
                
                std::cout << std::endl;
                std::cout << "Working..." << std::endl;
                
                start = std::chrono::system_clock::now();
                
                indexer->makeIndex(file);
                
                end = std::chrono::system_clock::now();
                
                elapsed = end - start;
                
                std::cout << std::endl;
                std::cout << "Done in:" << std::endl;
                std::cout << elapsed.count() << " seconds" << std::endl;
                std::cout << elapsed.count() / 60 << " minutes" << std::endl;
                
                usleep(500 * 1000);
                
                std::cout << std::endl;
                
                goto restart;
                
                break;
                
            case 4:
                
                std::cout << std::endl;
                std::cout << "Search: " << std::endl;
                
                std::cout << std::endl;
                std::cout << "search >> ";
                
                std::cin.ignore();
                std::getline(std::cin,queryString);
                
                query.search(queryString,*indexer);
                
                // TODO: add stuff here to be able to request a document
                
                std::cout << std::endl;
                std::cout << "Provide the document ID for a document to view or 0 to continue: " << std::endl;
                
                std::cout << std::endl;
                std::cout << "document ID# >> ";
                
                std::cin >> documentID;
                
                while(std::cin.fail()) {
                    
                    std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
                    std::cin.clear();
                    std::cin.ignore(256,'\n');
                    
                    std::cout << "document ID# >> ";
                    std::cin >> choice;
                    
                }
                
                if(choice == 0) { break; }
                
                {
                
                    Document tmp = indexer->getDocumentByID(choice);
                    bool returnFromDoc = false;
                    char decision = '\0';
                    
                    std::system("clear");
                    
                    std::cout << std::endl;
                    std::cout << "Title: " << tmp.title() << std::endl;
                    std::cout << "Contributor: " << tmp.username() << std::endl;
                    std::cout << "Date: " << tmp.date() << " @ " << tmp.time() << std::endl;
                    std::cout << std::endl << tmp.body() << std::endl;
                    std::cout << std::endl;
                    
                    while(returnFromDoc != true) {
                    
                        std::cout << "Return to menu? y/n >> ";
                        std::cin >> decision;
                        
                        while(std::cin.fail()) {
                            
                            std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
                            std::cin.clear();
                            std::cin.ignore(256,'\n');
                            
                            std::cout << "Return to menu? y/n >> ";
                            std::cin >> decision;
                            
                        }
                        
                        if(decision == 'y') {
                            
                            returnFromDoc = true;
                            
                            goto restart;
                            
                            break;
                        
                        }
                        
                    }
                    
                }
                
                break;
                
            case 5:
                
                std::cout << std::endl;
                std::cout << "Working..." << std::endl;
                
                indexer->listIndex();
                
                std::cout << std::endl;
                std::cout << "Done." << std::endl;
                
                usleep(250 * 1000);
                
                goto restart;
                
                break;
                
            case 6:
                
                std::cout << std::endl;
                std::cout << "Documents processed: " << indexer->getNumDocs() << std::endl;
                std::cout << "Words indexed: " << indexer->getNumTokens() << std::endl;
                std::cout << std::endl;
                
                break;
                
            case 7:
                
                persist = false;
                
                break;
                
            default:
                
                std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
                
                goto restart;
                
                break;
                
        }
        
    }
    
}

void SearchEngine::launchUI() {
    
    int choice = 0;
    bool persist = true;
    
restart:
    
    std::system("clear");
    
    std::cout << std::endl;
    std::cout << " __  __           _                 __          ___ _    _ " << std::endl;
    std::cout << "|  \\/  |         | |                \\ \\        / (_) |  (_)" << std::endl;
    std::cout << "| \\  / |_   _ ___| |_ __ _ _ __   __ \\ \\  /\\  / / _| | ___ " << std::endl;
    std::cout << "| |\\/| | | | / __| __/ _` | '_ \\ / _` \\ \\/  \\/ / | | |/ / |" << std::endl;
    std::cout << "| |  | | |_| \\__ \\ || (_| | | | | (_| |\\  /\\  /  | |   <| |" << std::endl;
    std::cout << "|_|  |_|\\____|___/\\__\\__,_|_| |_|\\__, | \\/  \\/   |_|_|\\_\\_|" << std::endl;
    std::cout << "                                  __/ |                    " << std::endl;
    std::cout << "                                 |___/                     " << std::endl << std::endl << std::endl;
    
    std::cout << "1. Interactive Mode" << std::endl;
    std::cout << "2. Maintenance Mode" << std::endl;
    std::cout << "3. Quit" << std::endl << std::endl;
    
    while(persist) {
    
        std::cout << ">> ";
        std::cin >> choice;
        
        while(std::cin.fail()) {
        
            std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            
            std::cout << ">> ";
            std::cin >> choice;
            
        }
        
        switch(choice) {
                
            case 1:
                interactive();
                
                goto restart;
                
                break;
            
            case 2:
                maintenance();
                
                goto restart;
                
                break;
            
            case 3:
                std::cout << std::endl << "Quitting..." << std::endl << std::endl;
                persist = false;
                break;
            
            default:
                std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
                break;
                
        }
        
    }
    
}

void SearchEngine::maintenance() {
    
    int choice = 0;
    bool persist = true;
    std::string path = "";
    
restart:
    
    std::system("clear");
    
    std::cout << std::endl;
    std::cout << "**************************" << std::endl;
    std::cout << "**   MAINTENANCE MENU   **" << std::endl;
    std::cout << "**************************" << std::endl << std::endl;
    
    std::cout << "1. Add new document" << std::endl;
    std::cout << "2. Clear the index" << std::endl;
    std::cout << "3. Back" << std::endl << std::endl;
    
    while(persist) {
        
        std::cout << ">> ";
        std::cin >> choice;
        
        while(std::cin.fail()) {
            
            std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            
            std::cout << ">> ";
            std::cin >> choice;
            
        }
        
        switch(choice) {
                
            case 1:
                
                std::cout << std::endl;
                std::cout << "Provide the path to a properly formatted document: " << std::endl;
                
                std::cout << std::endl;
                std::cout << "path >> ";
                
                std::cin >> path;
                
                addDocument(path);
                
                std::cout << std::endl;
                
                goto restart;
                
                break;
                
            case 2:
                
                std::cout << std::endl;
                std::cout << "Working..." << std::endl;
                
                clearIndex();
                
                std::cout << std::endl;
                std::cout << "Done." << std::endl;
                
                usleep(250 * 1000);
                
                goto restart;
                
                break;
                
            case 3:
                
                persist = false;
                
                break;
                
            default:
                
                std::cout << std::endl << "Invalid input. Please try again." << std::endl << std::endl;
                
                goto restart;
                
                break;
                
        }
        
    }
    
}
