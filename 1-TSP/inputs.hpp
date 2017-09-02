#ifndef INPUTS
#define INPUTS

void get_test_input(vector<Point> *input);

// void get_test_input(vector<string> * input) {
//   (*input).push_back("95.0129 61.5432");
//   (*input).push_back("23.1139 79.1937");
//   (*input).push_back("60.6843 92.1813");
//   (*input).push_back("48.5982 73.8207");
//   (*input).push_back("89.1299 17.6266");
//   (*input).push_back("76.2097 40.5706");
//   (*input).push_back("45.6468 93.5470");
//   (*input).push_back("1.8504 91.6904");
//   (*input).push_back("82.1407 41.0270");
//   (*input).push_back("44.4703 89.3650");
// }

void get_test_input(vector<Point> *input) {
  (*input).push_back(Point("95.0129 61.5432"));
  (*input).push_back(Point("23.1139 79.1937"));
  (*input).push_back(Point("60.6843 92.1813"));
  (*input).push_back(Point("48.5982 73.8207"));
  (*input).push_back(Point("89.1299 17.6266"));
  (*input).push_back(Point("76.2097 40.5706"));
  (*input).push_back(Point("45.6468 93.5470"));
  (*input).push_back(Point("1.8504  91.6904"));
  (*input).push_back(Point("82.1407 41.0270"));
  (*input).push_back(Point("44.4703 89.3650"));
}

#endif
