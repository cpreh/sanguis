#ifndef SANGUIS_LOAD_MODEL_PART_RESULT_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_RESULT_HPP_INCLUDED

#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/part_map.hpp>
#include <sanguis/load/model/part_result_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
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
		sanguis::load::model::cell_size const &,
		sanguis::load::model::part_map &&
	);

	part_result(
		part_result &&
	);

	part_result &
	operator=(
		part_result &&
	) = delete;

	~part_result();

	sanguis::load::model::cell_size const &
	cell_size() const;

	sanguis::load::model::part_map const &
	parts() const;
private:
	sanguis::load::model::cell_size cell_size_;

	sanguis::load::model::part_map parts_;
};

}
}
}

#endif
