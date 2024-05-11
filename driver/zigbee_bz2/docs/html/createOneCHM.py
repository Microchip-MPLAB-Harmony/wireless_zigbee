#The script is used create a single CHM file for a given platform.
#The Platform variable is used when the script is called without
#parameters (for example, by double-clicking in the explorer).
#The script can be also executed from the command line with parameters
#which will be treated as platform names. Specify several platforms,
#separating them with spaces, to produce several CHM files.
#The logic of creating eachn CHM file is the same as in other scripts of
#this type: createCHMs.py and updateCHMs.py.
import os, shutil, sys
from subprocess import call
from os.path import join, isfile, isdir

Platform = "PIC32CX-BZ_Zigbee"
#PathToStackDocs = "D:\work\svn_Microchip\\trunk\stack\doc"
PathToStackDocs = "D:\work\\Zigbee_docs\BitCloud\docs\PIC32CX-BZ_Zigbee" 
BitCloudPaths = [
	"D:\work\\Zigbee_docs\BitCloud\html",
	"D:\work\\Zigbee_docs\BitCloud Profile Suite\html",
	"D:\work\\Zigbee_docs\BitCloud ZLL\html",
]
CommonDirPath = "D:\work\\Zigbee_docs\BitCloud\html\common"
DoxToChmScriptPath = "doxtochm.py"
CreatedCHMsDir = "CREATED_CHM"	

def getDirs(path):
	return [join(path, x) for x in os.listdir(path) if isdir(join(path, x))]

def getDirsNames(path):
	return [x for x in os.listdir(path) if isdir(join(path, x))]
	
def getFiles(path):
	return [join(path, x) for x in os.listdir(path) if isfile(join(path, x))]

def getCHMs(path):
	return [x for x in os.listdir(path) if os.path.splitext(x)[-1] == ".chm"]

def safeMkDir(destDir, name):
	if name in os.listdir(destDir):
		shutil.rmtree(join(destDir, name))
	os.mkdir(join(destDir, name))

def copyTreeExceptName(srcDir, destDir, exceptName):
	for name in os.listdir(srcDir):
		path = join(srcDir, name)
		if name != exceptName:
			if isfile(path):
				#if the file already exists remove it
				if name in os.listdir(destDir):
					os.remove(join(destDir, name))
				shutil.copy(path, destDir)
			elif isdir(path):
				safeMkDir(destDir, name)
				copyTreeExceptName(path, join(destDir, name), exceptName)

def createCHM(platform):
	success = False
	dir = ""
	dirName = ""

	for bitCloudPath in BitCloudPaths:
		for x in os.listdir(bitCloudPath):
			if platform.lower() == x.lower():
				dir = join(PathToStackDocs, x)
				dirName = x
				safeMkDir(PathToStackDocs, dirName)
				copyTreeExceptName(join(bitCloudPath, dirName), dir, ".svn")
				safeMkDir(PathToStackDocs, "common")
				copyTreeExceptName(CommonDirPath, join(PathToStackDocs, "common"), ".svn")
				success = True
				break

	if success:
		call(["python.exe", DoxToChmScriptPath, dir])

		chms = getCHMs(dir)
		subDirsWithCHMs = []
		for subDir in getDirsNames(dir):
			if getCHMs(join(dir, subDir)) != []:
				subDirsWithCHMs.append(subDir)
		if chms != [] or subDirsWithCHMs != []:
			for chm in chms:
				shutil.copy(join(dir, chm), chm)
			for subDir in subDirsWithCHMs:
				safeMkDir(os.getcwd(), subDir)
				copyTreeExceptName(join(dir, subDir), subDir, None)
	else:
		print "Platform " + platform + " has not been found at any of BitCloud paths."
		return

if __name__ == "__main__":
	if len(sys.argv) > 1:
		for platform in sys.argv[1:]:
			createCHM(platform)
	else:
		createCHM(Platform)


