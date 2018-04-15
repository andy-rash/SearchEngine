/*!
 * \file QueryProcessor.cpp
 * \brief Contains the implementation for QueryProcessor objects.
 */

#include "QueryProcessor.hpp"

QueryProcessor::QueryProcessor() : numDocs(0) {

    pugi::xml_document doc;
    
    // load stop words by default
    if(!(doc.load_file("./Resources/XML/stop-words.xml"))) {
        
        std::cerr << "Error loading stop-words.xml (QueryProcessor.cpp)!" << std::endl;
        
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

void QueryProcessor::difference(set_type& set,
                                set_type& difference_set) {
    
    typedef set_type::iterator iterator;
    
    iterator first1 = set.begin();
    iterator last1  = set.end();
    
    iterator first2 = difference_set.begin();
    iterator last2  = difference_set.end();
    
    while(first1 != last1 && first2 != last2) {
    
        if(first1->first < first2->first) { ++first1; }
        else if(first2->first < first1->first) { ++first2; }
        else {
        
            set.erase(first1);
            
            ++first2;
            
        }
        
    }
    
}

typename QueryProcessor::set_type
QueryProcessor::intersect(std::vector<Token>& affirmative) {

    std::unordered_map<int,std::pair<int,float>> tmp1;
    std::unordered_map<int,std::pair<int,float>> tmp2;
    
    set_type term1;
    set_type::iterator first1;
    set_type::iterator last1;
    
    set_type term2;
    set_type::iterator first2;
    set_type::iterator last2;
    
    set_type intersection;
    set_type::iterator result;
    
    for(std::vector<Token>::iterator it = affirmative.begin(); it != affirmative.end(); ++it) {
    
        tmp1 = it->docFreqs();
        
        for(auto& elem : tmp1) { term1.emplace_back(std::make_pair(elem.first,elem.second.second)); }
        
        if(++it != affirmative.end()) {
        
            tmp2 = it->docFreqs();
            
            for(auto& elem : tmp2) { term2.emplace_back(std::make_pair(elem.first,elem.second.second)); }
            
        } else {
            
            std::sort(term1.begin(),term1.end());
            std::sort(intersection.begin(),intersection.end());
            
            first1 = term1.begin();
            last1  = term1.end();
            first2 = intersection.begin();
            last2  = intersection.end();
            
            while(first1 != last1 && first2 != last2) {
                
                if(first1->first < first2->first) { ++first1; }
                else if(first2->first < first1->first) { ++first2; }
                else {
                    
                    first2->second += first1->second;
                    
                    ++first1;
                    ++first2;
                    
                }
                
            }
            
            break;
        
        }
        
        if(!term2.empty()) {
        
            if(intersection.empty()) {
            
                std::sort(term1.begin(),term1.end());
                std::sort(term2.begin(),term2.end());
                
                first1 = term1.begin();
                last1  = term1.end();
                first2 = term2.begin();
                last2  = term2.end();
                
                while(first1 != last1 && first2 != last2) {
                    
                    if(first1->first < first2->first) { ++first1; }
                    else if(first2->first < first1->first) { ++first2; }
                    else {
                        
                        intersection.push_back(*first1);
                        result = intersection.end() - 1;
                        result->second += first2->second;
                        
                        ++result;
                        ++first1;
                        ++first2;
                        
                    }
                    
                }
                
            } else {
            
                std::sort(term1.begin(),term1.end());
                std::sort(intersection.begin(),intersection.end());
                
                first1 = term1.begin();
                last1  = term1.end();
                first2 = intersection.begin();
                last2  = intersection.end();
                
                while(first1 != last1 && first2 != last2) {
                    
                    if(first1->first < first2->first) { ++first1; }
                    else if(first2->first < first1->first) { ++first2; }
                    else {
                        
                        first2->second += first1->second;
                        
                        ++first1;
                        ++first2;
                        
                    }
                    
                }
                
                std::sort(term2.begin(),term2.end());
                std::sort(intersection.begin(),intersection.end());
                
                first1 = term2.begin();
                last1  = term2.end();
                first2 = intersection.begin();
                last2  = intersection.end();
                
                while(first1 != last1 && first2 != last2) {
                    
                    if(first1->first < first2->first) { ++first1; }
                    else if(first2->first < first1->first) { ++first2; }
                    else {
                        
                        first2->second += first1->second;
                        
                        ++first1;
                        ++first2;
                        
                    }
                    
                }
                
            }
            
        } else {
        
            std::sort(term1.begin(),term1.end());
            std::sort(intersection.begin(),intersection.end());
            
            first1 = term1.begin();
            last1  = term1.end();
            first2 = intersection.begin();
            last2  = intersection.end();
            
            while(first1 != last1 && first2 != last2) {
                
                if(first1->first < first2->first) { ++first1; }
                else if(first2->first < first1->first) { ++first2; }
                else {
                    
                    first2->second += first1->second;

                    ++first1;
                    ++first2;
                    
                }
                
            }
            
        }
        
        tmp1.clear();
        tmp2.clear();
        term1.clear();
        term2.clear();
        
    }
    
    return intersection;
    
}

void QueryProcessor::oleander(std::string& token) {
    
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

typename QueryProcessor::set_type
QueryProcessor::processTerms(std::vector<std::string>& terms,
                             IndexInterface& indexer) {
    
    std::vector<Token> affirmative;
    std::vector<Token> notAffirmative;
    set_type results = set_type();
    
    for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) {
        
        if(*it == "NOT") {
            
            stem(*(++it));
            
            if(indexer.hasWord(*it)) {
                
                Token tok = indexer.findWord(*it);
                tok.calculateRanks(indexer.getNumDocs());
                
                notAffirmative.push_back(tok);
                
            }
            
        } else if(*it != "AND" && *it != "OR") {
            
            stem(*it);
            
            if(indexer.hasWord(*it)) {
                
                Token tok = indexer.findWord(*it);
                tok.calculateRanks(indexer.getNumDocs());
                
                affirmative.push_back(tok);
                
            }
            
        }
        
    }
    
    if(terms[0] == "AND") {
        
        results = intersect(affirmative);
        
    } else { // default to a union of all elements containing the search terms
        
        results = unionize(affirmative);
        
    }
    
    if(!notAffirmative.empty()) {
        
        // remove the NOT-ed documents from the results
        set_type difference_set = unionize(notAffirmative);
        
        difference(results,difference_set);
        
    }
    
    std::sort(results.begin(),results.end(),
              [](const std::pair<int,float>& lhs,
                 const std::pair<int,float>& rhs) { return rhs.second < lhs.second; } );
    
    return results;
    
}

void QueryProcessor::search(std::string& query,
                            IndexInterface& indexer) {
    
    std::stringstream ss(query);
    std::vector<std::string> terms;
    std::string tmp;
    
    while(getline(ss,tmp,' ')) {
        
        if(stopWords.count(tmp) == 0) { terms.push_back(tmp); }
        
        tmp = "";
        
    }
    
    set_type results = processTerms(terms,indexer);
    
    if(results.empty()) {
        
        std::cout << std::endl;
        std::cout << "Search returned no results." << std::endl;
        std::cout << std::endl;
        
    } else {
        
        if(results.size() >= 15) {
            
            for(set_type::iterator it = results.begin(); it != results.begin()+15; ++it) {
                
                Document tmp = indexer.getDocumentByID(it->first);
                
                std::cout << std::endl;
                std::cout << "Document ID# " << it->first << std::endl;
                std::cout << tmp.title() << std::endl;
                std::cout << "Contributor: " << tmp.username() << " Date: " << tmp.date() << std::endl;
                std::cout << "tf-idf: " << it->second << std::endl;
                std::cout << std::endl;
                
            }
            
        } else {
            
            for(set_type::iterator it = results.begin(); it != results.end(); ++it) {
                
                Document tmp = indexer.getDocumentByID(it->first);
                
                std::cout << std::endl;
                std::cout << "Document ID# " << it->first << std::endl;
                std::cout << tmp.title() << std::endl;
                std::cout << "Contributor: " << tmp.username() << " Date: " << tmp.date() << std::endl;
                std::cout << "tf-idf: " << it->second << std::endl;
                std::cout << std::endl;
                
            }
            
        }
        
    }
    
}

void QueryProcessor::stem(std::string& token) {
    
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

typename QueryProcessor::set_type
QueryProcessor::unionize(std::vector<Token>& affirmative) {

    std::unordered_map<int,std::pair<int,float>> tmp1;
    std::unordered_map<int,std::pair<int,float>> tmp2;
    
    set_type term1;
    set_type::iterator first1;
    set_type::iterator last1;
    
    set_type term2;
    set_type::iterator first2;
    set_type::iterator last2;
    
    set_type unionization;
    set_type::iterator result;
    
    for(std::vector<Token>::iterator it = affirmative.begin(); it != affirmative.end(); ++it) {
    
        tmp1 = it->docFreqs();
        
        for(auto& elem : tmp1) { term1.emplace_back(std::make_pair(elem.first,elem.second.second)); }
        
        if(++it != affirmative.end()) {
        
            tmp2 = it->docFreqs();
            
            for(auto& elem : tmp2) { term2.emplace_back(std::make_pair(elem.first,elem.second.second)); }
            
        } else {
            
            std::sort(term1.begin(),term1.end());
            std::sort(unionization.begin(),unionization.end());
            
            first1 = term1.begin();
            last1  = term1.end();
            first2 = unionization.begin();
            last2  = unionization.end();
            
            if(unionization.empty()) { for(auto& elem : term1) { unionization.push_back(elem); } }
            
            while(first1 != last1 && first2 != last2) {
                
                if(first2 == last2) { std::copy(first1,last1,first2); break; }
                
                if(first2->first < first1->first) { unionization.push_back(*first2); ++first2; }
                else if(first1->first < first2->first) { unionization.push_back(*first1); ++first1; }
                else {
                    
                    first2->second += first1->second;
                    
                    ++first1;
                    ++first2;
                    
                }
                
            }
            
            break;
        
        }
        
        if(!term2.empty()) {
        
            std::sort(term1.begin(),term1.end());
            std::sort(term2.begin(),term2.end());
            
            first1 = term1.begin();
            last1  = term1.end();
            first2 = term2.begin();
            last2  = term2.end();
            
            while(first1 != last1 && first2 != last2) {
            
                if(first2 == last2) { std::copy(first1,last1,result); break; }
                
                if(first2->first < first1->first) { unionization.push_back(*first2); ++first2; }
                else if(first1->first < first2->first) { unionization.push_back(*first1); ++first1; }
                else {
                
                    unionization.push_back(*first1);
                    
                    result = unionization.end() - 1;
                    result->second += first2->second;
                    
                    ++first1;
                    ++first2;
                    
                }
                
            }
            
        } else {
        
            std::sort(term1.begin(),term1.end());
            std::sort(unionization.begin(),unionization.end());
            
            first1 = term1.begin();
            last1  = term1.end();
            first2 = unionization.begin();
            last2  = unionization.end();
            
            if(unionization.empty()) { for(auto& elem : term1) { unionization.push_back(elem); } }
            
            while(first1 != last1 && first2 != last2) {
                
                if(first2 == last2) { std::copy(first1,last1,first2); break; }
                
                if(first2->first < first1->first) { unionization.push_back(*first2); ++first2; }
                else if(first1->first < first2->first) { unionization.push_back(*first1); ++first1; }
                else {
                    
                    first2->second += first1->second;
                    
                    ++first1;
                    ++first2;
                    
                }
                
            }
            
        }
        
        tmp1.clear();
        tmp2.clear();
        term1.clear();
        term2.clear();
        
    }

    return unionization;
    
}
