#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/path_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

fcppt::string
sanguis::tools::libmergeimage::path_to_string(sanguis::tools::libmergeimage::path const &_path)
{
  fcppt::string result{};

  for (fcppt::string const &element : _path)
  {
    result += element + FCPPT_TEXT('/');
  }

  return result;
}
