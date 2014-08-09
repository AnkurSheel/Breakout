local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		require('base').run(enginePath, outputDirectory)
		require('utilities').run(enginePath, outputDirectory)
		project "Physics"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/Physics"
		utils.addfiles(inputPath) 
		links { "Base", "Utilities" }
		includedirs
		{
			enginePath.."/Source/Physics/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (enginePath.."/Source/Physics/src/stdafx.cpp")
		defines {"PHYSICS_EXPORTS"}
	end
}
