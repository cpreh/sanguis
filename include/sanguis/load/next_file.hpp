#ifndef SANGUIS_LOAD_NEXT_FILE_HPP_INCLUDED
#define SANGUIS_LOAD_NEXT_FILE_HPP_INCLUDED

#include <fcppt/filesystem/directory_iterator.hpp>


namespace sanguis
{
namespace load
{

fcppt::filesystem::directory_iterator const
next_file(
	fcppt::filesystem::directory_iterator
);

}
}

#endif
