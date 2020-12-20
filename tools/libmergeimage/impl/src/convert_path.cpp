#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/impl/convert_path.hpp>
#include <sanguis/tools/libmergeimage/impl/tree_depth.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::path
sanguis::tools::libmergeimage::impl::convert_path(
	std::filesystem::path const &_path
)
{
	sanguis::tools::libmergeimage::path result{};

	for(
		std::filesystem::path const &elem
		:
		_path
	)
	{
		if(
			result.size()
			==
			sanguis::tools::libmergeimage::impl::tree_depth::value
		)
		{
			break;
		}

		result.push_back(
			fcppt::filesystem::path_to_string(
				elem
			)
		);
	}

	return
		result;
}
