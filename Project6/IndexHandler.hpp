/*!
 * \file IndexHandler.hpp
 * \brief Contains the interface for IndexHandler objects.
 */

#ifndef INDEXHANDLER_HPP
#define INDEXHANDLER_HPP

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "AVLTree.hpp"
#include "Document.hpp"
#include "DocumentProcessor.hpp"
#include "Token.hpp"

#include "./Resources/pugixml-1.7/src/pugixml.hpp"
#include "./Resources/cereal/include/cereal/archives/binary.hpp"

/*!
 * \class IndexHandler.
 * \brief Reads and writes to the main index.
 * \brief Searches the index based on a request from the query processor.
 */

class IndexHandler {

private:
    
    DocumentProcessor docProc;                                             //!< \private DocumentProcessor object.
//    std::unordered_map<std::string,std::vector<std::pair<int,int>>> index; //!< \private hash table containing the index.
    std::ofstream outputFile;                                              //!< \private std::ofstream object for outputting the persistent index.
    AVLTree<Token> tokens;                                                 //!< \private AVL tree to contain the tokens (one form of the index).
    int numDocs;                                                           //!< \private Number of documents processed.
    int numTokens;                                                         //!< \private Number of tokens created.
    
public:
    
    /*!
     * \fn IndexHandler().
     * \brief Initializes the member data with default values.
     */
    
    IndexHandler() : numDocs(0),
                     numTokens(0) {}
    
    void addDocument(const std::string& path);
    
    /*!
     * \fn clearIndex().
     * \brief Completely clears the index, be it hash table or AVL tree.
     */
    
    void clearIndex();
    
    /*!
     * \fn emptyIndexAVL().
     * \brief Returns whether the index (AVL) is empty.
     * \return boolean whether the index is empty.
     */
    
    bool emptyIndexAVL();

    /*!
     * \fn emptyIndexHash().
     * \brief Returns whether the index (hash table) is empty.
     * \return boolean whether the index is empty.
     */
    
    /*
    bool emptyIndexHash();
    */
    
    /*!
     * \fn findWord(std::string& term).
     * \brief Finds a word in the index and returns a Token containing its document/document frequencies.
     * \param term - a single search term.
     * \return Token reference that matches the search term.
     */
    
    Token& findWord(std::string& term);
    
    const Document& getDocumentByID(const int& docID);
    
    /*!
     * \fn getNumDocs().
     * \brief Returns the number of documents processed.
     * \return integer representing the number of documents processed.
     */
    
    int getNumDocs() const;
    
    /*!
     * \fn getNumTokens().
     * \brief Returns the number of tokens created.
     * \return integer representing the number of tokens created.
     */
    
    int getNumTokens() const;
    
    /*!
     * \fn hasWord(std::string& term).
     * \brief Returns whether a word is contained within the index.
     * \param term - a single search term.
     * \return boolean whether the index contains the term.
     */
    
    bool hasWord(std::string& term);
    
    /*!
     * \fn listIndexAVL().
     * \brief Writes the index (AVL) to a persistent file.
     */
    
    void listIndexAVL();
    
    /*!
     * \fn listIndexHash().
     * \brief Writes the index (hash table) to a persistent file.
     */
    
    /*
    void listIndexHash();
    */
    
    /*!
     * \fn loadIndexAVL().
     * \brief Loads the index into an AVL tree from a persistent index file.
     * \return boolean whether the operation was successful.
     */
    
    bool loadIndexAVL();
    
    /*!
     * \fn loadIndexHash().
     * \brief Loads the index into a hash table from a persistent index file.
     * \return boolean whether the operation was successful.
     */
    
    /*
    bool loadIndexHash();
    */
    
    /*!
     * \fn makeIndexAVL(const std::string& fileName).
     * \brief Makes the index from files in a given directory.
     * \param fileName - a path to a directory containing files to be parsed.
     * \return boolean whether the operation was successful.
     */
    
    bool makeIndexAVL(const std::string& fileName);
    
    /*!
     * \fn makeIndexHash(const std::string& fileName).
     * \brief Makes the index from files in a given directory.
     * \param fileName - a path to a directory containing files to be parsed.
     * \return boolean whether the operation was successful.
     */
    
    /*
    bool makeIndexHash(const std::string& fileName);
    */
     
};

#endif /* INDEXHANDLER_HPP */
