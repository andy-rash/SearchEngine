/*!
 * \file AVLTree.hpp
 * \brief Templated interface and implementation of an AVL tree.
 */

#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>

/*!
 * \struct node.
 * \param _Type - a type for the node template.
 * \brief A node for use in the AVL tree. Holds a value, height, and pointers to left and right child nodes.
 * \see AVLTree.
 */

template<class _Type>
struct node {
    
    typedef _Type	    value_type; //!< \typedef The base type of the node.
    
    value_type _value;              //!< \public Value stored in the node.
    int        _height;             //!< \public Height of the node in the tree.
    node*      _parent;             //!< \public A pointer to the parent of the node.
    node*      _left ;              //!< \public A pointer to the left child of the node.
    node* 	   _right;              //!< \public A pointer to the right child of the node.

    /*!
     * \fn node().
     * \brief Initializes the member data with default values.
     */
    
    node() : _value(value_type()), _height(-1), _parent(nullptr), _left(nullptr), _right(nullptr) {}
    
    /*!
     * \fn node(const node& copy).
     * \brief Copy constructor.
     * \param copy - another node to copy.
     */
    
    node(const node& copy) : _value(copy._value), _height(copy._height) {
        
        if(copy._left != nullptr) { _left = new node(*copy._left); }
        
        if(copy._right != nullptr)  { _right = new node(*copy._right); }
        
        if(_left != nullptr) {
            
            _left->_parent = this;
        
        }
        
        if(_right != nullptr) {
            
            _right->_parent = this;
        
        }
    
    }
    
    /*!
     * \fn node(node&& copy).
     * \brief Move constructor.
     * \param copy - another node to move from.
     */
    
    node(node&& copy) {
    
        _value = std::move(copy._value);
        _height = std::move(copy._height);
        
        _parent = copy._parent;
        copy._parent = nullptr;
        
        _left = copy._left;
        copy._left = nullptr;
        
        _right = copy._right;
        copy._right = nullptr;
        
    }
    
    /*!
     * \fn node(const value_type& value, node* parent, node* left, node* right).
     * \brief Initializes the member data with a given value and pointers to a parent, left, and right child and a height of -1.
     * \param value - a value of type value_type.
     * \param parent - a pointer to the parent of the new node (should almost always be nullptr).
     * \param left - a pointer to the left child of the new node (should almost always be nullptr).
     * \param right - a pointer to the right child of the new node (should almost always be nullptr).
     */
    
    node(const value_type& value,
         node* parent,
         node* left,
         node* right) : _value(value), _height(-1), _parent(parent), _left(left), _right(right) {}
    
    /*!
     * \fn node(const value_type& value, const size_type& height, node* parent, node* left, node* right).
     * \brief Initializes the member data with a given value, height, and pointers to the parent, left, and right child.
     * \param value - a value of type value_type.
     * \param height - the height for the new node (should almost always be -1).
     * \param parent - a pointer to the parent of the new node (should almost always be nullptr).
     * \param left - a pointer to the left child of the new node (should almost always be nullptr).
     * \param right - a pointer to the right child of the new node (should almost always be nullptr).
     */
    
    node(const value_type& value,
         const int& height,
         node* parent,
         node* left,
         node* right) : _value(value), _height(height), _parent(parent), _left(left), _right(right) {}

    /*!
     * \fn ~node()
     * \brief Destructor.
     */
    
    ~node() {
        
        // don't delete the parent before the child!
        
        if(_left != nullptr) {
            
            delete _left;
            _left = nullptr;
        
        }
        
        if(_right != nullptr) {
            
            delete _right;
            _right = nullptr;
        
        }
        
    }
    
    /*!
     * \fn operator= (node copy).
     * \param copy - a node passed by value.
     * \brief Assignment operator; uses copy-swap idiom.
     * \return a reference to a node.
     */
    
    node& operator= (node copy) {
    
        swap(*this,copy);
        
        return *this;
        
    }
    
