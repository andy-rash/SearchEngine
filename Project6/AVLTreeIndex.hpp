/*!
 * \file AVLTreeIndex.hpp
 * \brief Contains the interface for AVLTreeIndex objects.
 */

#ifndef AVLTREEINDEX_HPP
#define AVLTREEINDEX_HPP

#include "AVLTree.hpp"
#include "IndexInterface.hpp"
#include "Token.hpp"

/*!
 * \class AVLTreeIndex.
 * \brief Class for dealing with the index in AVL tree form.
 * \see HashTableIndex.
 * \see IndexInterface.
 */

class AVLTreeIndex : public IndexInterface {
    
private:
    
    AVLTree<Token> tokens; //!< \private An AVL tree to contain Tokens, representing the index.
    
public:
    
    /*!
     * \fn AVLTreeIndex().
     * \brief Initializes the member data with default values.
     */
    
    AVLTreeIndex();
    
    /*!
     * \fn ~AVLTreeIndex().
     * \brief Destructor for proper memory management.
     */
    
    ~AVLTreeIndex();
    
    /*!
     * \fn addDocument(const std::string& path).
     * \brief Function for adding a document.
     * \param path - a path to a file to add to the index.
     */
    
    void addDocument(const std::string& path);
    
    /*!
     * \fn clearIndex().
     * \brief Function for clearing the index.
     */
    
    void clearIndex();
    
    /*!
     * \fn emptyIndex().
     * \brief Function for returning whether the index is empty.
     * \return boolean whether the index is empty.
     */
    
    bool emptyIndex() const;
    
    /*!
     * \fn findWord(std::string& term).
     * \brief Function for finding a word in the index.
     * \param term - term to search for in the index.
     * \return Token (by value for HashTableIndex compatibility) representing the searched word.
     */
    
    Token findWord(std::string& term);
    
    /*!
     * \fn getDocumentByID(const int& docID).
     * \brief Function for getting a document pertaining to a given ID number.
     * \param docID - a document ID number.
     * \return Document reference.
     */
    
    const Document& getDocumentByID(const int& docID);
    
    /*!
     * \fn hasWord(std::string& term).
     * \brief Function for returning whether the index contains a given word.
     * \param term - a term to search the index for.
     * \return boolean whether the index contains the word.
     */
    
    bool hasWord(std::string& term);
    
    /*!
     * \fn listIndex().
     * \brief Function for writing the persistent index.
     */
    
    void listIndex();
    
    /*!
     * \fn loadIndex().
     * \brief Function for loading an index in from persistent state.
     * \return boolean whether the index was successfully loaded.
     */
    
    bool loadIndex();

    /*!
     * \fn makeIndex(const std::string& fileName).
     * \brief Function for creating the index.
     * \param fileName - a directory containing files to be put in the index.
     * \return boolean whether the index was successfully created.
     */
    
    bool makeIndex(const std::string& fileName);
    
};

#endif /* AVLTREEINDEX_HPP */
