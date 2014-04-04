#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/aux_/convert_path.hpp>
#include <sanguis/tools/libmergeimage/aux_/tree_depth.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::path
sanguis::tools::libmergeimage::aux_::convert_path(
	boost::filesystem::path const &_path
)
{
	// TODO: Is there a better way to express this?

	sanguis::tools::libmergeimage::path result;

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
