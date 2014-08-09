local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		require('Base').run(enginePath, outputDirectory)
		require('Utilities').run(enginePath, outputDirectory)
		require('AI').run(enginePath, outputDirectory)
		require('Graphics').run(enginePath, outputDirectory)
		require('Physics').run(enginePath, outputDirectory)
		require('Sound').run(enginePath, outputDirectory)
		project "Gamebase"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/GameBase"
		utils.addfiles(inputPath) 
		links { "Base", "Utilities", "AI", "Graphics", "Physics", "Sound" }
		includedirs
		{
			enginePath.."/Source/GameBase/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/Source/AI/src",
			enginePath.."/Source/GraphicsEngine/Includes",
			enginePath.."/Source/Physics/Includes",
			enginePath.."/Source/Sound/Includes",
			enginePath.."/extern/Include/VisualLeakDetector"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32"
		}		
		pchsource (enginePath.."/Source/GameBase/src/stdafx.cpp")
		defines {"GAMEBASE_EXPORTS" }
	end
}
