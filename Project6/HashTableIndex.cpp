/*!
 * \file HashTableIndex.cpp
 * \brief Contains the implementation for HashTableIndex objects.
 */

#include "HashTableIndex.hpp"

HashTableIndex::HashTableIndex() {}

HashTableIndex::~HashTableIndex() { index.clear(); }

void HashTableIndex::addDocument(const std::string& path) {

    docProc.addDocument(path,index);
    
    numDocs = docProc.documentsSize();
    numTokens = (int)index.size();
    
}

void HashTableIndex::clearIndex() {

    index.clear();
    docProc.clear();
    
    numDocs = 0;
    numTokens = 0;
    
}

bool HashTableIndex::emptyIndex() const { return index.empty(); }

Token HashTableIndex::findWord(std::string& term) {

    index_type::iterator it = index.find(term);
    
    Token tok;
    tok.payload(it->first);
    tok.docFreqs(it->second);
    tok.corpusFrequency((int)it->second.size());
    
    return tok;

}

const Document& HashTableIndex::getDocumentByID(const int& docID) { return docProc.getDocumentByID(docID); }

bool HashTableIndex::hasWord(std::string& term) { return (index.find(term) != index.end()); }

void HashTableIndex::listIndex() {

    outputFile.open("./Output/index.xml");
    
    if(outputFile.is_open()) {
        
        outputFile << "<document>" << std::endl;
        
        outputFile << "     <processed>" << numDocs << "</processed>" << std::endl;
        
        for(auto it = index.begin(); it != index.end(); ++it) {
            
            outputFile << "     <term Term=\"" << it->first << "\">" << std::endl;
            
            for(auto& id : it->second) {
                
                outputFile << "         <id ID=\"" << id.first << "\">" << std::endl;
                outputFile << "                 <frequency>" << id.second.first << "</frequency>" << std::endl;
                outputFile << "         </id>" << std::endl;
                
            }
            
            outputFile << "     </term>" << std::endl;
            
        }
        
        outputFile << "</document>" << std::endl;
        
    }
    
    outputFile.close();

}

bool HashTableIndex::loadIndex() {
    
    pugi::xml_document doc;
    
    if(!(doc.load_file("./Output/index.xml"))) {
        
        std::cerr << "Error loading index file!" << std::endl;
        return false;
        
    } else {
        
        clearIndex();
        
        pugi::xml_node document = doc.child("document");
        pugi::xml_node_iterator itr;
        pugi::xml_node_iterator childItr;
        
        if(strcmp("processed",document.child("processed").name()) == 0) {
            
            numDocs = std::stoi(std::string(document.child("processed").text().get()));
            
        }
        
        for(itr = document.begin(); itr != document.end(); ++itr) {
            
            
            if(strcmp("term",itr->name()) == 0) {
                
                // get iterator to "id" tag
                childItr = itr->child("id");
                
                // make map of <docID / <freq / tf-idf> > values
                std::unordered_map<int,std::pair<int,float>> tmp;
                for(childItr = itr->begin(); childItr != itr->end(); ++childItr) {
                
                    tmp[std::stoi(std::string(childItr->attribute("ID").value()))] = std::make_pair(
                                                                                     std::stoi(
                                                                                     std::string(childItr->child("frequency").text().get())),0.0f);
                    
                }
                
                // insert in the index with the term itself as the key
                index.insert(std::make_pair(std::string(itr->attribute("Term").value()),tmp));
                
            }
            
        }
        
        numTokens = (int)index.size();
        
        return true;
        
    }
    
    return false;
    
}

bool HashTableIndex::makeIndex(const std::string& fileName) {

    if(docProc.batchTokenize(fileName,index)) {
        
        numDocs = docProc.documentsSize();
        numTokens = (int)index.size();
        
        return true;
        
    }
    
    return false;

}
