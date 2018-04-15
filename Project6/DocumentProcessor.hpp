/*!
 * \file DocumentProcessor.hpp
 * \brief Contains the interface for DocumentProcessor objects.
 */

#ifndef DOCUMENTPROCESSOR_HPP
#define DOCUMENTPROCESSOR_HPP

#include <algorithm>
#include <codecvt>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

#include <sys/types.h>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "AVLTree.hpp"
#include "Document.hpp"
#include "Token.hpp"

#include "./Resources/pugixml-1.7/src/pugixml.hpp"
#include "./Resources/Oleander/stemming/english_stem.h"

/*!
 * \class DocumentProcessor.
 * \brief Processes each document from the corpus.
 * \brief Stems and removes stop words.
 * \brief Computes term frequencies (information stored in Token objects)
 * \see Document.
 * \see Token.
 */

class DocumentProcessor {

private:
    
    typedef std::size_t size_type;                                                                   //!< \typedef size_type based on std::size_t.
    typedef std::unordered_map<std::string,std::unordered_map<int,std::pair<int,float>>> index_type; //!< \typedef The base type of the hash table index.
    
    pugi::xml_document doc;                    //!< \private Pugi XML document object.
    stemming::english_stem<> StemEnglish;      //!< \private Oleander stemming object.
    std::string body;                          //!< \private Temporary string to hold the body text of a document.
    std::string date;                          //!< \private Temporary string to hold the date of a document.
    std::string time;                          //!< \private Temporary string to hold the time of a document.
    std::string title;                         //!< \private Temporary string to hold the title of a document.
    std::string username;                      //!< \private Temporary string to hold the username of a document's contributor.
    int id;                                    //!< \private Temporary integer to hold the ID of a document.
    
    int numDocs;                               //!< \private integer for containing the number of documents processed.
    std::unordered_set<std::string> stopWords; //!< \private std::unordered_set to contain the stop words.
    std::unordered_set<Document> documents;    //!< \private std::unordered_set to contain Documents for later lookup.
    
    /*!
     * \fn getDir(const std::string& dir, std::vector<std::string>& rhs).
     * \brief Internal function. Returns the contents of a given directory.
     * \param dir - a string to get the directory listing from.
     * \param ls - a std::vector that contains the directory listing after the function completes.
     */
    
    void getDir(const std::string& dir,
                std::vector<std::string>& ls);
    
    /*!
     * \fn oleander(std::string& token.
     * \brief Internal function. Stems a given word using the Oleander library.
     * \param token - a token to be stemmed (using the library).
     */
    
    void oleander(std::string& token);
    
    /*!
     * \fn stem(std::string& token).
     * \brief Internal function. Processes a given token (stems, removes certain characters, transforms to lower case).
     * \param token - a token to be processed.
     */
    
    void stem(std::string& token);
    
public:
    
    /*!
     * \fn DocumentProcessor().
     * \brief Loads the stopwords into the std::unordered_set by default.
     */
    
    DocumentProcessor();
    
    /*!
     * \fn addDocument(const std::string& fileName, AVLTree<Token>& tokens).
     * \brief Adds a document to the set of documents.
     * \param fileName - a string representing the path to the file to parse.
     * \param tokens - an AVL tree that holds the resulting tokens.
     * \return boolean whether the document was added successfully.
     */
    
    bool addDocument(const std::string& fileName,
                     AVLTree<Token>& tokens);
    
    /*!
     * \fn addDocument(const std::string& fileName, index_type& index).
     * \brief Adds a document to the set of documents.
     * \param fileName - a string representing the path to the file to parse.
     * \param index - an index object that holds the resulting data.
     * \return boolean whether the document was added successfully.
     */
    
    bool addDocument(const std::string& fileName,
                     index_type& index);
    
    /*!
     * \fn batchTokenize(const std::string& path,AVLTree<Token>& tokens).
     * \brief Parses the XML file(s), tokenizes the pages, and adds each Token to the AVL tree.
     * \param path - a path to the directory containing the file(s).
     * \param tokens - an AVL tree that holds the resulting tokens.
     * \return boolean whether the process was successful.
     */
    
    bool batchTokenize(const std::string& fileName,
                       AVLTree<Token>& tokens);
    
    /*!
     * \fn batchTokenize(const std::string& path,index_type& index).
     * \brief Parses the XML file(s), tokenizes the pages, and adds each token to the index.
     * \param path - a path to the directory containing the file(s).
     * \param index - an index object that holds the resulting data
     * \return boolean whether the process was successful.
     */
    
    bool batchTokenize(const std::string& fileName,
                       index_type& index);
    
    /*!
     * \fn clear().
     * \brief Clears the contents of the set of documents.
     */
    
    void clear();
    
    /*!
     * \fn crateDocuments(const std::string& fileName).
     * \brief Creates a set of Documents from the documents contained in a given directory.
     * \param fileName - a std::string containing the path to the file.
     * \return boolean whether the set of documents was successfully created.
     */
    
    bool createDocuments(const std::string& fileName);
    
    /*!
     * \fn documentsSize().
     * \brief Returns the number of documents processed.
     * \return integer representing the number of documents processed.
     */
    
    int documentsSize() const;
    
    /*!
     * \fn getDocuments().
     * \brief Returns the set of Documents.
     * \return std::unordered_set containing the documents.
     */
    
    std::unordered_set<Document>&
    getDocuments();
    
    /*!
     * \fn getDocumentByID(const int& docID).
     * \brief Returns a specific document out of the set pertaining to a specific ID number.
     * \return const Document reference pertaining to the given ID number.
     */
    
    const Document& getDocumentByID(const int& docID);
    
    /*!
     * \fn tokenize(Document& doc, AVLTree<Token>& tokens).
     * \brief Tokenizes a given Document and adds the Tokens to the given AVL tree.
     * \param doc - a document to tokenize.
     * \param tokens - an AVL tree that holds the resulting tokens.
     */
    
    void tokenize(Document& doc,
                  AVLTree<Token>& tokens);
    
    /*!
     * \fn tokenize(Document& doc, index_type& tokens).
     * \brief Tokenizes a given Document and adds the tokens to the index.
     * \param doc - a document to tokenize.
     * \param index - an index object that holds the resulting data.
     */
    
    void tokenize(Document& doc,
                  index_type& index);
    
};

#endif /* DOCUMENTPROCESSOR_HPP */
