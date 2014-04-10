#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_RESULT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_RESULT_HPP_INCLUDED

#include <sanguis/client/load/model/part_map.hpp>
#include <sanguis/client/load/model/part_result_fwd.hpp>
#include <sanguis/model/cell_size.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

class part_result
{
	FCPPT_NONCOPYABLE(
		part_result
	);
public:
	part_result(
		sanguis::model::cell_size const &,
		sanguis::client::load::model::part_map &&
	);

	part_result(
		part_result &&
	);

	part_result &
	operator=(
		part_result &&
	) = delete;

	~part_result();

	sanguis::model::cell_size const &
	cell_size() const;

	sanguis::client::load::model::part_map const &
	parts() const;
private:
	sanguis::model::cell_size cell_size_;

	sanguis::client::load::model::part_map parts_;
};

}
}
}
}

#endif
