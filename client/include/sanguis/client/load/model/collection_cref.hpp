#ifndef SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_COLLECTION_CREF_HPP_INCLUDED

#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

using
collection_cref
=
fcppt::reference<
	sanguis::client::load::model::collection const
>;

}
}
}
}

#endif
