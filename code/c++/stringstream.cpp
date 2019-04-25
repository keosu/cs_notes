#include <fstream>
#include <functional>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <tuple>

using namespace std;
using namespace cv;

#include <functional>
#include <iostream>

vector<tuple<string, Mat&, float>> vec;

int main(int argc, char** argv) {
  string path = "x.txt";

  fstream f(path);
  if (f.fail()) {
    fprintf(stderr, "Error opening file %s\n", path.c_str());
    exit(1);
  }
  string line;
  string name;
  float prob;
  while (getline(f, line)) {
    stringstream ss(line);
    ss >> name >> prob;
    cout << "name: " << name << ", prob: " << prob << endl;
    Mat img = imread("cat.png");
    cout << "image size: " << img.size() << endl;
    vec.emplace_back(name, ref(img), prob);
  }

  for (auto ele : vec) {
    cout << get<0>(ele) << " , " << get<1>(ele) << " , " << get<2>(ele) << endl;
  }

  return 0;
}