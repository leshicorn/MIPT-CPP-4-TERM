#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

template <typename Iterator>
class Page {
public:
    Page(Iterator begin, Iterator end)
        : begin_(begin), end_(end) {}

    size_t size() const {
        return distance(begin_, end_);
    }

    Iterator begin() const {
        return begin_;
    }

    Iterator end() const {
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
        : begin_(begin), end_(end), page_size_(page_size) {}

    size_t size() const {
        return (distance(begin_, end_) + page_size_ - 1) / page_size_;
    }

    auto begin() const {
        return PageIterator(begin_, end_, page_size_, 0);
    }

    auto end() const {
        return PageIterator(begin_, end_, page_size_, size());
    }

private:
    Iterator begin_, end_;
    size_t page_size_;

    class PageIterator : public iterator<forward_iterator_tag, Page<Iterator>> {
    public:
        PageIterator(Iterator begin, Iterator end, size_t page_size, size_t page_index)
            : begin_(begin), end_(end), page_size_(page_size), page_index_(page_index) {
            advance_iterator_to_current_page();
        }

        bool operator==(const PageIterator& other) const {
            return begin_ == other.begin_ && end_ == other.end_ && page_index_ == other.page_index_;
        }

        bool operator!=(const PageIterator& other) const {
            return !(*this == other);
        }

        PageIterator& operator++() {
            advance_iterator_to_next_page();
            return *this;
        }

        PageIterator operator++(int) {
            PageIterator temp = *this;
            advance_iterator_to_next_page();
            return temp;
        }

        const Page<Iterator>& operator*() const {
            return page_;
        }

        const Page<Iterator>* operator->() const {
            return &page_;
        }

    private:
        Iterator begin_, end_;
        size_t page_size_, page_index_;
        Page<Iterator> page_;

        void advance_iterator_to_current_page() {
            size_t offset = page_index_ * page_size_;
            begin_ = next(begin_, offset);
            end_ = min(next(begin_, page_size_), end_);
            page_ = Page<Iterator>(begin_, end_);
        }

        void advance_iterator_to_next_page() {
            size_t offset = (++page_index_) * page_size_;
            begin_ = next(begin_, offset);
            end_ = min(next(begin_, page_size_), end_);
            page_ = Page<Iterator>(begin_, end_);
        }
    };
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    using Iterator = decltype(begin(c));
    return Paginator<Iterator>(begin(c), end(c), page_size);
}

void TestPageCounts() {
    vector<int> v(15);

    assert(Paginate(v, 1).size() == v.size());
    assert(Paginate(v, 3).size() == 5u);
    assert(Paginate(v, 5).size() == 3u);
    assert(Paginate(v, 4).size() == 4u);
    assert(Paginate(v, 15).size() == 1u);
    assert(Paginate(v, 150).size() == 1u);
    assert(Paginate(v, 14).size() == 2u);
}

void TestLooping() {
    vector<int> v(15);
    iota(begin(v), end(v), 1);

    Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
    ostringstream os;
    for (const auto& page : paginate_v) {
        for (int x : page) {
            os << x << ' ';
        }
        os << '\n';
    }

    assert(os.str() == "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
    vector<string> vs = {"one", "two", "three", "four", "five"};
    for (auto page : Paginate(vs, 2)) {
        for (auto& word : page) {
            word[0] = toupper(word[0]);
        }
    }

    const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
    assert(vs == expected);
}

void TestPageSizes() {
    string letters(26, ' ');

    Paginator letters_pagination(letters.begin(), letters.end(), 11);
    vector<size_t> page_sizes;
    for (const auto& page : letters_pagination) {
        page_sizes.push_back(page.size());
    }

    const vector<size_t> expected = {11, 11, 4};
    assert(page_sizes == expected);
}

void TestConstContainer() {
    const string letters = "abcdefghijklmnopqrstuvwxyz";

    vector<string> pages;
    for (const auto& page : Paginate(letters, 10)) {
        pages.push_back(string(page.begin(), page.end()));
    }

    const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
    assert(pages == expected);
}

void TestPagePagination() {
    vector<int> v(22);
    iota(begin(v), end(v), 1);

    vector<vector<int>> lines;
    for (const auto& split_by_9 : Paginate(v, 9)) {
        for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
            lines.push_back({});
            for (int item : split_by_4) {
                lines.back().push_back(item);
            }
        }
    }

    const vector<vector<int>> expected = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9},
        {10, 11, 12, 13},
        {14, 15, 16, 17},
        {18},
        {19, 20, 21, 22}
    };
    assert(lines == expected);
}

int main() {
    TestPageCounts();
    TestLooping();
    TestModification();
    TestPageSizes();
    TestConstContainer();
    TestPagePagination();

    cout << "All tests passed!" << endl;

    return 0;
}
