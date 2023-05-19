#ifndef SRC_TESTS_HEADERS_UNIVERSITYTEST_H_
#define SRC_TESTS_HEADERS_UNIVERSITYTEST_H_

#include <string>
#include <utility>

struct UniversityTest {
public:
  std::string professor;
  std::string student;

  UniversityTest() : professor("test"), student("test") {}
  UniversityTest(std::string p_professor, std::string p_student)
      : professor(std::move(p_professor)), student(std::move(p_student)) {}
  UniversityTest &operator=(const UniversityTest &other) = default;
};

#endif //  SRC_TESTS_HEADERS_UNIVERSITYTEST_H_