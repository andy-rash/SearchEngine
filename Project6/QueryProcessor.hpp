/*!
 * \file QueryProcessor.hpp
 * \brief Contains the interface for QueryProcessor objects.
 */

#ifndef QUERYPROCESSOR_HPP
#define QUERYPROCESSOR_HPP

#include <algorithm>
#include <codecvt>
#include <locale>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Document.hpp"
#include "IndexInterface.hpp"
#include "AVLTreeIndex.hpp"
#include "HashTableIndex.hpp"

#include "./Resources/pugixml-1.7/src/pugixml.hpp"
#include "./Resources/Oleander/stemming/english_stem.h"

/*!
 * \class QueryProcessor.
 * \brief Class for parsing user queries and ranking results.
 * \see IndexInterface.
 */

class QueryProcessor {

private:
    
    typedef std::vector<std::pair<int,float>> set_type; //!< \typedef The basic set of doc ID / tf-idf pairs.
    
    int numDocs;                               //!< \private Number of documents processed; used in tf-idf calculations.
    stemming::english_stem<> StemEnglish;      //!< \private Oleander stemming object.
    std::unordered_set<std::string> stopWords; //!< \private std::unordered_set to contain the stop words.
    
    /*!
     * \fn difference(set_type& set, set_type& difference_set).
     * \brief Internal function. Finds the difference of two sets.
     * \param set - the return set; the set being subtracted from.
     * \param difference_set - the set being subtracted from the main set.
     */
    
    void difference(set_type& set,
                    set_type& difference_set);
    
    /*!
     * \fn intersect(std::vector<Token>& affirmative).
     * \brief Internal function. Finds the intersection of a given number of Tokens.
     * \param affirmative - a set of Tokens to find the intersection of.
     * \return set_type containing the intersection of affirmative's Tokens.
     */
    
    set_type
    intersect(std::vector<Token>& affirmative);
    
    /*!
     * \fn oleander(std::string& token).
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
    
    /*!
     * \fn unionize(std::vector<Token>& affirmative).
     * \brief Internal function. Finds the union of a given number of Tokens.
     * \param affirmative - a set of Tokens to find the union of.
     * \return set_type containing the union of affirmative's Tokens.
     */
    
    set_type
    unionize(std::vector<Token>& affirmative);
    
public:

    /*!
     * \fn QueryProcessor().
     * \brief Initializes the member data with default values.
     */
    
    QueryProcessor();
    
    /*!
     * \fn processTerms(std::vector<std::string>& terms, IndexInterface& indexer).
     * \brief parses the query based on boolean terms if any and returns a set of results if any.
     * \param terms - a std::vector containing the search terms to be processed.
     * \param indexer - an indexing object; one of either AVLTreeIndex or HashTableIndex.
     * \return a set_type containing the search results.
     */
    
    set_type
    processTerms(std::vector<std::string>& terms,
                 IndexInterface& indexer);
    
    /*!
     * \fn search(std::string& query, IndexInterface& indexer).
     * \brief Performs a search based on the given query; sends the tokenized query to processTerms(); also outputs the results.
     * \param query - a string to search the index for.
     * \param indexer - an indexing object; one of either AVLTreeIndex or HashTableIndex.
     */
    
    void search(std::string& query,
                IndexInterface& indexer);
    
    /*!
     * \fn setNumDocs(const IndexInterface& indexer).
     * \brief Sets the number of documents processed; for use in calculating tf-idf values.
     * \param indexer - an indexing object; one of either AVLTreeIndex or HashTableIndex.
     */
    
    void setNumDocs(const IndexInterface& indexer) { numDocs = indexer.getNumDocs(); }
    
};

#endif /* QUERYPROCESSOR_HPP */
