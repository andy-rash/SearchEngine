/*!
 * \file DocumentProcessor.cpp
 * \brief Contains the implmentation for DocumentProcessor objects.
 */

#include "DocumentProcessor.hpp"

DocumentProcessor::DocumentProcessor() {

    // load stop words by default
    if(!(doc.load_file("./Resources/XML/stop-words.xml"))) {
        
        std::cerr << "Error loading stop-words.xml (DocumentProcessor.cpp)!" << std::endl;
        
    } else {
        
        pugi::xml_node document = doc.child("document");
        pugi::xml_node_iterator itr;
        
        for(itr = document.begin(); itr != document.end(); ++itr) {
            
            if(strcmp("word",itr->name()) == 0) {
                
                stopWords.insert(itr->text().get());
                
            }
            
        }
        
    }
    
}

bool DocumentProcessor::addDocument(const std::string& fileName,
                                    AVLTree<Token>& tokens) {

    if(!(doc.load_file(fileName.c_str()))) {
        
        std::cerr << "Error loading file to be indexed!" << std::endl;
        return false;
        
    } else {
        
        pugi::xml_node dump = doc.child("mediawiki");
        pugi::xml_node_iterator itr;
        std::stringstream ss;
        
        for(itr = dump.begin(); itr != dump.end(); ++itr) {
            
            if(strcmp("page",itr->name()) == 0) {
                
                title = itr->child("title").text().get();
                body = itr->child("revision").child("text").text().get();
                id = std::stoi(itr->child("id").text().get());
                
                if(itr->child("revision").child("contributor").child("ip")) {
                    
                    username = itr->child("revision").child("contributor").child("ip").text().get();
                    
                } else if(itr->child("revision").child("contributor").child("username")) {
                    
                    username = itr->child("revision").child("contributor").child("username").text().get();
                    
                }
                
                std::string tmp = itr->child("revision").child("timestamp").text().get();
                ss.str(tmp);
                tmp = ss.str();
                getline(ss,date,'T');
                getline(ss,time,'Z');
                
                Document page(body,date,time,title,username,id);
                
                documents.insert(page);
                ++numDocs;
                
                tokenize(page, tokens);
                
                body = "";
                date = "";
                time = "";
                title = "";
                tmp = "";
                username = "";
                id = 0;
                ss.str(std::string());
                
            }
            
        }
        
    }
    
    return true;
    
}

bool DocumentProcessor::addDocument(const std::string& fileName,
                                    index_type& index) {

    if(!(doc.load_file(fileName.c_str()))) {
        
        std::cerr << "Error loading file to be indexed!" << std::endl;
        return false;
        
    } else {
        
        pugi::xml_node dump = doc.child("mediawiki");
        pugi::xml_node_iterator itr;
        std::stringstream ss;
        
        for(itr = dump.begin(); itr != dump.end(); ++itr) {
            
            if(strcmp("page",itr->name()) == 0) {
                
                title = itr->child("title").text().get();
                body = itr->child("revision").child("text").text().get();
                id = std::stoi(itr->child("id").text().get());
                
                if(itr->child("revision").child("contributor").child("ip")) {
                    
                    username = itr->child("revision").child("contributor").child("ip").text().get();
                    
                } else if(itr->child("revision").child("contributor").child("username")) {
                    
                    username = itr->child("revision").child("contributor").child("username").text().get();
                    
                }
                
                std::string tmp = itr->child("revision").child("timestamp").text().get();
                ss.str(tmp);
                tmp = ss.str();
                getline(ss,date,'T');
                getline(ss,time,'Z');
                
                Document page(body,date,time,title,username,id);
                
                documents.insert(page);
                ++numDocs;
                
                tokenize(page,index);
                
                body = "";
                date = "";
                time = "";
                title = "";
                tmp = "";
                username = "";
                id = 0;
                ss.str(std::string());
                
            }
            
        }
        
    }
    
    return true;
    
}

bool DocumentProcessor::batchTokenize(const std::string& fileName,
                                      AVLTree<Token>& tokens) {

    std::vector<std::string> directory;
    getDir(fileName,directory);
    std::string pathName = fileName;
    bool added = false;
    
    for(auto& str : directory) {
    
        pathName += '/' + str;
        
        added = addDocument(pathName,tokens);
        
        pathName = fileName;
        
        if(added == false) { return added; }
        
    }
    
    return added;
    
}

