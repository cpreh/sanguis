#ifndef SANGUIS_LOAD_FIRST_FILE_HPP_INCLUDED
#define SANGUIS_LOAD_FIRST_FILE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{

boost::filesystem::directory_iterator const
first_file(
	boost::filesystem::path const &
);

}
}

#endif