    /*!
     * \fn swap(node<_Type>& lhs,node<_Type>& rhs).
     * \param lhs - first node to be swapped.
     * \param rhs - second node to be swapped.
     * \brief friend swap function for external use.
     */
    
    template<class _Type1>
    friend
    void swap(node<_Type>& lhs,
              node<_Type>& rhs) {
        
        using std::swap;
        
        swap(lhs._value,rhs._value);
        swap(lhs._height,rhs._height);
        swap(lhs._parent,rhs._parent);
        swap(lhs._left,rhs._parent);
        swap(lhs._right,rhs._right);
    
    }
    
};

// forward declare AVLTree class for use in the iterators
template<class _Type> class AVLTree;

/*!
 * \class AVLTree_iterator.
 * \param _Type - a type for the node pointer.
 * \param _NodePtr - a pointer to the nodes to be iterated through.
 * \brief A non-const iterator that iterates through the tree in-order.
 * \see AVLTree.
 */

template<class _Type,
         class _NodePtr>
class AVLTree_iterator {

    typedef _NodePtr        _node_pointer; //!< \typedef A pointer to the nodes in the AVL tree.
    typedef AVLTree<_Type>* _AVLTree;      //!< \typedef A reference AVL tree pointer.
    
    _node_pointer _ptr;                    //!< \private A pointer to the nodes in the AVL tree.
    _AVLTree _ref;                         //!< \private A reference AVL tree pointer.
    
    /*!
     * \fn AVLTree_iterator(_node_pointer ptr,_AVLTree tree).
     * \param ptr - node pointer for the iterator to be initialized with.
     * \param tree - a tree for the node to point to.
     * \brief Initializes the member data with given values.
     */
    
    AVLTree_iterator(_node_pointer ptr,
                     _AVLTree tree) : _ptr(ptr), _ref(tree) {}
    
    template<class> friend class AVLTree;
    template<class,class> friend class AVLTree_const_iterator;
    
public:
    
    typedef std::forward_iterator_tag                                             iterator_category;
    typedef typename std::pointer_traits<_node_pointer>::element_type::value_type value_type;
    typedef value_type&                                                           reference;
    typedef value_type*                                                           pointer;
    typedef std::ptrdiff_t                                                        difference_type;
    
    /*!
     * \fn AVLTree_iterator().
     * \brief Initializes the member data with default values.
     */
    
    AVLTree_iterator() : _ptr(nullptr), _ref(nullptr) {}
    
    /*!
     * \fn AVLTree_iterator(const AVLTree_iterator& copy).
     * \param copy - an AVL tree object to be copied.
     * \brief Initializes the member data with values from the copy object.
     */
    
    AVLTree_iterator(const AVLTree_iterator& copy) : _ptr(copy._ptr), _ref(copy._ref) {}
    
    /*!
     * \fn ~AVLTree_iterator().
     * \brief Default destructor.
     */
    
    ~AVLTree_iterator() {}
    
    /*!
     * \fn operator= (const AVLTree_iterator& copy).
     * \param copy - an AVL tree object to be copied.
     * \brief Assignment operator.
     * \return reference to the new AVL tree object.
     */
    
    AVLTree_iterator& operator= (const AVLTree_iterator& copy) {
    
        if(this != &copy) {
        
            _ptr = copy._ptr;
            _ref = copy._ref;
            
        }
        
        return *this;
        
    }
    
    /*!
     * \fn operator* () const.
     * \brief Dereference operator.
     * \return reference to the value contained in the node.
     */
    
    reference operator* () const { return _ptr->_value; }
    
    /*!
     * \fn operator-> () const.
     * \brief Arrow operator.
     * \return pointer to the node.
     */
    
    pointer operator-> () const { return &(operator*()); }
    
    /*!
     * \fn operator++ ().
     * \brief Pre-increment operator.
     * \return incremented iterator reference.
     */
    
