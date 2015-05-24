#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/load/model/part_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

typedef
fcppt::unique_ptr<
	sanguis::client::load::model::part
>
part_unique_ptr;

}
}
}
}

#endif
