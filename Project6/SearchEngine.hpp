/*!
 * \file SearchEngine.hpp
 * \brief Contains the interface for SearchEngine objects.
 */

#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "AVLTreeIndex.hpp"
#include "Document.hpp"
#include "HashTableIndex.hpp"
#include "IndexInterface.hpp"
#include "QueryProcessor.hpp"

/*!
 * \class SearchEngine.
 * \brief Class for performing UI functionality.
 * \see IndexInterface.
 * \see QueryProcessor.
 */

class SearchEngine {

private:
    
    IndexInterface* indexer; //!< \private A pointer to an IndexInterface.
    QueryProcessor query;    //!< \private A QueryProcessor object for processing search queries.
    int numDocs;             //!< \private An integer for holding the number of documents processed.
    int numTokens;           //!< \private An integer for holding the number of tokens processed.
    
public:
    
    /*!
     * \fn SearchEngine().
     * \brief Initializes the member data with default values and loads in the last created index file.
     */
    
    SearchEngine();
    
    /*!
     * \fn ~SearchEngine().
     * \brief Deletes the pointer to the indexer if it has been initialized.
     */
    
    ~SearchEngine();
    
    /*!
     * \fn addDocument(const std::string& path).
     * \brief Adds a new document to the index.
     * \param path - path to a file containing properly formatted XML to parse.
     */
    
    void addDocument(const std::string& path);
    
    /*!
     * \fn clearIndex().
     * \brief Clears the index.
     */
    
    void clearIndex();
    
    /*!
     * \fn interactive().
     * \brief Displays the interactive menu.
     */
    
    void interactive();
    
    /*!
     * \fn launchUI().
     * \brief Displays the main menu.
     */
    
    void launchUI();
    
    /*!
     * \fn interactive().
     * \brief Displays the maintenance menu.
     */
    
    void maintenance();
    
};

#endif /* SEARCHENGINE_HPP */
