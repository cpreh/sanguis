#ifndef SANGUIS_LOAD_SKIP_DIRECTORIES_HPP_INCLUDED
#define SANGUIS_LOAD_SKIP_DIRECTORIES_HPP_INCLUDED

#include <fcppt/filesystem/directory_iterator.hpp>


namespace sanguis
{
namespace load
{

fcppt::filesystem::directory_iterator const
skip_directories(
	fcppt::filesystem::directory_iterator
);

}
}

#endif
