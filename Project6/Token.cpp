/*!
 * \file Token.cpp
 * \brief Contains some of the implementation for Token objects.
 */

#include "Token.hpp"

void Token::calculateRanks(const int& numDocs) {

    auto d = (_docFreqs.size() > 0) ? _docFreqs.size() : 1;
    
    for(auto& elem : _docFreqs) {
    
        auto idf = log10f((float)numDocs / (float) d);
        
        int tf = elem.second.first;
        
        elem.second.second = tf * idf;
    
    }
    
}

bool Token::hasDocPair(const std::pair<int,int>& docID) const {
    
    std::unordered_map<int,std::pair<int,float>>::const_iterator itr = _docFreqs.find(docID.first);
    
    return (itr != _docFreqs.end());
    
}

void Token::incrDocPair(const std::pair<int,int>& docID) {
    
    std::unordered_map<int,std::pair<int,float>>::iterator itr = _docFreqs.find(docID.first);
    
    if(itr != _docFreqs.end()) { ++(itr->second.first); }
    
}
