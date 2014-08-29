local utils = require('utils')

return {
	run = function(enginePath, outputDirectory)
		project "Graphics"
		kind "SharedLib"
		location = outputDirectory
		inputPath = enginePath.."/Source/GraphicsEngine"
		utils.addfiles(inputPath) 
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
		configuration ("Debug")
			links { "Base_d", "Utilities_d"}
		configuration ("Release")
			links { "Base", "Utilities" }
	end
}
