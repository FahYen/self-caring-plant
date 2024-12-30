set(srcs "CameraStream.c"
            "connect_wifi.c")
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS ".")