bool DocumentProcessor::batchTokenize(const std::string& fileName,
                                      index_type& index) {

    std::vector<std::string> directory;
    getDir(fileName,directory);
    std::string pathName = fileName;
    bool added = false;
    
    for(auto& str : directory) {
        
        pathName += '/' + str;
        
        added = addDocument(pathName,index);
        
        pathName = fileName;
        
        if(added == false) { return added; }
        
    }
    
    return added;
    
}

bool DocumentProcessor::createDocuments(const std::string& fileName) {
    
    if(documents.empty()) {
    
        std::vector<std::string> directory;
        getDir(fileName,directory);
        std::string pathName = fileName;
        bool added = false;
        
        for(auto& str : directory) {
            
            pathName += '/' + str;
            
            
            if(!(doc.load_file(pathName.c_str()))) {
                
                std::cerr << "Error loading file to be indexed!" << std::endl;
                added = false;
                
            } else {
                
                pugi::xml_node dump = doc.child("mediawiki");
                pugi::xml_node_iterator itr;
                std::stringstream ss;
                
                for(itr = dump.begin(); itr != dump.end(); ++itr) {
                    
                    if(strcmp("page",itr->name()) == 0) {
                        
                        title = itr->child("title").text().get();
                        body = itr->child("revision").child("text").text().get();
                        id = std::stoi(itr->child("id").text().get());
                        
                        if(itr->child("revision").child("contributor").child("ip")) {
                            
                            username = itr->child("revision").child("contributor").child("ip").text().get();
                            
                        } else if(itr->child("revision").child("contributor").child("username")) {
                            
                            username = itr->child("revision").child("contributor").child("username").text().get();
                            
                        }
                        
                        std::string tmp = itr->child("revision").child("timestamp").text().get();
                        ss.str(tmp);
                        tmp = ss.str();
                        getline(ss,date,'T');
                        getline(ss,time,'Z');
                        
                        Document page(body,date,time,title,username,id);
                        
                        documents.insert(page);
                        
                        body = "";
                        date = "";
                        time = "";
                        title = "";
                        tmp = "";
                        username = "";
                        id = 0;
                        ss.str(std::string());
                        
                    }
                    
                }
                
            }
            
            pathName = fileName;
            
        }
        
        return added;
        
    }
    
    return false;
    
}

void DocumentProcessor::clear() { documents.clear(); numDocs = 0; }

int DocumentProcessor::documentsSize() const { return numDocs; }

void DocumentProcessor::getDir(const std::string& dir,
                               std::vector<std::string>& ls) {

    DIR* dp;
    struct dirent* dirp;
    
    if((dp = opendir(dir.c_str())) == nullptr) {
    
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        
    }
    
    while((dirp = readdir(dp)) != nullptr) {
        
        if(dirp->d_name[0] != '.') { ls.push_back(std::string(dirp->d_name)); }
        
    }
    
    closedir(dp);
    
}

std::unordered_set<Document>&
DocumentProcessor::getDocuments() { return documents; }

const Document& DocumentProcessor::getDocumentByID(const int& docID) {

    Document tmp;
    tmp.id(docID);
    
    if(documents.empty()) { createDocuments("./Resources/XML/res/main-split"); }
    
    std::unordered_set<Document>::const_iterator it = documents.find(tmp);
    
    return *it;
    
}

void DocumentProcessor::oleander(std::string& token) {
    
    wchar_t* UnicodeTextBuffer = new wchar_t[token.length()+1];
    
    std::wmemset(UnicodeTextBuffer,0,token.length()+1);
    
    std::mbstowcs(UnicodeTextBuffer,token.c_str(),token.length());
    
    std::wstring wString = UnicodeTextBuffer;
    
    StemEnglish(wString);
    
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    
    delete[] UnicodeTextBuffer;
    UnicodeTextBuffer = nullptr;
    
    token = converterX.to_bytes(wString);
    
}

