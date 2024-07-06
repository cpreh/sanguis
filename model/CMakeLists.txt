fcppt_utils_load_source_files(model/files.txt SANGUIS_MODEL_FILES)

sanguis_add_library(
  model
  "${SANGUIS_MODEL_FILES}"
  HAS_IMPL_DIR
  DEPS
  ${sgecharconv_TARGET}
  ${sgeparse_TARGET}
  ${sgeparsejson_TARGET}
  ${fcppt_core_TARGET}
  ${fcppt_filesystem_TARGET}
  ${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
  TRANSITIVE_DEPS
  fcppt_core_interface)
