local function addfiles(inputpath)
  files
	{ 
		inputPath.."**.h", 
		inputPath.."**.hxx", 
		inputPath.."**.hpp", 
		inputPath.."**.cpp", 
	}
end

--local f = io.open("fileList.txt", "w")
local function CreateDirs(filePath, newPathPrefix)
	local pathName = path.rebase(filePath, os.getcwd(), "../");
	os.mkdir(newPathPrefix..pathName)
	--f:write("Dir : "..filePath.." : "..pathName.."\n")
end

local function CopyFiles(filePath, newPathPrefix)
	local pathName = path.rebase(filePath, os.getcwd(), "../");
	os.copyfile(filePath, newPathPrefix..pathName)
	--f:write("File : "..filePath.." : "..pathName.."\n")
end

local function CreateProjectForGithub(dirPath)

	os.rmdir(dirPath)
	os.mkdir(dirPath)

	for _, fname in ipairs(os.matchdirs("../Engine/**")) do
		if string.match(fname, "InternalDoc") == nil then
			if string.match(fname, "Engine/Source/") == nil then
				CreateDirs(fname, dirPath)
			elseif string.match(fname, "/src") == nil then
				CreateDirs(fname, dirPath)
			end
		end
	end

	for _, fname in ipairs(os.matchfiles("../Engine/**")) do
		if string.match(fname, "/Engine/Source") == nil then
			CopyFiles(fname, dirPath)
		elseif string.match(fname, "Includes") ~= nil then
			CopyFiles(fname, dirPath)
		end
	end
end
--f:close()

return {
  addfiles = addfiles,
  CreateProjectForGithub = CreateProjectForGithub
}