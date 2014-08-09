local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		require('Base').run(enginePath, outputDirectory)
		require('Utilities').run(enginePath, outputDirectory)
		project "Graphics"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/GraphicsEngine"
		utils.addfiles(inputPath) 
		links { "Base", "Utilities" }
		includedirs
		{
			enginePath.."/Source/GraphicsEngine/Includes",
			enginePath.."/Source/Base/Includes",
			enginePath.."/Source/Utilities/Includes",
			enginePath.."/extern/Include/VisualLeakDetector",
			enginePath.."/extern/Include/DirectX"
		}
		libdirs 
		{
			enginePath.."/extern/Lib/VisualLeakDetector/Win32",
			enginePath.."/extern/Lib/DirectX/x86"
		}		
		pchsource (enginePath.."/Source/GraphicsEngine/src/stdafx.cpp")
		defines {"GRAPHICSENGINE_EXPORTS"}
		excludes {"**/ScreenElement.hxx"}
	end
}
