
#include <fstream>
#include <iostream>
#include <string>
 
#include "cereal/archives/json.hpp" 
#include "cereal/types/memory.hpp"
#include "cereal/types/string.hpp"  
#include "cereal/types/unordered_map.hpp"

using namespace std;

struct MyRecord {
  int x, y;
  float z;

  template <class Archive>
  void serialize(Archive& ar) {
    ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(z));
  }

  friend std::ostream& operator<<(std::ostream& os, const MyRecord& mr);
};

std::ostream& operator<<(std::ostream& os, const MyRecord& mr) {
  os << "MyRecord(" << mr.x << ", " << mr.y << "," << mr.z << ")\n";
  return os;
}

struct SomeData {
  int32_t id;
  std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data;

  SomeData(int32_t id_ = 0) : id(id_), data(new std::unordered_map<uint32_t, MyRecord>) {}

  template <class Archive>
  void save(Archive& ar) const {
    ar(CEREAL_NVP(id), CEREAL_NVP(data));
  }

  template <class Archive>
  void load(Archive& ar) {
    ar(id, data);
  }

  void push(uint32_t, const MyRecord& mr) { data->insert(std::make_pair(100, mr)); }

  void print() {
    std::cout << "ID : " << id << "\n";
    if (data->empty()) return;
    for (auto& item : *data) {
      std::cout << item.first << "\t" << item.second << "\n";
    }
  }
};

void test() {
  {
    std::ofstream os("obj.json");
    cereal::JSONOutputArchive archive(os);

    MyRecord mr = {1, 2, 3.0};

    SomeData myData(1111);
    myData.push(100, mr);

    archive(myData);
  }
  {
    std::ifstream is("obj.json");
    cereal::JSONInputArchive archive(is);

    SomeData myData;
    archive(myData);
    myData.print();
  }
}

int main() {
  test(); 
 
  return 0;
}