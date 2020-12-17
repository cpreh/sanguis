#ifndef SANGUIS_TILES_COLLECTION_REF_HPP_INCLUDED
#define SANGUIS_TILES_COLLECTION_REF_HPP_INCLUDED

#include <sanguis/tiles/collection_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace tiles
{

using
collection_ref
=
fcppt::reference<
	sanguis::tiles::collection
>;

}
}

#endif
