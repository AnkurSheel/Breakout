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

local utils = require('utils')
	
	
--utils.CreateProjectForGithub("Test/")

projectName = "Breakout"

solution (projectName)
	outputDirectory = "../Projects"
	location (outputDirectory)
	language "C++"
	objdir "../Obj/"
	--configurations {"Release", "Debug", "ReleaseCandidate"}
	configurations {"Release", "Debug"}
	pchheader "stdafx.h"
	
	configuration { "Debug" } -- Will select Win32 | Debug in our case
		defines { "_DEBUG" }
		flags { "Symbols" } -- Debug symbols
		targetsuffix '_d' 
		targetdir "../Debug"
		libdirs {"../Debug"}
		
	configuration { "Release*" } -- Selects both Release
		defines { "NDEBUG" }
		flags { "Optimize" } -- Optimization switches on
		targetdir "../bin"
		libdirs {"../bin"}
		
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
		["Interfaces"] = {"../**.hxx"},
		["Headers"] = {"../**.h"},
		["Sources"] = {"../**.c", "../**.cpp"}
	}

	require('ai').run("../Engine", outputDirectory)
	require('base').run("../Engine", outputDirectory)
	require('gameBase').run("../Engine", outputDirectory)
	require('utilities').run("../Engine", outputDirectory)
	require('graphics').run("../Engine", outputDirectory)
	require('physics').run("../Engine", outputDirectory)
	require('sound').run("../Engine", outputDirectory)
		
	project (projectName)
		kind "SharedLib"
		location = outputDirectory
		inputPath = "../Source/"..projectName.."/"
		utils.addfiles(inputPath) 
		links { "Base", "Utilities", "AI", "Graphics", "Physics", "Sound", "Gamebase" }
		includedirs
		{
			"../Engine/Source/Base/Includes",
			"../Engine/Source/Utilities/Includes",
			"../Engine/Source/AI/src",
			"../Engine/Source/GraphicsEngine/Includes",
			"../Engine/Source/Physics/Includes",
			"../Engine/Source/Sound/Includes",
			"../Engine/Source/GameBase/Includes",
			"../Engine/extern/Include/VisualLeakDetector",
			inputPath.."Includes",
			inputPath.."src"
		}	
		libdirs 
		{
			"../Engine/extern/Lib/VisualLeakDetector/Win32"
		}		
		pchsource (inputPath.."src/stdafx.cpp")

	mainProjectName = projectName.."Main"
	project (mainProjectName)
		kind "WindowedApp"
		location = outputDirectory
		inputPath = "../Source/"..mainProjectName.."/"
		utils.addfiles(inputPath) 
		links { projectName, "Base", "Utilities" }
		includedirs
		{
			"../Source/"..projectName.."/Includes",
			"../Engine/Source/Base/Includes",
			"../Engine/Source/Utilities/Includes",
			"../Engine/Source/GameBase/Includes",
			inputPath.."src",
			"../Engine/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			"../Engine/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (inputPath.."src/stdafx.cpp")
		flags{"WinMain"}
		configuration ("Debug")
			debugdir "../Debug"
		configuration ("Release")
			debugdir "../bin"

			