void DocumentProcessor::stem(std::string& token) {

    token.erase(std::remove(token.begin(),token.end(),'\n'),token.end());
    token.erase(std::remove(token.begin(),token.end(),'\t'),token.end());
    token.erase(std::remove(token.begin(),token.end(),'\''),token.end());
    token.erase(std::remove(token.begin(),token.end(),'\"'),token.end());
    token.erase(std::remove(token.begin(),token.end(),'\\'),token.end());
    token.erase(std::remove(token.begin(),token.end(),'<'),token.end());
    token.erase(std::remove(token.begin(),token.end(),'>'),token.end());
    
    std::transform(token.begin(),token.end(),token.begin(),::tolower);
  
    oleander(token);
    
}

void DocumentProcessor::tokenize(Document& doc,
                                 AVLTree<Token>& tokens) {

    std::string tmp = "";
    
    std::stringstream ss(doc.title() + " " + doc.username() + " " + doc.body());
    while(getline(ss,tmp,' ')) {
        
        if(stopWords.count(tmp) == 0) {
            
            DocumentProcessor::stem(tmp);
            
            Token tok;
            tok.payload(tmp);
            
            tok.addDocPair(std::make_pair(doc.id(),1));
            tok.incrCorpFreq();
            
            AVLTree<Token>::iterator it = tokens.find(tok);
            
            if(it != tokens.end() && !(tok < *tokens.begin())) {
                
                if(*it != tok) { tokens.insert(tok); }
                
                if(it->hasDocPair(std::make_pair(doc.id(),1))) {
                    
                    it->incrDocPair(std::make_pair(doc.id(),1));
                    
                } else {
                    
                    it->addDocPair(std::make_pair(doc.id(),1));
                    it->incrCorpFreq();
                    
                }
                
            } else { tokens.insert(tok); }
            
        }
        
        tmp = "";
        
    }
    
    tmp = "";
    ss.str(std::string());
    
}

void DocumentProcessor::tokenize(Document& doc,
                                 index_type& index) {

    std::string tmp = "";
    
    std::stringstream ss(doc.title() + " " + doc.username() + " " + doc.body());
    while(getline(ss,tmp,' ')) {
        
        if(stopWords.count(tmp) == 0) {
            
            DocumentProcessor::stem(tmp);
            
            index_type::iterator it = index.find(tmp);
            
            if(it != index.end()) {
            
                if(it->second.find(doc.id()) != it->second.end()) {
                
                    // get and store the current std::pair<doc ID / std::pair<frequency / tf-idf> >
                    // iterate the frequency
                    // delete the pair from it->second
                    // insert a new pair
                    
                    // get
                    std::unordered_map<int,std::pair<int,float>>::iterator itr = it->second.find(doc.id());
                    
                    // store
                    std::pair<int,std::pair<int,float>> temp = std::make_pair(itr->first,itr->second);
                    
                    // iterate
                    temp.second.first++;
                    
                    // delete
                    it->second.erase(itr);
                    
                    // insert
                    it->second.insert(temp);
                    
                } else {
                
                    // insert a new pair of <doc ID / <1,0.0f>> into it->second
                    
                    it->second.insert(std::make_pair(doc.id(),std::make_pair(1,0.0f)));
                    
                }
                
            } else {
            
                // std::unordered_map<std::string,std::unordered_map<int,std::pair<int,float>>>
                //
                // - std::string = tmp
                // - int #1      = docID
                // - int #2      = frequency of term in document
                // - float       = tf-idf
                
                std::unordered_map<int,std::pair<int,float>> tmpMap;
                
                tmpMap.insert( std::make_pair( doc.id(),std::make_pair(1,0.0f) ) );
                
                index.insert(std::make_pair(tmp,tmpMap));
                
            }
            
//            Token tok;
//            tok.payload(tmp);
//            
//            tok.addDocPair(std::make_pair(doc.id(),1));
//            tok.incrCorpFreq();
//            
//            AVLTree<Token>::iterator it = tokens.find(tok);
//            
//            if(it != tokens.end() && !(tok < *tokens.begin())) {
//                
//                if(*it != tok) { tokens.insert(tok); }
//                
//                if(it->hasDocPair(std::make_pair(doc.id(),1))) {
//                    
//                    it->incrDocPair(std::make_pair(doc.id(),1));
//                    
//                } else {
//                    
//                    it->addDocPair(std::make_pair(doc.id(),1));
//                    it->incrCorpFreq();
//                    
//                }
//                
//            } else { tokens.insert(tok); }
            
        }
        
        tmp = "";
        
    }
    
    tmp = "";
    ss.str(std::string());
    
}
