project(pearls_lib)

set(HEADER_FILES
        Bitvector.cpp Bitvector.h)

set(SOURCE_FILES
        Bitvector.cpp
        Bitvector.h
        NumbersGenerator.cpp
        NumbersGenerator.h
        endianness.h
        endianness.cpp
        bitops.cpp
        bitops.h bitvector_sort.cpp bitvector_sort.h vector_shift.cpp vector_shift.h)

add_library(pearls_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
