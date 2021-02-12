#project name = Liasteria API = LAPI

################ option ###################

projectopt	=
debug 		=
prefixdebug =
apiname 	= lapi
version 	= _0.2

ifdef debugmode
debug 		+= -g -ggdb
projectopt 	+= 
prefixdebug = _dbg
lapiname 	= $(apiname)$(version)$(prefixdebug)
else
lapiname 	= $(apiname)$(version)
endif

exe 		= $(lapiname)
stripexe	= $(lapiname)_strip

library		= -lstdc++ -lcomctl32 -lkernel32 -lcomdlg32 -luser32 -lgdi32
projectlib 	= -l:$(lapiname).a
win32opt	= -mwindows -municode 
lang 		= -x c++

I 			= -I$(d_include) -I$(d_project) -I$(d_build)
L 			= $(projectlib) $(library) -L$(d_include) -L$(d_project) -L$(d_temp) -L$(d_build)

opt 		= $(debug) -fno-exceptions -static -static-libgcc -static-libstdc++ $(projectopt) $(win32opt)

######
punt =,
prob =
space = $(prob) $(prob)
######
ifdef debugmode
searchcpp 		= $(strip $(notdir $(wildcard $(d_project)*.cpp)))
rnsufcpp 		= $(strip $(patsubst %.cpp, %$(prefixdebug).o, $(searchcpp)))
rnsufcppsub		= $(strip $(subst $(space),$(punt),$(strip $(rnsufcpp))))
modulecpp 		= $(strip $(notdir $(wildcard $(module)*.cpp)))
moduleobj 		= $(strip $(patsubst %.cpp, %$(prefixdebug).o, $(modulecpp)))
moduleobjsub	= $(strip $(subst $(space),$(punt),$(strip $(moduleobj))))
else
searchcpp 		= $(strip $(notdir $(wildcard $(d_project)*.cpp)))
rnsufcpp 		= $(strip $(patsubst %.cpp, %.o, $(searchcpp)))
rnsufcppsub		= $(strip $(subst $(space),$(punt),$(strip $(rnsufcpp))))
modulecpp 		= $(strip $(notdir $(wildcard $(module)*.cpp)))
moduleobj 		= $(strip $(patsubst %.cpp, %.o, $(modulecpp)))
moduleobjsub	= $(strip $(subst $(space),$(punt),$(strip $(moduleobj))))
endif

ifdef debugmode

else
endif

### вычисляемые переменные

objfileproject = $(call fn_FormatFileobj,$(d_project),*.cpp,)
objfileprojectform = $(strip $(subst $(space),$(punt),$(strip $(call fn_FormatFileobj,$(d_project),*.cpp,$(prefixdebug)))))
objfilewrap = $(call fn_FormatFileobj,$(d_wrap),*.cpp,)

####################################################################################################

test_test:
	$(call fn_Test)


# ifeq ($(call fn_GetFileCount,$(d_wrap),*.cpp),1)
	# @echo 1 file
# else
	# @echo $(call fn_GetFileCount,$(d_wrap),*.cpp)
# endif

all_make_api: compile_project compile_wrap linker
	@echo "end $@"

all_remake_api: del_all compile_project compile_wrap linker
	@echo "end $@"

del_all: del_temp del_build
	@echo "end $@"

del_temp:
	@rm -v -f -r $(d_temp)*.*

del_build:
	@rm -v -f -r $(d_build)*.*

compile_project: $(objfileproject)
	@$(ar) cr $(d_temp)$(lapiname).a $(d_temp){$(objfileprojectform)}
	@$(ranlib) $(d_temp)$(lapiname).a
	@cp $(d_temp)$(lapiname).a $(d_build)$(lapiname).a
	@echo "end $@"
#

$(objfileproject):
	$(if \
		$(strip $(findstring fn_true,$(call fn_GetStatusFile,$(d_project)$(strip $(patsubst %$(prefixdebug), %, $*)).cpp,$(d_temp)$*.o))),\
	@echo fn_true, \
	@echo compile $*;\
		$(CC) $(lang) -c $(d_project)$*.cpp -o $(d_temp)$*$(prefixdebug).o  $(I)\
	)

compile_wrap: $(objfilewrap)
	@echo "end $@"

$(objfilewrap):	
	$(if \
		$(strip $(findstring fn_true,$(call fn_GetStatusFile,$(d_wrap)$(strip $(patsubst %$(prefixdebug), %, $*)).cpp,$(d_temp)$*.o))),\
	@echo fn_true, \
	@echo compile $*;\
		$(CC) $(lang) -c $(d_wrap)$*.cpp -o $(d_temp)$*$(prefixdebug).o  $(I)\
	)

linker:
	$(CC) $(d_temp)$(objfilewrap)$(prefixdebug) -o $(d_build)$(lapiname).exe  $(I) $(L) $(opt)
	@echo "end $@"

#i686-w64-mingw32-gcc -c $(d_project)$*.cpp -o $(d_temp)$*.o -lstdc++ -lcomctl32 -lkernel32 -lcomdlg32 -luser32 -lgdi32 -static -static-libgcc -static-libstdc++ -mwindows -municode $(I)



#	$(if $(strip $(findstring fn_true,$(call fn_GetStatusFile,$(module)$(strip $(patsubst %_$(prefixdebug), %, $*)).cpp,$(temp)$*.o))),\
##	@echo -e "${GREEN} not rebuild module $* $(ECHO_DEF)",\
#	@echo -e "${YELLOW} rebuild module $* $(ECHO_DEF)";\
#	$(CC) $(lang) -c $(module)$(strip $(patsubst %_$(prefixdebug), %, $*)).cpp -o $(temp)$*.o $(I) $(opt))