    AVLTree_iterator& operator++ () {
    
        _node_pointer tmp;
        
        if(_ptr == nullptr) {
        
            _ptr = _ref->_root;
            
            if(_ptr == nullptr) { throw std::underflow_error("AVLTree_iterator operator++ () : tree is empty"); }
            
            while(_ptr->_left != nullptr) { _ptr = _ptr->_left; }
            
        } else {
            
            if(_ptr->_right != nullptr) {
            
                _ptr = _ptr->_right;
                
                while(_ptr->_left != nullptr) { _ptr = _ptr->_left; }
                
            } else {
            
                tmp = _ptr->_parent;
                
                while(tmp != nullptr && _ptr == tmp->_right) {
                
                    _ptr = tmp;
                    
                    tmp = tmp->_parent;
                    
                }
                
                _ptr = tmp;
                
            }
        
        }
            
        return *this;
        
    }
    
    /*!
     * \fn operator++ (int).
     * \brief Post-increment operator.
     * \return an iterator value that points to the iterator pre-increment.
     */
    
    AVLTree_iterator operator++ (int) {
    
        AVLTree_iterator tmp(*this);
        
        ++(*this);
        
        return tmp;
        
    }
    
    /*!
     * \fn operator== ().
     * \param lhs - first operand to be compared.
     * \param rhs - second operand to be compared.
     * \brief Equality operator.
     * \return boolean value whether the iterators are equal.
     */
    
    friend
    bool operator== (const AVLTree_iterator& lhs,
                     const AVLTree_iterator& rhs) { return (lhs._ptr == rhs._ptr) && (lhs._ref == rhs._ref); }
    
    /*!
     * \fn bool operator!= ().
     * \param lhs - first operand to be compared.
     * \param rhs - second operand to be compared.
     * \brief Inequality operator.
     * \return boolean value whether the iterators are not equal.
     */
    
    friend
    bool operator!= (const AVLTree_iterator& lhs,
                     const AVLTree_iterator& rhs) { return !(lhs == rhs); }
    
};

/*!
 * \class AVLTree_const_iterator.
 * \param _Type - a type for the node pointer.
 * \param _NodePtr - a pointer to the nodes to be iterated through.
 * \brief A constant iterator that iterates through the tree in-order.
 * \see AVLTree.
 */

template<class _Type,
         class _NodePtr>
class AVLTree_const_iterator {
    
    typedef _NodePtr        _node_pointer; //!< \typedef A pointer to the nodes in the AVL tree.
    typedef AVLTree<_Type>* _AVLTree;      //!< \typedef A reference AVL tree pointer.
    
    _node_pointer _ptr;                    //!< \public A pointer to the nodes in the AVL tree.
    _AVLTree _ref;                         //!< \public A reference AVL tree pointer.
    
    /*!
     * \fn AVLTree_const_iterator(_node_pointer ptr,_AVLTree tree).
     * \param ptr - node pointer for the iterator to be initialized with.
     * \param tree - a tree for the node to point to.
     * \brief Initializes the member data with given values.
     */
    
    AVLTree_const_iterator(_node_pointer ptr,
                           _AVLTree tree) : _ptr(ptr), _ref(tree) {}
    
    template<class>       friend class AVLTree;
    template<class,class> friend class AVLTree_iterator;
    
public:
    
    typedef std::forward_iterator_tag                                             iterator_category;
    typedef typename std::pointer_traits<_node_pointer>::element_type::value_type value_type;
    typedef value_type&                                                           reference;
    typedef value_type*                                                           pointer;
    typedef std::ptrdiff_t                                                        difference_type;
    
    /*!
     * \fn AVLTree_const_iterator().
     * \brief Initializes the member data with default values.
     */
    
    AVLTree_const_iterator() : _ptr(nullptr), _ref(nullptr) {}
    
    /*!
     * \fn AVLTree_const_iterator(const AVLTree_iterator<_Type,_node_pointer>& copy).
     * \param copy - an AVL tree object to be copied.
     * \brief Initializes the member data with values from the copy object.
     */
    
