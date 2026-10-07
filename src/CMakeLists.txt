zephyr_library()
zephyr_library_include_directories(.)
zephyr_library_include_directories(${ZEPHYR_CURRENT_MODULE_DIR}/include)
zephyr_include_directories(${ZEPHYR_CURRENT_MODULE_DIR}/include)

# Packaging. Do not add device functions to these files.
zephyr_library_sources(eyestar.c)

zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_BACKEND_HARDWARE hardware_transfer.c)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_BACKEND_LIBRARY_MOCK lib_mock_transfer.c)

# Device API: mock xor library, same symbols (eyestar_init, …).
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_BACKEND_PUBLIC_MOCK
			     ${ZEPHYR_CURRENT_MODULE_DIR}/mock/eyestar.c)

set(eyestar_LIB ${ZEPHYR_CURRENT_MODULE_DIR}/lib)

if(CONFIG_PEROVSAT_EYESTAR_BACKEND_HARDWARE OR CONFIG_PEROVSAT_EYESTAR_BACKEND_LIBRARY_MOCK)
	zephyr_library_include_directories(${eyestar_LIB})
	zephyr_library_sources(${eyestar_LIB}/eyestar.c)
endif()
