#include <iostream> 
#include <memory_resource> 
#include <map> 
#include <list> 
#include <stdexcept> 
#include <iterator> 
#include <utility> 
#include <initializer_list> 
 
class CustomMemoryResource : public std::pmr::memory_resource { 
public: 
    ~CustomMemoryResource() { 
        for (auto& [ptr, size] : allocated_blocks_) { 
            ::operator delete(ptr); 
        } 
    } 
 
protected: 
    void* do_allocate(size_t bytes, size_t alignment) override { 
        auto it = recycled_blocks_.find(bytes); 
        if (it != recycled_blocks_.end() && !it->second.empty()) { 
            void* ptr = it->second.front(); 
            it->second.pop_front(); 
            return ptr; 
        } 
        void* ptr = ::operator new(bytes, std::align_val_t(alignment)); 
        allocated_blocks_[ptr] = bytes; 
        return ptr; 
    } 
 
    void do_deallocate(void* p, size_t bytes, size_t alignment) override { 
        auto it = allocated_blocks_.find(p); 
        if (it != allocated_blocks_.end() && it->second == bytes) { 
            allocated_blocks_.erase(it); 
            recycled_blocks_[bytes].push_back(p); 
        } 
    } 
 
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override { 
        return this == &other; 
    } 
 
private: 
    std::map<void*, size_t> allocated_blocks_; 
    std::map<size_t, std::list<void*>> recycled_blocks_; 
}; 
 
template <class T, class allocator_type = std::pmr::polymorphic_allocator<T>> 
requires std::is_copy_constructible_v<T> && std::is_same_v<allocator_type, std::pmr::polymorphic_allocator<T>> 
class ForwardList { 
private: 
    struct Node { 
        T data_; 
        Node* next_; 
        explicit Node(const T& val) : data_(val), next_(nullptr) {} 
    }; 
 
    using node_allocator_type = std::pmr::polymorphic_allocator<Node>; 
    node_allocator_type node_allocator_; 
    allocator_type allocator_; 
    Node* head_; 
    size_t size_; 
 
public: 
    class ForwardListIterator { 
    public: 
        using value_type = T; 
        using reference_type = value_type&; 
        using pointer_type = value_type*; 
        using difference_type = std::ptrdiff_t; 
        using iterator_category = std::forward_iterator_tag; 
 
        explicit ForwardListIterator(Node* node) : current_(node) {} 
 
        inline bool operator==(const ForwardListIterator& other) const { 
            return current_ == other.current_; 
        } 
 
        inline bool operator!=(const ForwardListIterator& other) const { 
            return !(*this == other); 
        } 
 
        inline reference_type operator*() const { 
            return current_->data_; 
        } 
 
        ForwardListIterator& operator++() { 
            current_ = current_->next_; 
            return *this; 
        } 
 
        ForwardListIterator operator++(int) { 
            ForwardListIterator temp = *this; 
            ++(*this); 
            return temp; 
        } 
 
        inline pointer_type operator->() const { 
            return &(current_->data_); 
        } 
 
    private: 
        Node* current_; 
 
        friend class ForwardList; 
    }; 
 
    explicit ForwardList(const allocator_type& resource = std::pmr::get_default_resource()) 
        : allocator_(resource), node_allocator_(resource), head_(nullptr), size_(0) {} 
 
    explicit ForwardList(size_t sz, std::pmr::memory_resource* resource = std::pmr::get_default_resource()) 
        : ForwardList(resource) { 
        Node* current = nullptr; 
        for (size_t i = 0; i < sz; ++i) { 
            Node* new_node = node_allocator_.allocate(1); 
            new (new_node) Node(T()); 
            if (!head_) { 
                head_ = new_node; 
            } else { 
                current->next_ = new_node; 
            } 
            current = new_node; 
            ++size_; 
        } 
    } 
 