    AVLTree_const_iterator(const AVLTree_iterator<_Type,_node_pointer>& copy) : _ptr(copy._ptr), _ref(copy._ref) {}
    
    /*!
     * \fn AVLTree_const_iterator(const AVLTree_const_iterator& copy).
     * \param copy - an AVL tree object to be copied.
     * \brief Initializes the member data with values from the copy object.
     */
    
    AVLTree_const_iterator(const AVLTree_const_iterator& copy) : _ptr(copy._ptr), _ref(copy._ref) {}
    
    /*!
     * \fn ~AVLTree_const_iterator().
     * \brief Default destructor.
     */
    
    ~AVLTree_const_iterator() {}
    
    /*!
     * \fn operator= (const AVLTree_const_iterator& copy).
     * \param copy - an AVL tree object to be copied.
     * \brief Assignment operator.
     * \return reference to the new AVL tree object.
     */
    
    AVLTree_const_iterator& operator= (const AVLTree_const_iterator& copy) {
        
        if(this != &copy) {
            
            _ptr = copy._ptr;
            _ref = copy._ref;
            
        }
        
        return *this;
        
    }
    
    /*!
     * \fn operator* () const.
     * \brief Dereference operator.
     * \return reference to the value contained in the node.
     */
    
    reference operator* () const { return _ptr->_value; }
    
    /*!
     * \fn operator-> () const.
     * \brief Arrow operator.
     * \return pointer to the node.
     */
    
    pointer operator-> () const { return &(operator*()); }
    
    /*!
     * \fn operator++ ().
     * \brief Pre-increment operator.
     * \return incremented iterator reference.
     */
    
    AVLTree_const_iterator& operator++ () {
        
        _node_pointer tmp;
        
        if(_ptr == nullptr) {
            
            _ptr = _ref->_root;
            
            if(_ptr == nullptr) { throw std::underflow_error("AVLTree_iterator operator++ () : tree is empty"); }
            
            while(_ptr->_left != nullptr) { _ptr = _ptr->_left; }
            
        } else {
            
            if(_ptr->_right != nullptr) {
                
                _ptr = _ptr->_right;
                
                while(_ptr->_left != nullptr) { _ptr = _ptr->_left; }
                
            } else {
                
                tmp = _ptr->_parent;
                
                while(tmp != nullptr && _ptr == tmp->_right) {
                    
                    _ptr = tmp;
                    
                    tmp = tmp->_parent;
                    
                }
                
                _ptr = tmp;
                
            }
            
        }
        
        return *this;
        
    }
    
    /*!
     * \fn operator++ (int).
     * \brief Post-increment operator.
     * \return an iterator value that points to the iterator pre-increment.
     */
    
    AVLTree_const_iterator operator++ (int) {
        
        AVLTree_const_iterator tmp(*this);
        
        ++(*this);
        
        return tmp;
        
    }
    
    /*!
     * \fn operator== ().
     * \param lhs - first operand to be compared.
     * \param rhs - second operand to be compared.
     * \brief Equality operator.
     * \return boolean value whether the iterators are equal.
     */
    
    friend
    bool operator== (const AVLTree_const_iterator& lhs,
                     const AVLTree_const_iterator& rhs) { return lhs._ptr == rhs._ptr; }
    
    /*!
     * \fn operator!= ().
     * \param lhs - first operand to be compared.
     * \param rhs - second operand to be compared.
     * \brief Inequality operator.
     * \return boolean value whether the iterators are not equal.
     */
    
    friend
    bool operator!= (const AVLTree_const_iterator& lhs,
                     const AVLTree_const_iterator& rhs) { return !(lhs == rhs); }
    
};

/*!
 * \class AVLTree.
 * \brief An AVL Tree template.
 * \see AVLTree_iterator.
 * \see AVLTree_const_iterator.
 * \see node.
 */

template<class _Type>
class AVLTree {
    
private:
    
