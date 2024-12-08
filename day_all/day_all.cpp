#include <cctype>
#include <iostream>
#include <iomanip> // E.g., std::quoted
#include <string>
#include <string_view>
#include <sstream> // E.g., std::istringstream, std::ostringstream
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <ranges> // E.g., std::subrange, std::view
#include <utility> // E.g., std::pair,..
#include <algorithm> // E.g., std::find, std::all_of,...
#include <numeric> // E.g., std::accumulate
#include <limits> // E.g., std::numeric_limits
#include <fstream>
#include <format>
#include <optional>
#include <regex>
#include <filesystem>

// Try to read the path to teh actual working directory
// from a text file at the location where we execute
std::optional<std::filesystem::path> get_working_dir() {
  std::optional<std::filesystem::path> result{};
    
  std::ifstream workingDirFile("working_dir.txt");

  std::string workingDir;
  std::getline(workingDirFile, workingDir); // Read the directory path
  std::filesystem::path dirPath{workingDir};

  if (std::filesystem::exists(dirPath) and std::filesystem::is_directory(dirPath)) {
    // Return the directory path as a std::filesystem::path
    result = std::filesystem::path(workingDir);
  }
  return result;
}

auto const NL = "\n";
auto const T = "\t";
auto const NT = "\n\t";

using Integer = int64_t; // 16 bit int: 3.27 x 10^4, 32 bit int: 2.14 x 10^9, 64 bit int: 9.22 x 10^18
using Result = Integer;
using Model = std::vector<std::string>;

namespace parsing {
  class Splitter {
  public:
    Splitter(std::string const& s) : m_s{s} {}
    Splitter(std::istream& is) : m_s{
       std::istreambuf_iterator<char>(is)
      ,std::istreambuf_iterator<char>()
    } {};
    std::vector<Splitter> lines() const {
      std::vector<Splitter> result{};
      std::istringstream is{m_s};
      std::string line{};
      while (std::getline(is,line)) result.push_back(line);
      return result;
    }
    std::pair<Splitter,Splitter> split(char ch) const {
      std::size_t pos = m_s.find(ch);
      if (pos == std::string::npos) {
        return {m_s, std::string{}};
      }
      return {m_s.substr(0, pos), m_s.substr(pos + 1)};
    }
    std::vector<Splitter> splits(char sep) const {
      std::vector<Splitter> result{};
      std::istringstream is{m_s};
      std::string line{};
      while (std::getline(is, line, sep)) {
        result.push_back(line);
      }
      return result;
    }
    Splitter trim() {
        auto start = std::find_if_not(m_s.begin(), m_s.end(), ::isspace);
        auto end = std::find_if_not(m_s.rbegin(), m_s.rend(), ::isspace).base();
        return std::string(start, end);
    }
    std::vector<Splitter> groups(std::string const& regexPattern) {
        std::vector<Splitter> result;
        std::regex pattern(regexPattern);
        std::smatch matches;

        if (std::regex_search(m_s, matches, pattern)) {
            // Iterate over the captured groups (start from 1, as 0 is the whole match)
            for (size_t i = 1; i < matches.size(); ++i) {
                result.push_back(matches[i].str());
            }
        }
        return result;
    }

    std::string const& str() const {return m_s;}
    operator std::string() const {return m_s;}
    auto size() const {return m_s.size();}
  private:
    std::string m_s{};
  };
}

Model parse(auto& in,int day) {
  using namespace parsing;
  Model result{};
  auto input = Splitter{in};
  auto lines = input.lines();
  if (lines.size()>1) {
    std::cout << NL << T << lines.size() << " lines";
    for (int i=0;i<lines.size() and i<5;++i) {
      auto line = lines[i];
      std::cout << NL << T << T << "line[" << i << "]:" << line.size() << " " << std::quoted(line.str());
      if (day==3) {
        /*
         #1 @ 850,301: 23x12
         #2 @ 898,245: 15x10
         #3 @ 8,408: 12x27
         */
        auto args = line.groups(R"(\#(\d+)\s@\s(\d+),(\d+):\s(\d+)x(\d+))");
        for (auto arg : args) {
          std::cout << NL << T << T << std::quoted(arg.str());
        }
      }
    }
  }
  else {
    // single line
    auto [left,right] = input.split(';');
    if (left.size()>0 and right.size()>0) {
      std::cout << NL << T << "left:" << std::quoted(left.str());
      auto l_tokens = left.splits(' ');
      for (auto const& token : l_tokens) {
        std::cout << NL << T << T << std::quoted(token.str());
      }
      std::cout << NL << T << "right:" << std::quoted(right.str());
      auto r_tokens = right.splits(' ');
      for (auto const& token : r_tokens) {
        std::cout << NL << T << T << std::quoted(token.str());
      }
    }
  }
  return result;
}

