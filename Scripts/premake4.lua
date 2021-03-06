-- solution "Common" -- Name for the solution, we'll only use this one as a template so won't be generated because there's no projects inside it
	-- configurations { "Debug", "Release", "ReleaseCandidate" } -- List of all our build types
	-- platforms { "Native", "PS3" } -- Platforms, Native is Win32 in our case

	-- configuration{ "*" } -- Selects all possible configurations
		-- defines { "BOOST_ALL_NO_LIB" }

	-- configuration { "Debug" } -- Will select Win32 | Debug & PS3 | Debug in our case
		-- defines { "_DEBUG" }
		-- flags { "Symbols" } -- Debug symbols
		-- targetsuffix '_d' 
		
	-- configuration { "Release*" } -- Selects both Release & ReleaseCandidate
		-- defines { "NDEBUG", "_SECURE_SCL=0" }
		-- flags { "Optimize" } -- Optimization switches on

	-- configuration { "Native" } -- On Win32
		-- defines{ "WIN32" } -- Define WIN32

	-- configuration { "ReleaseCandidate" } -- All ReleaseCandidates needs a special define
		-- defines { "RELEASE_CANDIDATE" }
	
	-- outputDirectory = "Test"
	
	-- fileSet = 
    -- {
        -- "**.cpp",
        -- "**.hpp",
        -- "**.h",
		-- "**.hxx"
    -- }
	
	-- project "Dummy" 	
package.path = "../Engine/Scripts/?.lua;" .. package.path
require('premake_options')
local utils = require('utils')

pathPrefix = "../"
--pathPrefix = "../../Breakout_Github"
if _OPTIONS["path_prefix"] then
	pathPrefix = _OPTIONS["path_prefix"]
end

if _OPTIONS["no_engine_project"] ~= nil then
	utils.CreateProjectForGithub(pathPrefix)
end

projectName = "Breakout"


solution (projectName)
	outputDirectory = pathPrefix.."/Projects"
	location (outputDirectory)
	language "C++"
	objdir (pathPrefix.."/Obj/")
	--configurations {"Release", "Debug", "ReleaseCandidate"}
	configurations {"Release", "Debug"}
	pchheader "stdafx.h"
	
	configuration { "Debug" } -- Will select Win32 | Debug in our case
		defines { "_DEBUG" }
		flags { "Symbols" } -- Debug symbols
		targetsuffix '_d' 
		targetdir (pathPrefix.."/Debug")
		libdirs {pathPrefix.."/Debug"}
		
	configuration { "Release*" } -- Selects both Release
		defines { "NDEBUG" }
		flags { "Optimize" } -- Optimization switches on
		targetdir (pathPrefix.."/bin")
		libdirs {pathPrefix.."/bin"}
		
	-- configuration { "ReleaseCandidate" } -- All ReleaseCandidates needs a special define
		-- defines { "RELEASE_CANDIDATE" }

	configuration { "Native" } -- On Win32
		defines{ "WIN32" } -- Define WIN32

	-- fileSet = 
    -- {
        -- "*.cpp",
        -- "*.hpp",
        -- "*.h",
		-- "*.hxx"
    -- }

	vpaths 
	{
		["Interfaces"] = {pathPrefix.."/**.hxx"},
		["Headers"] = {pathPrefix.."/**.h"},
		["Sources"] = {pathPrefix.."/**.c", pathPrefix.."/**.cpp"}
	}

	mainProjectName = projectName.."Main"
	project (mainProjectName)
		kind "WindowedApp"
		location = outputDirectory
		inputPath = pathPrefix.."/Source/"..mainProjectName.."/"
		utils.addfiles(inputPath) 
		if _OPTIONS["no_engine_project"] == nil then
			links { projectName, "Base", "Utilities" }
		end
		includedirs
		{
			pathPrefix.."/Source/"..projectName.."/Includes",
			pathPrefix.."/Engine/Source/Base/Includes",
			pathPrefix.."/Engine/Source/Utilities/Includes",
			pathPrefix.."/Engine/Source/GameBase/Includes",
			inputPath.."src",
			pathPrefix.."/Engine/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			pathPrefix.."/Engine/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (inputPath.."src/stdafx.cpp")
		flags{"WinMain"}
		configuration ("Debug")
			debugdir (pathPrefix.."/Debug")
			if _OPTIONS["no_engine_project"] ~= nil then
				links { projectName, "Base_d", "Utilities_d" }
			end
		configuration ("Release")
			debugdir (pathPrefix.."/bin")
			if _OPTIONS["no_engine_project"] ~= nil then
				links { projectName, "Base", "Utilities" }
			end
			
	project (projectName)
		kind "SharedLib"
		location = outputDirectory
		inputPath = pathPrefix.."/Source/"..projectName.."/"
		utils.addfiles(inputPath) 
		if _OPTIONS["no_engine_project"] == nil then
			links { "Base", "Utilities", "AI", "Graphics", "Physics", "Sound", "Gamebase" }
		end
		includedirs
		{
			pathPrefix.."/Engine/Source/Base/Includes",
			pathPrefix.."/Engine/Source/Utilities/Includes",
			pathPrefix.."/Engine/Source/AI/Includes",
			pathPrefix.."/Engine/Source/GraphicsEngine/Includes",
			pathPrefix.."/Engine/Source/Physics/Includes",
			pathPrefix.."/Engine/Source/Sound/Includes",
			pathPrefix.."/Engine/Source/GameBase/Includes",
			pathPrefix.."/Engine/extern/Include/VisualLeakDetector",
			inputPath.."Includes",
			--inputPath.."src"
		}	
		libdirs 
		{
			pathPrefix.."/Engine/extern/Lib/VisualLeakDetector/Win32"
		}		
		pchsource (inputPath.."src/stdafx.cpp")
		defines("BREAKOUT_EXPORTS")
	if _OPTIONS["no_engine_project"] ~= nil then
		configuration ("Debug")
			links { "Base_d", "Utilities_d", "AI_d", "Graphics_d", "Physics_d", "Sound_d", "Gamebase_d" }
		configuration ("Release")
			links { "Base", "Utilities", "AI", "Graphics", "Physics", "Sound", "Gamebase" }
	else		
		require('ai').run(pathPrefix.."/Engine", outputDirectory)
		require('base').run(pathPrefix.."/Engine", outputDirectory)
		require('gameBase').run(pathPrefix.."/Engine", outputDirectory)
		require('utilities').run(pathPrefix.."/Engine", outputDirectory)
		require('graphics').run(pathPrefix.."/Engine", outputDirectory)
		require('physics').run(pathPrefix.."/Engine", outputDirectory)
		require('sound').run(pathPrefix.."/Engine", outputDirectory)
	end
	