    typedef _Type             value_type;      //!< \typedef The base type of the tree.
    typedef value_type&       reference;       //!< \typedef A reference to the base type of the tree.
    typedef const value_type& const_reference; //!< \typedef A constant refernce to the base type of the tree.
    typedef std::size_t       size_type;       //!< \typedef An unsigned integral type; used for the size of the tree.
    typedef node<value_type>  _node;           //!< \typedef A node.
    typedef node<value_type>* _node_pointer;   //!< \typedef A pointer to a node.
    
    template<class,class> friend class AVLTree_iterator;
    template<class,class> friend class AVLTree_const_iterator;
    
    _node_pointer _root;                       //!< \private A pointer to the root node.
    size_type     _sz;                         //!< \private size_type that holds the size of the tree.
    
public:
    
    typedef AVLTree_iterator<_Type, _node_pointer>       iterator;       //!< \typedef A forward iterator over the tree.
    typedef AVLTree_const_iterator<_Type, _node_pointer> const_iterator; //!< \typedef A forward const_iterator over the tree.
    
    /*!
     * \fn AVLTree().
     * \brief Initializes the member data with default values.
     */
    
    AVLTree() : _root(nullptr),_sz(0) {}
    
    /*!
     * \fn AVLTree(const AVLTree& copy).
     * \brief Copy constructor.
     * \param copy - an object reference to an AVLTree instance to be copied.
     */
    
    AVLTree(const AVLTree& copy) : _sz(copy._sz) {
    
        if(copy._root) {
            
            _root = new _node(*copy._root);
        
        }
        
    }
    
    /*!
     * \fn AVLTree(AVLTree&& copy).
     * \brief Move constructor.
     * \param copy - an rvalue reference to an AVLTree instance to be moved from.
     */
    
    AVLTree(AVLTree&& copy) : _root(copy._root), _sz(copy._sz) {
    
        copy._root = nullptr;
        copy._sz = 0;
        
    }
    
    /*!
     * \fn ~AVLTree().
     * \brief Destructor. Calls _clear() to properly manage memory.
     */
    
    ~AVLTree() { _clear(_root); }
    
    /*!
     * \fn operator= (const AVLTree& copy).
     * \brief Overloaded assignment operator.
     * \param copy - an object reference to an AVLTree instance to be copied.
     * \return reference to an AVLTree object.
     */
    
    AVLTree& operator= (AVLTree copy);

    /*!
     * \fn begin().
     * \brief Beginning element of the tree (lowest element).
     * \return iterator to the first node in-order in the AVL tree.
     */
    
    iterator begin();
    
    /*!
     * \fn begin().
     * \brief Beginning element of the tree (lowest element).
     * \return const_iterator to the first node in-order in the AVL tree.
     */
    
    const_iterator begin() const;
    
    /*!
     * \fn clear().
     * \brief Removes all elements in the tree.
     */
    
    void clear() { _clear(_root); _sz = 0; }
    
    /*!
     * \fn contains(const value_type& val).
     * \brief Returns whether the tree is empty.
     * \param val - a value to search for in the tree.
     * \return bool whether the tree contains the value.
     */
    
    bool contains(const value_type& val) { return _contains(val,_root); }
    
    /*!
     * \fn empty().
     * \brief Returns whether the tree is empty.
     * \return bool whether tree is empty.
     */
    
    bool empty() const { return (_root == nullptr); }
    
    /*!
     * \fn iterator end().
     * \brief Last position in tree (after max element).
     * \return iterator to a nullptr.
     */
    
    inline
    iterator end() { return iterator(nullptr,this); }
    
    /*!
     * \fn const_iterator end().
     * \brief Last position in tree (after max element).
     * \return const_iterator to a nullptr.
     */
    
    inline
    const_iterator end() const { return const_iterator(nullptr,this); }
    
