local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		require('base').run(enginePath, outputDirectory)
		require('utilities').run(enginePath, outputDirectory)
		project "AI"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/AI/"
		utils.addfiles(inputPath)
		links { "Base", "Utilities" }
		includedirs
		{
			enginePath.."/Source/AI/src",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes/",
			enginePath.."/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}
		pchsource (enginePath.."/Source/AI/src/stdafx.cpp")
		defines {"AI_EXPORTS"}
	end
}

