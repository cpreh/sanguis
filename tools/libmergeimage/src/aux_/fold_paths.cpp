#include <sanguis/tools/libmergeimage/path_count_pair.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/convert_path.hpp>
#include <sanguis/tools/libmergeimage/aux_/fold_paths.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/tree_depth.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::path_count_pair_vector
sanguis::tools::libmergeimage::aux_::fold_paths(
	sanguis::tools::libmergeimage::aux_::path_vector const &_paths
)
{
	sanguis::tools::libmergeimage::path_count_pair_vector result;

	// TODO: Is there a better way to express this?
	auto const mismatch(
		[](
			sanguis::tools::libmergeimage::aux_::path_vector::const_iterator const _begin,
			sanguis::tools::libmergeimage::aux_::path_vector::const_iterator const _end
		)
		{
			if(
				_begin
				==
				_end
			)
				return
					_end;

			boost::filesystem::path const &path1(
				*_begin
			);

			return
				std::find_if(
					std::next(
						_begin
					),
					_end,
					[
						&path1
					](
						boost::filesystem::path const &_path2
					)
					{
						return
							!std::equal(
								path1.begin(),
								std::next(
									path1.begin(),
									sanguis::tools::libmergeimage::aux_::tree_depth::value
								),
								_path2.begin()
							);
					}
				);
		}
	);

	for(
		sanguis::tools::libmergeimage::aux_::path_vector::const_iterator
			cur(
				_paths.begin()
			),
			next(
				mismatch(
					cur,
					_paths.end()
				)
			);
		cur != _paths.end();
		cur = next,
		next =
			mismatch(
				cur,
				_paths.end()
			)
	)
		result.push_back(
			sanguis::tools::libmergeimage::path_count_pair(
				sanguis::tools::libmergeimage::aux_::convert_path(
					*cur
				),
				fcppt::cast::to_unsigned(
					std::distance(
						cur,
						next
					)
				)
			)
		);

	return
		result;
}
