#include <sanguis/tools/libmergeimage/path_count_pair.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/convert_path.hpp>
#include <sanguis/tools/libmergeimage/impl/fold_paths.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/tree_depth.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::path_count_pair_vector
sanguis::tools::libmergeimage::impl::fold_paths(
	sanguis::tools::libmergeimage::impl::path_vector const &_paths
)
{
	sanguis::tools::libmergeimage::path_count_pair_vector result;

	// TODO: Is there a better way to express this?
	auto const mismatch(
		[](
			sanguis::tools::libmergeimage::impl::path_vector::const_iterator const _begin,
			sanguis::tools::libmergeimage::impl::path_vector::const_iterator const _end
		)
		{
			return
				_begin
				==
				_end
				?
					_end
				:
					std::find_if(
						std::next(
							_begin
						),
						_end,
						[
							_begin
						](
							boost::filesystem::path const &_path2
						)
						{
							return
								!std::equal(
									_begin->begin(),
									std::next(
										_begin->begin(),
										sanguis::tools::libmergeimage::impl::tree_depth::value
									),
									_path2.begin()
								);
						}
					);
		}
	);

	for(
		sanguis::tools::libmergeimage::impl::path_vector::const_iterator
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
				sanguis::tools::libmergeimage::impl::convert_path(
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