    /*!
     * \fn find(const value_type& val).
     * \brief Returns a value from the tree.
     * \param val - a value to search for in the tree.
     * \return iterator to a value in the tree or end() if it doesn't exist.
     */
    
    iterator find(const value_type& val) { return _find(val,_root); }
    
    /*!
     * \fn find(const value_type& val).
     * \brief Returns a value from the tree.
     * \param val - a value to search for in the tree.
     * \return const_iterator to a value in the tree or end() if it doesn't exist.
     */
    
    const_iterator find(const value_type& val) const { return std::lower_bound(begin(),end(),val); }
    
    /*!
     * \fn insert(const value_type& val).
     * \brief Inserts an element of type value_type into the list.
     */

    void insert(const value_type& val) { _insert(val,_root); ++_sz; }
    
    /*!
     * \fn size().
     * \brief Returns the size of the tree.
     * \return size_type representing the size of the tree.
     */
    
    size_type size() const { return _sz; }
    
    /*!
     * \fn operator== (const AVLTree& lhs, AVLTree& rhs).
     * \brief Compares two AVL trees for equality.
     * \param lhs - one AVL tree to compare.
     * \param ptr - second AVL tree to compare.
     * \return boolean whether two trees are equal.
     */
    
    friend inline
    bool operator== (AVLTree& lhs,
                     AVLTree& rhs) { return (lhs._root == rhs._root) && (lhs._sz == rhs._sz); }
    
    /*!
     * \fn operator!= (const AVLTree& lhs, AVLTree& rhs).
     * \brief Compares two AVL trees for inequality.
     * \param lhs - one AVL tree to compare.
     * \param ptr - second AVL tree to compare.
     * \return boolean whether two trees are not equal.
     */
    
    friend inline
    bool operator!= (AVLTree& lhs,
                     AVLTree& rhs) { return !(lhs == rhs); }
    
    /*!
     * \fn swap(AVLTree& other).
     * \brief Swaps this with another AVL tree.
     * \param other - the other AVL tree to swap this with.
     */
    
    void swap(AVLTree& other);
    
private:
    
    /*!
     * \fn _clear(node_pointer& ptr).
     * \brief Internal function. Deletes a node and its subtree(s) recursively.
     * \param ptr - a reference to a pointer to a node in the tree.
     */
    
    void _clear(_node_pointer& ptr);
    
    /*!
     * \fn _contains(const value_type& val, node_pointer& ptr).
     * \brief Internal function. Attempts to find a value in the tree.
     * \param val - a value to search for in the tree.
     * \param ptr - a reference to a pointer to a node in the tree.
     * \return bool whether the tree contains the value.
     */
    
    bool _contains(const value_type& val,
                   _node_pointer& ptr);
    
    /*!
     * \fn _find(const value_type& val, node_pointer& ptr).
     * \brief Internal function. Finds a value in the tree and returns an iterator to that position.
     * \param val - a value to find in the tree.
     * \param ptr - a reference to a pointer to a node in the tree.
     * \return iterator to the given value.
     */
    
    iterator _find(const value_type& val,
                   _node_pointer& ptr);
    
    /*!
     * \fn _find(const value_type& val, node_pointer& ptr).
     * \brief Internal function. Finds a value in the tree and returns a const_iterator to that position.
     * \param val - a value to find in the tree.
     * \param ptr - a reference to a pointer to a node in the tree.
     * \return const_iterator to the given value.
     */
    
    const_iterator _find(const value_type& val,
                         _node_pointer& ptr) const;
    
    /*!
     * \fn _height(node_pointer ptr).
     * \brief Internal function. Returns the height of a given node.
     * \param ptr - a pointer to a node in the tree.
     * \return integer representing the height of a node.
     */
    
    int _height(_node_pointer ptr) const { return (ptr) ? ptr->_height : -1; }
    
    /*!
     * \fn _insert(const value_type& val, node_pointer& ptr).
     * \brief Internal function. Inserts a value recursively into the tree at a given node.
     * \param val - a value to be inserted.
     * \param ptr - a pointer to a node in the tree.
     */
    
