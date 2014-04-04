#include <sanguis/tools/libmergeimage/aux_/gather_paths.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/tree_depth.hpp>
#include <fcppt/filesystem/strip_prefix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::aux_::path_vector_vector
sanguis::tools::libmergeimage::aux_::gather_paths(
	boost::filesystem::path const &_base_path
)
{
	sanguis::tools::libmergeimage::aux_::path_vector_vector result;

	for(
		boost::filesystem::recursive_directory_iterator it(
			_base_path
		);
		it != boost::filesystem::recursive_directory_iterator();
		++it
	)
	{
		if(
			it.level()
			==
			sanguis::tools::libmergeimage::aux_::tree_depth::value - 1
			&&
			!it.no_push_pending()
		)
		{
			it.no_push(
				true
			);

			sanguis::tools::libmergeimage::aux_::path_vector temp;

			for(
				boost::filesystem::path const &path
				:
				boost::make_iterator_range(
					boost::filesystem::directory_iterator(
						*it
					),
					boost::filesystem::directory_iterator()
				)
			)
				temp.push_back(
					fcppt::filesystem::strip_prefix(
						_base_path,
						path
					)
				);

			result.push_back(
				temp
			);
		}
	}

	return
		result;
}