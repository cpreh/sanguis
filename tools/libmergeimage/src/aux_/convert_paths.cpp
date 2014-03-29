#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/path_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/convert_paths.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/tree_depth.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::path_vector
sanguis::tools::libmergeimage::aux_::convert_paths(
	sanguis::tools::libmergeimage::aux_::path_vector const &_paths
)
{
	return
		fcppt::algorithm::map<
			sanguis::tools::libmergeimage::path_vector
		>(
			_paths,
			[](
				boost::filesystem::path const &_path
			)
			{
				sanguis::tools::libmergeimage::path result;

				// TODO: Is there a better way to express this?

				for(
					boost::filesystem::path const &elem
					:
					_path
				)
				{
					if(
						result.size()
						==
						sanguis::tools::libmergeimage::aux_::tree_depth::value
					)
						break;

					result.push_back(
						fcppt::filesystem::path_to_string(
							elem
						)
					);
				}

				return
					result;
			}
		);
}
