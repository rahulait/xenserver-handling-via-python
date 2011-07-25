##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=VMUtil
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/VMUtil"
ProjectPath            := "/VMUtil"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=ubuntu1
Date                   :=Monday 25 July 2011
CodeLitePath           :="/home/ubuntu1/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
LinkOptions            :=  $(shell wx-config --debug=yes --libs --unicode=yes)
IncludePath            :=  "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/VMUtil$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/VMUtil$(ObjectSuffix): VMUtil.cpp $(IntermediateDirectory)/VMUtil$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/VMUtil/VMUtil.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/VMUtil$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VMUtil$(DependSuffix): VMUtil.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/VMUtil$(ObjectSuffix) -MF$(IntermediateDirectory)/VMUtil$(DependSuffix) -MM "/VMUtil/VMUtil.cpp"

$(IntermediateDirectory)/VMUtil$(PreprocessSuffix): VMUtil.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VMUtil$(PreprocessSuffix) "/VMUtil/VMUtil.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/VMUtil$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/VMUtil$(DependSuffix)
	$(RM) $(IntermediateDirectory)/VMUtil$(PreprocessSuffix)
	$(RM) $(OutputFile)


