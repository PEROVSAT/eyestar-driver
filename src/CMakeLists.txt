zephyr_library()
zephyr_library_include_directories(.)
zephyr_include_directories(.)
zephyr_library_sources(eyestar_s4.c)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_HARDWARE hardware_transfer.c)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_SIMULATION simulation_transfer.c)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_LIBRARY_MOCK lib_mock_transfer.c)
set(eyestar_s4_LIB ${ZEPHYR_CURRENT_MODULE_DIR}/lib)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_HARDWARE
			     ${eyestar_s4_LIB}/eyestar_s4_lib.c)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_SIMULATION
			     ${eyestar_s4_LIB}/eyestar_s4_lib.c)
zephyr_library_sources_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_LIBRARY_MOCK
			     ${eyestar_s4_LIB}/eyestar_s4_lib.c)
zephyr_include_directories_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_HARDWARE     ${eyestar_s4_LIB})
zephyr_include_directories_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_SIMULATION   ${eyestar_s4_LIB})
zephyr_include_directories_ifdef(CONFIG_PEROVSAT_EYESTAR_S4_BACKEND_LIBRARY_MOCK ${eyestar_s4_LIB})
