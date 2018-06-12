# include macros
m4_builtin([include], m4/ax_check_compile_flag.m4)
m4_builtin([include], m4/ax_compiler_vendor.m4)
m4_builtin([include], m4/ax_compiler_version.m4)
m4_builtin([include], m4/ax_openmp.m4)

# get version of MPIHelloWorld from DESCRIPTION file
AC_INIT(MPIHelloWorld, m4_esyscmd_s([awk -e '/^Version:/ {print $2}' Repo/DESCRIPTION]))

# get C++ compiler from R configuration
CXX=`"${R_HOME}/bin/R" CMD config CXX`

# Switch to a C++ compiler, and check if it works.
AC_LANG(C++)
AC_REQUIRE_CPP
AC_PROG_CXX

# Check if compiling debug version
AC_ARG_ENABLE(debug, [AC_HELP_STRING([--enable-debug],
    [build debug version of MPIHelloWorld])], [build_debug=yes], [build_debug=no])

# Check if compiler warnings should be turned on
AC_ARG_ENABLE(warnings, [AC_HELP_STRING([--enable-warnings],
    [compile MPIHelloWorld with warning messages])], [warnings=yes], [warnings=no])

# Check if specific version of SIMD instructions requested
AC_ARG_ENABLE(simd, [AC_HELP_STRING([--enable-simd],
    [specify simd instruction set (sse, avx)])],
    [simd_version=$enableval], [simd_version=sse])

# default MPIHelloWorld specific flags
MPI_HW_CPP_FLAGS=" -DBOOST_MATH_PROMOTE_DOUBLE_POLICY=0 "
MPI_HW_CXX_FLAGS=
MPI_HW_LIBS=

# get compiler info
AX_COMPILER_VENDOR
AX_COMPILER_VERSION
AX_OPENMP

# set openmp flags
MPI_HW_CXX_FLAGS+=" $OPENMP_CXXFLAGS "
MPI_HW_LIBS+=" $OPENMP_CXXFLAGS "

echo "building on $ax_cv_cxx_compiler_vendor compiler version $ax_cv_cxx_compiler_version"

# set compile flags for debug build
if test "x$build_debug" = "xyes" ; then
    echo "Building Debug Version of MPIHelloWorld"
    MPI_HW_CPP_FLAGS+=" -DMPI_HW_DEBUG "
fi

# set compile flags if warnings enabled
if test "x$warnings" = "xyes" ; then
    AX_CHECK_COMPILE_FLAG([-Wall], [MPI_HW_CXX_FLAGS+=" -Wall "])
    AX_CHECK_COMPILE_FLAG([-Wextra], [MPI_HW_CXX_FLAGS+=" -Wextra "])
    AX_CHECK_COMPILE_FLAG([-Werror], [MPI_HW_CXX_FLAGS+=" -Werror "])
    AX_CHECK_COMPILE_FLAG([-Wno-unused-parameter], [MPI_HW_CXX_FLAGS+=" -Wno-unused-parameter "])
    AX_CHECK_COMPILE_FLAG([-Wno-unused-function], [MPI_HW_CXX_FLAGS+=" -Wno-unused-function "])
fi

# set compile flags for SIMD
if test "x$simd_version" = "xsse" ; then
    echo "Compiling with SSE instructions"
    AX_CHECK_COMPILE_FLAG([-msse4.2], [MPI_HW_CXX_FLAGS+=" -msse4.2 "])
elif test "x$simd_version" = "xyes" ; then
    echo "Compiling with SSE instructions"
    AX_CHECK_COMPILE_FLAG([-msse4.2], [MPI_HW_CXX_FLAGS+=" -msse4.2 "])
elif test "x$simd_version" = "xavx" ; then
    echo "Compiling with AVX instructions"
    AX_CHECK_COMPILE_FLAG([-mavx], [MPI_HW_CXX_FLAGS+=" -mavx "])    
elif test "x$simd_version" = "xno" ; then
    echo "Compiling without SIMD instructions"
else
    echo "Error: Invalid SIMD type"
    exit -1
fi

# export variables containing flags
AC_SUBST(MPI_HW_CPP_FLAGS)
AC_SUBST(MPI_HW_CXX_FLAGS)
AC_SUBST(MPI_HW_LIBS)

# create makefile, output configure file
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

