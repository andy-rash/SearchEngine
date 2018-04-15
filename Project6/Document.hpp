/*!
 * \file Document.hpp
 * \brief Contains the interface and inlined implementation for Document objects.
 */

#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <functional>
#include <string>

/*!
 * \class Document.
 * \brief Class for holding the information contained in a single page from WikiBooks.
 * \see DocumentProcessor.
 */

class Document {

private:
    
    std::string _body;     //!< \private A std::string to contain the body text.
    std::string _date;     //!< \private A std::string to contain the date a document was added to the corpus.
    std::string _time;     //!< \private A std::string to contain the time a document was added to the corpus.
    std::string _title;    //!< \private A std::string to contain the title.
    std::string _username; //!< \private A std::string to contain the username of the contributor.
    int _id;               //!< \private An integer containing the document ID.
    
    friend
    struct std::hash<Document>;
    
public:
    
    /*!
     * \fn Document().
     * \brief Initializes the member data with default values.
     */
    
    Document() : _body(std::string()),
                 _date(std::string()),
                 _time(std::string()),
                 _title(std::string()),
                 _username(std::string()),
                 _id(0) {}
    
    /*!
     * \fn Document(const std::string& body, const std::string& date, const std::string& time, const std::string& title, const std::string& username, const int& id).
     * \brief Initializes the member data with given values.
     * \param body - initializes the body string with the given value.
     * \param date - initializes the date string with the given value.
     * \param time - initializes the time string with the given value.
     * \param title - initializes the title string with the given value.
     * \param username - initializes the username string with the given value.
     * \param id - initializes the id with the given value.
     */
    
    Document(const std::string& body,
             const std::string& date,
             const std::string& time,
             const std::string& title,
             const std::string& username,
             int id) : _body(body),
                       _date(date),
                       _time(time),
                       _title(title),
                       _username(username),
                       _id(id) {}
    
    /*!
     * \fn Document(const Document& copy).
     * \brief Overloaded assignment operator.
     * \param copy - a Document object to copy assuming it's not self-assignment.
     * \return a Document reference.
     */
    
    Document& operator= (const Document& copy) {
    
        if(this != &copy) {
        
            _body = copy._body;
            _date = copy._date;
            _time = copy._time;
            _title = copy._title;
            _username = copy._username;
            _id = copy._id;
            
        }
        
        return *this;
        
    }
    
    /*!
     * \fn body().
     * \brief Returns the body text of a document.
     * \return reference to the Document's body text (std::string).
     */
    
    inline
    const std::string& body() const { return _body; }
    
    /*!
     * \fn body(const std::string& body).
     * \brief Sets the Document's body text.
     * \param body - a string to set the Document body text to.
     */
    
    inline
    void body(const std::string& body) { _body = body; }
    
    /*!
     * \fn date().
     * \brief Returns the date that the document was added to the corpus.
     * \return reference to the Document's date (std::string).
     */
    
    inline
    const std::string& date() const { return _date; }
    
    /*!
     * \fn date(const std::string& date).
     * \brief date the Document's date.
     * \param body - a string to set the Document date to.
     */
    
    inline
    void date(const std::string& date) { _date = date; }
    
    /*!
     * \fn id().
     * \brief Returns the ID of a document.
     * \return reference to the Document's ID number (int).
     */
    
    inline
    const int& id() const { return _id; }
    
    /*!
     * \fn id(const int& id).
     * \brief Sets the Document's ID number.
     * \param id - an integer to set the Document ID to.
     */
    
    inline
    void id(const int& id) { _id = id; }
    
    /*!
     * \fn time().
     * \brief Returns the time that the document was added to the corpus.
     * \return reference to the Document's time (std::string).
     */
    
    inline
    const std::string& time() const { return _time; }
    
    /*!
     * \fn time(const std::string& time).
     * \brief Sets the Document's time.
     * \param time - a string to set the Document time to.
     */
    
    inline
    void time(const std::string& time) { _time = time; }
    
    /*!
     * \fn title().
     * \brief Returns the title of a document.
     * \return reference to the Document's title (std::string).
     */
    
    inline
    const std::string& title() const { return _title; }
    
    /*!
     * \fn title(const std::string& title).
     * \brief Sets the Document's title.
     * \param title - a string to set the Document title to.
     */
    
    inline
    void title(const std::string& title) { _title = title; }
    
    /*!
     * \fn username().
     * \brief Returns the username of the contributor of a document.
     * \return reference to the Document's username (std::string).
     */
    
    inline
    const std::string& username() const { return _username; }
    
    /*!
     * \fn username(const std::string& username).
     * \brief Sets the Document's username.
     * \param username - a string to set the Document username to.
     */
    
    inline
    void username(const std::string& username) { _username = username; }
    
    /*!
     * \fn operator== (const Document& lhs, const Document& rhs).
     * \brief Compares two Document objects for equality.
     * \param lhs - A constant Document reference.
     * \param rhs - A constant Document reference.
     * \return boolean whether two Tokens are the same.
     */
    
    friend inline
    bool operator== (const Document& lhs,
                     const Document& rhs) { return (lhs._id == rhs._id); }
    
    /*!
     * \fn operator!= (const Document& lhs, const Document& rhs).
     * \brief Compares two Document objects for inequality.
     * \param lhs - A constant Document reference.
     * \param rhs - A constant Document reference.
     * \return boolean whether two Tokens are not the same.
     */
    
    friend inline
    bool operator!= (const Document& lhs,
                     const Document& rhs) { return !(lhs == rhs); }
    
    /*!
     * \fn operator< (const Document& lhs, const Document& rhs).
     * \brief Returns whether one Document is less than another.
     * \param lhs - A constant Document reference.
     * \param rhs - A constant Document reference.
     * \return boolean whether one Token is less than another.
     */
    
    friend inline
    bool operator< (const Document& lhs,
                    const Document& rhs) { return (lhs._title < rhs._title); }
    
};

// define hashing for Document objects
namespace std {

    template<>
    struct std::hash<Document> {
        
        std::size_t operator() (const Document& doc) {
            
            return ( (std::hash<int>()(doc._id) << 5) >> 6 );
            
        }
        
    };
    
}

#endif /* DOCUMENT_HPP */
