/*!
 * \file Token.hpp
 * \brief Contains the interface (and some inlined implementation) for Token objects.
 */

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cmath>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/*!
 * \class Token.
 * \brief Class for representing each token in the corpus.
 * \brief Also maintains information pertaining to the relationship between the token and its frequencies.
 * \see Document.
 * \see DocumentProcessor.
 */

class Token {

private:
    
    std::string _payload;                                   //!< \private A std::string to contain the token extracted from the corpus.
    std::unordered_map<int,std::pair<int,float>> _docFreqs; //!< \private A std::unordered_map for document/(document frequency/tf-idf) pairs.
    int corpusFreq;                                         //!< \private An integer for containing a Token's frequency in the corpus.
    
public:
    
    /*!
     * \fn Token().
     * \brief Initializes the member data with default values.
     */
    
    Token() : _payload(std::string()),
              _docFreqs(std::unordered_map<int,std::pair<int,float>>()),
              corpusFreq(0) {}
    
    /*!
     * \fn Token(const std::string& payload).
     * \brief Initializes the member data with a given payload and default values for the rest of the data members.
     * \param payload - a payload to initialize the Token with.
     */
    
    Token(const std::string& payload) : _payload(payload),
                                        _docFreqs(std::unordered_map<int,std::pair<int,float>>()),
                                        corpusFreq(0) {}
    
    /*!
     * \fn Token(std::string&& payload).
     * \brief Initializes the member data with a given payload and default values for the rest of the data members.
     * \param payload - an rvalue payload to initialize the Token with.
     */
    
    Token(std::string&& payload) : _payload(std::move(payload)),
                                   _docFreqs(std::unordered_map<int,std::pair<int,float>>()),
                                   corpusFreq(0) {}
    
    /*!
     * \fn add_doc_pair(const std::pair<int,int>& doc).
     * \brief Adds a new <document ID/<document frequency/tf-idf>> pair to the Token's internal container.
     * \param doc - a std::pair containing a document ID and a base frequency in the document.
     */
    
    inline
    void addDocPair(const std::pair<int,int>& doc) {
        
        _docFreqs[doc.first] = std::make_pair(doc.second,0.0f);
        
    }
    
    /*!
     * \fn calculateRanks(const int& numDocs).
     * \brief Calculates the tf-idf values for a Token for all documents that contain that Token.
     * \param numDocs - the number of documents in the corpus.
     */
    
    void calculateRanks(const int& numDocs);
    
    /*!
     * \fn corpus_frequency().
     * \brief Returns a Token's corpus frequency.
     * \return reference to the Token's corpus frequency.
     */
    
    inline
    int& corpusFrequency() { return corpusFreq; }
    
    /*!
     * \fn corpus_frequency(const int& corpFreq).
     * \brief Sets the corpus frequency to a given value.
     * \param corpFreq - a given value to set the Token's corpus frequency.
     */
    
    void corpusFrequency(const int& corpFreq) { corpusFreq = corpFreq; }
    
    /*!
     * \fn get_docs().
     * \brief Returns a std::unordered_map containing the Token's associated <document/<document frequency/tf-idf>> pairs.
     * \return reference to a std::unordered_map containing <document/<document frequency/tf-idf>> pairs.
     */
    
    inline
    std::unordered_map<int,std::pair<int,float>>& docFreqs() { return _docFreqs; }
    
    /*!
     * \fn docFreqs(const std::unordered_map<int,std::pair<int,float>>& docs).
     * \brief Sets docFreqs to a given value.
     * \param docs - a std::unordered_map containing <document/<document frequency/tf-idf>> pairs.
     */
    
    inline
    void docFreqs(const std::unordered_map<int,std::pair<int,float>>& docs) { _docFreqs = docs; }
    
    /*!
     * \fn has_doc_pair(const std::pair<int,int>& docID).
     * \brief Returns whether the Token already contains a document/document frequency pair.
     * \param docID - a std::pair containing the document ID to be searched for.
     * \return boolean whether the Token already contains a document ID.
     */
    
    bool hasDocPair(const std::pair<int,int>& docID) const;

    /*!
     * \fn incr_corp_freq().
     * \brief Increments the corpus frequency by 1.
     */
    
    void incrCorpFreq() { ++corpusFreq; }
    
    /*!
     * \fn incr_corp_freq(const int& corpFreq).
     * \brief Increments the corpus frequency by a given amount.
     * \param corpFreq - a given value to increment the Token's corpus frequency.
     */
    
    void incrCorpFreq(const int& corpFreq) { corpusFreq += corpFreq; }
    
    /*!
     * \fn incr_doc_freq(const std::pair<int,int>& docID).
     * \brief Increments the frequency of a Token in a given document by 1.
     * \param docID - a document ID for which to increment the associated Token frequency.
     */
    
    void incrDocPair(const std::pair<int,int>& docID);
    
    /*!
     * \fn payload().
     * \brief Returns a Token's payload.
     * \return reference to the Token's payload (std::string).
     */
    
    inline
    std::string& payload() { return _payload; }
    
    /*!
     * \fn payload(const std::string& payload).
     * \brief Sets the Token's payload.
     * \param payload - a string to set the Token payload to.
     */
    
    void payload(const std::string& payload) { _payload = payload; }
    
    /*!
     * \fn payload(std::string&& payload).
     * \brief Sets the Token's payload using an rvalue reference.
     * \param payload - a string to set the Token payload to.
     */
    
    void payload(std::string&& payload) { _payload = std::move(payload); }
    
    /*!
     * \fn operator== (const Token& lhs, const Token& rhs).
     * \brief Compares two Token objects for equality.
     * \param lhs - A constant Token reference.
     * \param rhs - A constant Token reference.
     * \return boolean whether two Tokens are the same.
     */
    
    friend inline
    bool operator== (const Token& lhs,
                     const Token& rhs) { return (lhs._payload == rhs._payload); }
    
    /*!
     * \fn operator!= (const Token& lhs, const Token& rhs).
     * \brief Compares two Token objects for inequality.
     * \param lhs - A constant Token reference.
     * \param rhs - A constant Token reference.
     * \return boolean whether two Tokens are not the same.
     */
    
    friend inline
    bool operator!= (const Token& lhs,
                     const Token& rhs) { return !(lhs == rhs); }
    
    /*!
     * \fn operator< (const Token& lhs, const Token& rhs).
     * \brief Returns whether one Token is less than another.
     * \param lhs - A constant Token reference.
     * \param rhs - A constant Token reference.
     * \return boolean whether a Token is less than another.
     */
    
    friend inline
    bool operator< (const Token& lhs,
                    const Token& rhs) { return (lhs._payload < rhs._payload); }
    
};

#endif /* TOKEN_HPP */