    void _insert(const value_type& val,
                 _node_pointer& ptr);
    
    /*!
     * \fn _max(const int& lhs, const int& rhs).
     * \brief Internal function. Returns the greater of two integers.
     * \param lhs - left hand side value.
     * \param rhs - right hand side value.
     * \return integer representing the greater of the two given values.
     */
    
    int _max(const int& lhs,
             const int& rhs) const { return (lhs < rhs) ? rhs : lhs; }
    
    /*!
     * \fn _leftLeft(node_pointer& ptr).
     * \brief Internal function. A case 1 rotate: when a node is inserted into the left subtree of the left child of the node of imbalance.
     * \param ptr - a reference to a pointer to a node in the tree.
     */
    
    void _leftLeft(_node_pointer& ptr);
    
    /*!
     * \fn _leftLeft(node_pointer& ptr).
     * \brief Internal function. A case 2 rotate: when a node is inserted into the right subtree of the left child of the node of imbalance.
     * \param ptr - a reference to a pointer to a node in the tree.
     */
    
    void _leftRight(_node_pointer& ptr);
    
    /*!
     * \fn _leftLeft(node_pointer& ptr).
     * \brief Internal function. A case 3 rotate: when a node is inserted into the left subtree of the right child of the node of imbalance.
     * \param ptr - a reference to a pointer to a node in the tree.
     */
    
    void _rightLeft(_node_pointer& ptr);
    
    /*!
     * \fn _leftLeft(node_pointer& ptr).
     * \brief Internal function. A case 4 rotate: when a node is inserted into the right subtree of the right child of the node of imbalance.
     * \param ptr - a reference to a pointer to a node in the tree.
     */
    
    void _rightRight(_node_pointer& ptr);
    
};

template<class _Type>
void AVLTree<_Type>::_clear(_node_pointer& ptr) {
    
    if(ptr) {
        
        _clear(ptr->_left);
        _clear(ptr->_right);
        
        delete ptr;
        
    }
    
    ptr = nullptr;
    
}

template<class _Type>
bool AVLTree<_Type>::_contains(const value_type& val,
                               _node_pointer& ptr) {

    _node_pointer tmp = ptr;
    bool exists = false;
    
    if(ptr) {
        
        while(ptr) {
            
            if(val < ptr->_value) { ptr = ptr->_left; }
            else if(ptr->_value < val) { ptr = ptr->_right; }
            else {
                
                exists = true;
                break;
            
            }
            
        }
        
    }
    
    ptr = tmp;
    
    return exists;
    
}

template<class _Type>
typename AVLTree<_Type>::iterator
AVLTree<_Type>::_find(const value_type& val,
                      _node_pointer& ptr) {

    _node_pointer tmp = ptr;
    iterator it = end();
    
    if(ptr) {
        
        while(ptr) {
            
            if(val < ptr->_value)       { ptr = ptr->_left;  }
            else if(ptr->_value < val)  { ptr = ptr->_right; }
            else if(ptr->_value == val) { it = iterator(ptr,this); break; }
            else                        { it = end(); break; }
            
        }
        
    }
    
    ptr = tmp;
    
    return it;
    
}

template<class _Type>
typename AVLTree<_Type>::const_iterator
AVLTree<_Type>::_find(const value_type& val,
                      _node_pointer& ptr) const {
    
    _node_pointer tmp = ptr;
    const_iterator it = end();
    
    if(ptr) {
        
        while(ptr) {
            
            if(val < ptr->_value)       { ptr = ptr->_left;  }
            else if(ptr->_value < val)  { ptr = ptr->_right; }
            else if(ptr->_value == val) { it = const_iterator(ptr,this); break; }
            else                        { it = end(); break; }
            
        }
        
    }
    
    ptr = tmp;
    
    return it;
    
}

