
// #include <iguana/json_reader.hpp>
// #include <iguana/json_writer.hpp>
#include <iguana/dynamic.hpp>

#include <string>

struct pair_t : public iguana::base_impl<pair_t> {
  pair_t() = default;
  pair_t(int a, int b) : x(a), y(b) {}
  int x;
  int y;
};
REFLECTION(pair_t, x, y);

int main() {
    auto t = iguana::create_instance("pair_t");
t->set_field_value("x", 12);
t->set_field_value("y", 24);

auto &r0 = t->get_field_value<int>("x");
CHECK(r0 == 12);
auto &r = t->get_field_value<int>("y");
CHECK(r == 24);

//序列化到protobuf数据格式
std::string str;
t->to_pb(str);

//从protobuf 格式反序列化到pair_t
pair_t s;
s.from_pb(str);

CHECK(s.x == 12);
CHECK(s.y == 24);

// 序列化到json
std::string json;
t->to_json(str);

s = {};
s.from_json(json);
CHECK(s.x == 12);
CHECK(s.y == 24);

// 序列化到xml
std::string xml;
t->to_xml(xml);
s.from_xml(xml);

// 序列化到yaml
std::string yaml;
t->to_yaml(yaml);
s.from_yaml(yaml);
}