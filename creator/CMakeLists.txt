INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

SET(
	SANGUIS_CREATOR_INCLUDE_FILES
	include/sanguis/creator/generator/car_park.hpp
	include/sanguis/creator/generator/opening.hpp
	include/sanguis/creator/generator/opening_container.hpp
	include/sanguis/creator/generator/parameters.hpp
	include/sanguis/creator/generator/parameters_fwd.hpp
	include/sanguis/creator/generator/randgen.hpp
	include/sanguis/creator/generator/randgen_fwd.hpp
	include/sanguis/creator/generator/randvalue.hpp
	include/sanguis/creator/generator/result.hpp
	include/sanguis/creator/generator/result_fwd.hpp
	include/sanguis/creator/generator/seed.hpp
	include/sanguis/creator/geometry/polygon.hpp
	include/sanguis/creator/geometry/rect.hpp
	include/sanguis/creator/geometry/shape.hpp
	include/sanguis/creator/geometry/shape_container.hpp
	include/sanguis/creator/geometry/shape_fwd.hpp
	include/sanguis/creator/geometry/solidity.hpp
	include/sanguis/creator/geometry/texture_name.hpp
	include/sanguis/creator/geometry/texture_point.hpp
	include/sanguis/creator/geometry/texture_unit.hpp
	include/sanguis/creator/geometry/unit.hpp
	include/sanguis/creator/geometry/vector.hpp
	include/sanguis/creator/geometry/vertex.hpp
	include/sanguis/creator/geometry/vertex_fwd.hpp
	include/sanguis/creator/symbol.hpp
)

SET(
	SANGUIS_CREATOR_SRC_FILES
	src/generator/car_park.cpp
	src/generator/parameters.cpp
	src/generator/randgen.cpp
	src/generator/result.cpp
	src/geometry/shape.cpp
	src/geometry/vertex.cpp
)

SET(
	SANGUIS_CREATOR_FILES
	"${SANGUIS_CREATOR_INCLUDE_FILES};${SANGUIS_CREATOR_SRC_FILES}"
)

FCPPT_UTILS_ADD_SOURCE_GROUPS(
	"${SANGUIS_CREATOR_FILES}"
)

ADD_LIBRARY(
	sanguiscreator
	SHARED
	${SANGUIS_CREATOR_FILES}
)
