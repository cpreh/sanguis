#ifndef SANGUIS_LOAD_FIRST_FILE_HPP_INCLUDED
#define SANGUIS_LOAD_FIRST_FILE_HPP_INCLUDED

#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sanguis
{
namespace load
{

fcppt::filesystem::directory_iterator const
first_file(
	fcppt::filesystem::path const &
);

}
}

#endif
