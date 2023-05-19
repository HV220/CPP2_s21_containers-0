#ifndef SRC_TESTS_HEADERS_PRESIDENTTEST_H_
#define SRC_TESTS_HEADERS_PRESIDENTTEST_H_

struct President {
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year)
      : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {}
  President(President &&other)
      : name(std::move(other.name)), country(std::move(other.country)),
        year(other.year) {}
  President &operator=(const President &other) = default;
};

#endif //  SRC_TESTS_HEADERS_PRESIDENTTEST_H_