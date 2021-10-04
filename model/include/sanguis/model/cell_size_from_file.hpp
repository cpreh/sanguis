#ifndef SANGUIS_MODEL_CELL_SIZE_FROM_FILE_HPP_INCLUDED
#define SANGUIS_MODEL_CELL_SIZE_FROM_FILE_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis::model
{

SANGUIS_MODEL_SYMBOL
sanguis::model::cell_size
cell_size_from_file(
	std::filesystem::path const &
);

}

#endif
