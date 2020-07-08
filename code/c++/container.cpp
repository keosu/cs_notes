  // map
  map<int, int> x{{3, 5}, {1, 1}, {2, 0}, {7, 9}};
  x.insert(make_pair(51, 87));
  x[435]++; // default value is 0
  x[435]++;
  cout << "map has key: " << x.count(436) << endl;
  for (auto i = x.begin(); i != x.end(); i++) {
    cout << i->first << " : " << i->second << endl;
  }
  cout << endl;

  // map: sort key
  struct cmp {
    bool operator()(const int& k1, const int& k2) { return k1 > k2; }
  };
  map<int, int, cmp> xy{{3, 5}, {1, 1}, {2, 0}, {7, 9}};
  xy.insert(make_pair(51, 87));

  for (auto i = xy.begin(); i != xy.end(); i++) {
    cout << i->first << " : " << i->second << endl;
  }
  
  // priority_queue
  
#include <iostream> // For standard streams
#include <queue> // For priority_queue<T>
#include <string> // For string class
using std::string;

// List contents of a priority queue
template<typename T>
void list_pq(std::priority_queue<T> pq, size_t count = 5) {
    size_t n {count};
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
        if (--n) continue;
        std::cout << std::endl;
        n = count;
    }
    std::cout << std::endl;
}

int main() {
    std::priority_queue<std::string> words;
    std::string word;
    std::cout << "Enter words separated by spaces, enter Ctrl+Z on a separate line to end:\n";
    while (true) {
        if ((std::cin >> word).eof())
            break;
        words.push(word);
    }
    std::cout << "You entered " << words.size() << " words:" << std::endl;
    list_pq(words);
}
