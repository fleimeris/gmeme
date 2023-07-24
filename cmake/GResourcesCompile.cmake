function (CompileGResources)
    find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

    set(GRESOURCE_C ${CMAKE_CURRENT_SOURCE_DIR}/src/gmeme.resource.c)
    set(GRESOURCE_XML gmeme.gresource.xml)

    add_custom_command (
            OUTPUT ${GRESOURCE_C}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
            COMMAND ${GLIB_COMPILE_RESOURCES} --generate-source --target=${GRESOURCE_C} ${GRESOURCE_XML}
    )

    set(GRESOURCE_C ${GRESOURCE_C} PARENT_SCOPE)
endfunction ()