    ForwardList(const std::initializer_list<T>& other, std::pmr::memory_resource* resource = std::pmr::get_default_resource()) 
        : ForwardList(resource) { 
        Node* current = nullptr; 
        for (const T& val : other) { 
            Node* new_node = node_allocator_.allocate(1); 
            new (new_node) Node(val); 
            if (!head_) { 
                head_ = new_node; 
            } else { 
                current->next_ = new_node; 
            } 
            current = new_node; 
            ++size_; 
        } 
    } 
 
    ForwardList(const ForwardList& other, std::pmr::memory_resource* resource = std::pmr::get_default_resource()) 
        : ForwardList(resource) { 
        Node* current_other = other.head_; 
        Node* current = nullptr; 
        while (current_other) { 
            Node* new_node = node_allocator_.allocate(1); 
            new (new_node) Node(current_other->data_); 
            if (!head_) { 
                head_ = new_node; 
            } else { 
                current->next_ = new_node; 
            } 
            current = new_node; 
            current_other = current_other->next_; 
            ++size_; 
        } 
    } 
 
    ForwardList& operator=(const ForwardList& other) { 
        if (this != &other) { 
            Clear(); 
            Node* current_other = other.head_; 
            Node* current = nullptr; 
            while (current_other) { 
                Node* new_node = node_allocator_.allocate(1); 
                new (new_node) Node(current_other->data_); 
                if (!head_) { 
                    head_ = new_node; 
                } else { 
                    current->next_ = new_node; 
                } 
                current = new_node; 
                current_other = current_other->next_; 
                ++size_; 
            } 
        } 
        return *this; 
    } 
 
    void Swap(ForwardList& other) { 
        std::swap(head_, other.head_); 
        std::swap(size_, other.size_); 
    } 
 
    void EraseAfter(ForwardListIterator pos) { 
        if (!pos.current_ || !pos.current_->next_) { 
            return; 
        } 
        Node* temp = pos.current_->next_; 
        pos.current_->next_ = temp->next_; 
        temp->~Node(); 
        node_allocator_.deallocate(temp, 1); 
        --size_; 
    } 
 
    void InsertAfter(ForwardListIterator pos, const T& value) { 
        Node* new_node = node_allocator_.allocate(1); 
        new (new_node) Node(value); 
        new_node->next_ = pos.current_->next_; 
        pos.current_->next_ = new_node; 
        ++size_; 
    } 
 
    ForwardListIterator Find(const T& value) const { 
        Node* current = head_; 
        while (current) { 
            if (current->data_ == value) { 
                return ForwardListIterator(current); 
            } 
            current = current->next_; 
        } 
        return End(); 
    } 
 
    void Clear() { 
        while (head_) { 
            PopFront(); 
        } 
    } 
 
    void PushFront(const T& value) { 
        Node* new_node = node_allocator_.allocate(1); 
        new (new_node) Node(value); 
        new_node->next_ = head_; 
        head_ = new_node; 
        ++size_; 
    } 
 
    void PopFront() { 
        if (!head_) { 
            throw std::runtime_error("List is empty!"); 
        } 
        Node* temp = head_; 
        head_ = head_->next_; 
        temp->~Node(); 
        node_allocator_.deallocate(temp, 1); 
        --size_; 
    } 
 
    T& Front() { 
        if (IsEmpty()) { 
            throw std::runtime_error("List is empty!"); 
        } 
        return head_->data_; 
    } 
 
    const T& Front() const { 
        if (IsEmpty()) { 
            throw std::runtime_error("List is empty!"); 
        } 
        return head_->data_; 
    } 
 
    ForwardListIterator Begin() const noexcept { return ForwardListIterator(head_); } 
    ForwardListIterator End() const noexcept { return ForwardListIterator(nullptr); } 
    bool IsEmpty() const noexcept { return size_ == 0; } 
    size_t Size() const noexcept { return size_; } 
 
    ~ForwardList() { Clear(); } 
};