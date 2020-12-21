#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_CREF_HPP_INCLUDED

#include <sanguis/client/load/model/part_fwd.hpp>
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
part_cref
=
fcppt::reference<
	sanguis::client::load::model::part const
>;

}
}
}
}

#endif
