#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sanguis/tools/libmergeimage/impl/count_maximum.hpp>
#include <sanguis/tools/libmergeimage/impl/merge_paths.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/join.hpp>

// This algorithm takes a container of path_vectors so that it may
// be called multiple times when merging a tree. Currently, this isn't done,
// however.
sanguis::tools::libmergeimage::impl::path_vector_vector
sanguis::tools::libmergeimage::impl::merge_paths(
    sanguis::tools::libmergeimage::impl::path_vector_vector const &_elements,
    sanguis::tools::libmergeimage::impl::count_maximum const _maximum)
{
  // Given a tuple of integers and an upper bound b, we want to
  // accumulate as many integers as possible such that their sum doesn't
  // exceed b but gets as close as possible. This problem is NP-complete.
  // However, if we are satisfied with the sum being at least b/2, then this
  // problem is solvable in P as follows:
  // Let the tuple of integers given be I=(i_1, ..., i_n), such that i_j
  // <= b (1 <= j <= n). Remove all integers from I that are greater than b/2,
  // leaving a new integer set J=(j_1, ..., j_m).
  // Take M=(j_1, ..., j_x) such that \sum_{i=1}{x}j_x is not greater
  // than b, and set J to (j_{x+1}, ..., j_m). It can be shown that
  // either x=m or the sum of M is at least b/2. By repeating this
  // process, we get a set of integer tuples such that every tuple's sum
  // is at least b/2 except for the last.

  sanguis::tools::libmergeimage::count_type const half(_maximum.get() / 2);

  sanguis::tools::libmergeimage::impl::path_vector_vector result;

  sanguis::tools::libmergeimage::impl::path_vector accum;

  auto const cost([](sanguis::tools::libmergeimage::impl::path_vector const &_vector)
                  { return _vector.size(); });

  // TODO(philipp): Use filter here
  for (sanguis::tools::libmergeimage::impl::path_vector const &element : _elements)
  {
    if (cost(element) > _maximum.get())
    {
      throw
          // TODO(philipp): Better error message
          sanguis::tools::libmergeimage::exception(FCPPT_TEXT("Cost of node too high"));
    }
    if (cost(element) > half)
    {
      result.push_back(element);
    }
  }

  // TODO(philipp): Maybe use filter and fold?

  for (sanguis::tools::libmergeimage::impl::path_vector const &element : _elements)
  {
    if (cost(element) > half)
    {
      continue;
    }

    if (cost(accum) + cost(element) > _maximum.get())
    {
      result.push_back(accum);

      accum.clear();
    }

    accum = fcppt::container::join(std::move(accum), element);
  }

  // Left over elements
  if (!accum.empty())
  {
    result.push_back(accum);
  }

  return result;
}
