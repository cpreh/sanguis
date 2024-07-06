fcppt_utils_load_source_files(tiles/files.txt SANGUIS_TILES_FILES)

sanguis_add_library(
  tiles
  "${SANGUIS_TILES_FILES}"
  HAS_IMPL_DIR
  DEPS
  ${sanguis_common_TARGET}
  ${sanguis_core_TARGET}
  ${sanguis_creator_TARGET}
  ${sanguis_model_TARGET}
  ${sgecharconv_TARGET}
  ${sgeimage2d_TARGET}
  ${sgeimagecolor_TARGET}
  ${sgeparsejson_TARGET}
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_DEPS
  sanguis_creator_interface
  sgeimage2d_interface
  fcppt_core_interface
  fcppt_log_interface
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES})
