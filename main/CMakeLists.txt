set(EXTRA_COMPONENT_DIRS src)

set(SOURCES ./src/main.c
./src/bt_avrc.c
./src/bt_a2dp.c
./src/bt_gap.c
./src/spiffs_wav.c)

idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS . inc)