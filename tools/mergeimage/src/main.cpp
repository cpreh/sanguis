#include <sanguis/model/object.hpp>
#include <sanguis/tools/libmergeimage/merge_paths.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char **argv
)
try
{
	if(
		argc != 2
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Usage: ")
			<< argv[0]
			<< FCPPT_TEXT(" <path>\n");

		return
			EXIT_FAILURE;
	}

	sanguis::model::object const result(
		sanguis::tools::libmergeimage::merge_paths(
			boost::filesystem::path(
				argv[1]
			)
		)
	);

	return
		EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return
		EXIT_FAILURE;
}
