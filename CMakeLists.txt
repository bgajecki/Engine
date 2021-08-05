
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Entity ENTITY)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Entity/Sublibrary SUBLIBRARY)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Process PROCESS)

set (ENGINE_SRCS
	${ENTITY}
	${SUBLIBRARY}
	${PROCESS}
	PARENT_SCOPE
)