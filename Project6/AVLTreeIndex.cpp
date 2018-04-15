/*!
 * \file AVLTreeIndex.cpp
 * \brief Contains the implementation for AVLTreeIndex objects.
 */

#include "AVLTreeIndex.hpp"

AVLTreeIndex::AVLTreeIndex() {}

AVLTreeIndex::~AVLTreeIndex() { tokens.clear(); }

void AVLTreeIndex::addDocument(const std::string& path) {

    docProc.addDocument(path,tokens);
    
    numDocs = docProc.documentsSize();
    numTokens = (int)tokens.size();
    
}

void AVLTreeIndex::clearIndex() {

    tokens.clear();
    docProc.clear();
    
    numDocs = 0;
    numTokens = 0;
    
}

bool AVLTreeIndex::emptyIndex() const { return tokens.empty(); }

Token AVLTreeIndex::findWord(std::string& term) {

    Token tok;
    tok.payload(term);
    
    return *(tokens.find(tok));
    
}

const Document& AVLTreeIndex::getDocumentByID(const int& docID) { return docProc.getDocumentByID(docID); }

bool AVLTreeIndex::hasWord(std::string& term) {

    Token tok;
    tok.payload(term);
    
    return (tokens.find(tok) != tokens.end());
    
}

void AVLTreeIndex::listIndex() {

    outputFile.open("./Output/index.xml");
    
    if(outputFile.is_open()) {
        
        outputFile << "<document>" << std::endl;
        
        outputFile << "     <processed>" << numDocs << "</processed>" << std::endl;
        
        for(AVLTree<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
            
            outputFile << "     <term Term=\"" << it->payload() << "\">" << std::endl;
            
            for(auto& id : it->docFreqs()) {
                
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

bool AVLTreeIndex::loadIndex() {

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
                
                Token tok;
                tok.payload(std::string(itr->attribute("Term").value()));
                
                childItr = itr->child("id");
                
                for(childItr = itr->begin(); childItr != itr->end(); ++childItr) {
                    
                    tok.addDocPair(std::make_pair(std::stoi(std::string(childItr->attribute("ID").value())),
                                                  std::stoi(std::string(childItr->child("frequency").text().get()))));
                    
                    tok.incrCorpFreq(1);
                    
                }
                
                tokens.insert(tok);
                
            }
            
        }
        
        numTokens = (int)tokens.size();
        
        return true;
        
    }
    
    return false;

}

bool AVLTreeIndex::makeIndex(const std::string& fileName) {

    if(docProc.batchTokenize(fileName,tokens)) {
        
        numDocs = docProc.documentsSize();
        numTokens = (int)tokens.size();
        
        return true;
        
    }
    
    return false;

}