Model parse(auto& in) {
  using namespace parsing;
  std::cout << "\n<BEGIN parse>";
  Model result{};
  std::string line{};
  int count{};
  auto lines = Splitter{in}.lines();
  for (auto const& line : lines) {
    std::cout << "\nLine[" << count++ << "]:" << " " << std::quoted(line.str()) << ":" << line.size();
    result.push_back(line);
  }
  std::cout << "\n<END parse>";
  return result;
}

using Args = std::vector<std::string>;

namespace part1 {
  std::optional<Result> solve_for(std::istream& in,Args const& args) {
    std::optional<Result> result{};
    std::cout << NL << NL << "part1";
    if (in) {
      auto model = parse(in);
    }
    return result;
  }
}

namespace part2 {
  std::optional<Result> solve_for(std::istream& in,Args const& args) {
    std::optional<Result> result{};
    std::cout << NL << NL << "part2";
    if (in) {
      auto model = parse(in);
    }
    return result;
  }
}

using Answers = std::vector<std::pair<std::string,std::optional<Result>>>;
int main(int argc, char *argv[]) {
  Args args{};
  for (int i=0;i<argc;++i) {
    args.push_back(argv[i]);    
  }
  std::filesystem::path working_dir{};
  if (auto dir = get_working_dir()) {
    working_dir = *dir;
  }
  else {
    std::cout << NL << "No working directory path configured";
  }
  std::cout << NL << "Using working_dir " << working_dir;
  for (int day = 1; day <= 25; ++day) {
    std::string fileName = std::format("puzzle_day_{}.txt", day);
    std::filesystem::path file{working_dir / fileName};
    std::ifstream in(file);
    if (!in) {
        std::cerr << NL << "Error: Could not open file " << file;
        continue;
    }
    std::cout << NL << "Parsing file: " << file;
    parse(in,day);
  }

  Answers answers{};
  std::vector<std::chrono::time_point<std::chrono::system_clock>> exec_times{};
  exec_times.push_back(std::chrono::system_clock::now());
    std::vector<int> states = {}; // Disabled
//  std::vector<int> states = {0};
//  std::vector<int> states = {0,1};
//  std::vector<int> states = {2};
//  std::vector<int> states = {2,3};
//  std::vector<int> states = {0,1,2,3};
  for (auto state : states) {
    switch (state) {
      case 0: {
        std::filesystem::path file{"../../example.txt"};
        std::ifstream in{file};
        if (in) answers.push_back({"Part 1 Example",part1::solve_for(in,args)});
        else std::cerr << "\nSORRY, no file " << file;
        exec_times.push_back(std::chrono::system_clock::now());
      } break;
      case 1: {
        std::filesystem::path file{"../../puzzle.txt"};
        std::ifstream in{file};
        if (in) answers.push_back({"Part 1     ",part1::solve_for(in,args)});
        else std::cerr << "\nSORRY, no file " << file;
        exec_times.push_back(std::chrono::system_clock::now());
      } break;
      case 2: {
        std::filesystem::path file{"../../example.txt"};
        std::ifstream in{file};
        if (in) answers.push_back({"Part 2 Example",part2::solve_for(in,args)});
        else std::cerr << "\nSORRY, no file " << file;
        exec_times.push_back(std::chrono::system_clock::now());
      } break;
      case 3: {
        std::filesystem::path file{"../../puzzle.txt"};
        std::ifstream in{file};
        if (in) answers.push_back({"Part 2     ",part2::solve_for(in,args)});
        else std::cerr << "\nSORRY, no file " << file;
        exec_times.push_back(std::chrono::system_clock::now());
      } break;
      default:{std::cerr << "\nSORRY, no action for state " << state;} break;
    }
  }
  
  std::cout << "\n\nANSWERS";
  for (int i=0;i<answers.size();++i) {
    std::cout << "\nduration:" << std::chrono::duration_cast<std::chrono::milliseconds>(exec_times[i+1] - exec_times[i]).count() << "ms";
    std::cout << " answer[" << answers[i].first << "] ";
    if (answers[i].second) std::cout << *answers[i].second;
    else std::cout << "NO OPERATION";
  }
  std::cout << "\n";
  /*
  For my input:
  ANSWERS
   ...
  */
  return 0;
}
