install : build
	R CMD INSTALL $(CONFIG_ARGS) MPIHelloWorld_*.tar.gz

build :
	rm -f MPIHelloWorld_*.tar.gz
	R CMD build --no-build-vignettes package

configure_script :
	autoconf package/configure.ac > package/configure
	rm -rf autom4te.cache

set_compiler_gcc :
	@printf "CC=ccache gcc\nCXX=ccache g++\n" > ~/.R/Makevars

set_compiler_clang :
	@printf "CC=ccache clang\nCXX=ccache clang++\n" > ~/.R/Makevars

docs : RcppInterface
	Rscript generateDocs.R

RcppInterface : 
	Rscript compileAttributes.R