template<class _Type>
void AVLTree<_Type>::_insert(const value_type& val,
                             _node_pointer& ptr) {
    
    if(!ptr) { ptr = new node<value_type>(val,nullptr,nullptr,nullptr); }
    else if(val < ptr->_value) {
        
        _insert(val,ptr->_left);
        
        if(ptr->_left) { ptr->_left->_parent = ptr; }
        
        if(_height(ptr->_left) - _height(ptr->_right) == 2) {
            
            if(val < ptr->_left->_value) { _leftLeft(ptr); }
            else { _leftRight(ptr); }
            
        }
        
    } else if(ptr->_value < val) {
        
        _insert(val,ptr->_right);

        if(ptr->_right) { ptr->_right->_parent = ptr; }
        
        if(_height(ptr->_right) - _height(ptr->_left) == 2) {
            
            if(ptr->_right->_value < val) { _rightRight(ptr); }
            else { _rightLeft(ptr); }
            
        }
        
    }
    
    ptr->_height = _max(_height(ptr->_left),_height(ptr->_right)) + 1;
    
}

template<class _Type>
void AVLTree<_Type>::_leftLeft(_node_pointer& ptr) {
    
    _node_pointer tmp = ptr->_left;
    
    ptr->_left = tmp->_right;
    
    if(ptr->_left) { ptr->_left->_parent = ptr; }
    
    tmp->_right = ptr;
    
    tmp->_parent = ptr->_parent;
    
    ptr->_parent = tmp;
    
    ptr->_height = _max(_height(ptr->_left),_height(ptr->_right)) + 1;
    
    tmp->_height = _max(_height(tmp->_left),ptr->_height) + 1;
    
    ptr = tmp;
    
}

template<class _Type>
void AVLTree<_Type>::_leftRight(_node_pointer& ptr) {
    
    _rightRight(ptr->_left);
    
    _leftLeft(ptr);
    
}

template<class _Type>
void AVLTree<_Type>::_rightLeft(_node_pointer& ptr) {
    
    _leftLeft(ptr->_right);
    
    _rightRight(ptr);
    
}

template<class _Type>
void AVLTree<_Type>::_rightRight(_node_pointer& ptr) {
    
    _node_pointer tmp = ptr->_right;
    
    ptr->_right = tmp->_left;
    
    if(ptr->_right) { ptr->_right->_parent = ptr; }
    
    tmp->_left = ptr;
    
    tmp->_parent = ptr->_parent;
    
    ptr->_parent = tmp;
    
    ptr->_height = _max(_height(ptr->_right),_height(ptr->_left)) + 1;
    
    tmp->_height = _max(_height(tmp->_right),ptr->_height) + 1;
    
    ptr = tmp;
    
}

template<class _Type>
AVLTree<_Type>& AVLTree<_Type>::operator= (AVLTree copy) {
    
    AVLTree::swap(copy);
    
    return *this;
    
}

template<class _Type>
typename AVLTree<_Type>::iterator
AVLTree<_Type>::begin() {

    _node_pointer tmp = _root;
    
    if(tmp) {
    
        if(tmp->_left != nullptr) {
            
            while(tmp->_left != nullptr) { tmp = tmp->_left; }
            
        }
        
    }
    
    return iterator(tmp,this);
    
}

template<class _Type>
typename AVLTree<_Type>::const_iterator
AVLTree<_Type>::begin() const {
    
    _node_pointer tmp = _root;
    
    if(tmp) {
        
        if(tmp->_left != nullptr) {
            
            while(tmp->_left != nullptr) { tmp = tmp->_left; }
            
        }
        
    }
    
    return const_iterator(tmp,this);
    
}

template<class _Type>
void AVLTree<_Type>::swap(AVLTree& other) {

    using std::swap;
    
    swap(_root,other._root);
    swap(_sz,other._sz);
    
}

template<class _Type>
void swap(AVLTree<_Type>& lhs,
          AVLTree<_Type>& rhs) { lhs.swap(rhs); }

#endif /* AVLTREE_HPP */
