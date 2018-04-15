#ifndef INDEXINTERFACE_HPP
#define INDEXINTERFACE_HPP

#include <fstream>
/*!
 * \file IndexInterface.hpp
 * \brief Contains the interface for IndexInterface objects.
 */

#include <string>

#include "DocumentProcessor.hpp"

#include "./Resources/pugixml-1.7/src/pugixml.hpp"

/*!
 * \class IndexInterface.
 * \brief Class for dealing with the index.
 * \see AVLTreeIndex.
 * \see HashTableIndex.
 */

class IndexInterface {

protected:
    
    DocumentProcessor docProc; //!< \private A DocumentProcessor object for parsing and processing source documents.
    std::ofstream outputFile;  //!< \private A std::ofstream object for outputting the index.
    int numDocs;               //!< \private An integer for containing the number of documents processed.
    int numTokens;             //!< \private An integer for containing the number of tokens processed.
    
public:
    
    /*!
     * \fn IndexInterface().
     * \brief Initializes the member data with default values.
     */
    
    IndexInterface() : numDocs(0),
                       numTokens(0) {}
    
    /*!
     * \fn ~IndexInterface().
     * \brief Virtual destructor for proper memory management of this and child classes.
     */
    
    virtual
    ~IndexInterface() {}
    
    /*!
     * \fn addDocument(const std::string& path).
     * \brief Virtual function for adding a document.
     * \param path - a path to a file to add to the index.
     */
    
    virtual
    void addDocument(const std::string& path) = 0;
    
    /*!
     * \fn clearIndex().
     * \brief Virtual function for clearing the index.
     */
    
    virtual
    void clearIndex() = 0;
    
    /*!
     * \fn emptyIndex().
     * \brief Virtual function for returning whether the index is empty.
     * \return boolean whether the index is empty.
     */
    
    virtual
    bool emptyIndex() const = 0;
    
    /*!
     * \fn findWord(std::string& term).
     * \brief Virtual function for finding a word in the index.
     * \param term - term to search for in the index.
     * \return Token (by value for HashTableIndex compatibility) representing the searched word.
     */
    
    virtual
    Token findWord(std::string& term) = 0;
    
    /*!
     * \fn getDocumentByID(const int& docID).
     * \brief Virtual function for getting a document pertaining to a given ID number.
     * \param docID - a document ID number.
     * \return Document reference.
     */
    
    virtual
    const Document& getDocumentByID(const int& docID) = 0;
    
    /*!
     * \fn getNumDocs().
     * \brief Returns the number of documents processed.
     * \return integer representing the number of documents processed.
     */
    
    int getNumDocs() const { return numDocs; }
    
    /*!
     * \fn getNumTokens().
     * \brief Returns the number of tokens processed.
     * \return integer representing the number of tokens processed.
     */
    
    int getNumTokens() const { return numTokens; }
    
    /*!
     * \fn hasWord(std::string& term).
     * \brief Virtual function for returning whether the index contains a given word.
     * \param term - a term to search the index for.
     * \return boolean whether the index contains the word.
     */
    
    virtual
    bool hasWord(std::string& term) = 0;
    
    /*!
     * \fn listIndex().
     * \brief Virtual function for writing the persistent index.
     */
    
    virtual
    void listIndex() = 0;
    
    /*!
     * \fn loadIndex().
     * \brief Virtual function for loading an index in from persistent state.
     * \return boolean whether the index was successfully loaded.
     */
    
    virtual
    bool loadIndex() = 0;
    
    /*!
     * \fn makeIndex(const std::string& fileName).
     * \brief Virtual function for creating the index.
     * \param fileName - a directory containing files to be put in the index.
     * \return boolean whether the index was successfully created.
     */
    
    virtual
    bool makeIndex(const std::string& fileName) = 0;
    
};

#endif /* INDEXINTERFACE_HPP */
