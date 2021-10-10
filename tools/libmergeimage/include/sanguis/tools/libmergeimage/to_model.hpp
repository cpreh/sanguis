#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_TO_MODEL_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_TO_MODEL_HPP_INCLUDED

#include <sanguis/model/cell_size_fwd.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>

namespace sanguis::tools::libmergeimage
{

SANGUIS_TOOLS_LIBMERGEIMAGE_SYMBOL
sanguis::model::object to_model(
    sanguis::model::cell_size const &, sanguis::tools::libmergeimage::saved_image_vector const &);

}

#endif
