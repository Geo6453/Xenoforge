import os
import shutil
from pathlib import Path

def checkFile(filePath):
    if not os.path.isfile(filePath):
        print("Ce n'est pas un fichier ou il n'existe pas")
        return False

    extensionFile = filePath.suffix
    extensionFile = extensionFile.lower()
    if(extensionFile != ".opus"):
        print("'"+filePath.stem+"'" + " is a "+extensionFile+", not a '.opus' file")
        return False

    filePathOpen = open(filePath, "r+b")
    filePathOpen.seek(0)
    readGenBytes = filePathOpen.read(96)
    readGenBytes = readGenBytes.hex(" ")

    checkGenBytes1 = "4f 67 67 53 00 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 a2 66 70 cd 01 13 4f 70 75 73 "
    checkGenBytes2 = "48 65 61 64 01 02 78 00 80 bb 00 00 00 00 00 4f 67 67 53 00 00 00 00 00 00 00 00 00 00 00 00 00 "
    checkGenBytes3 = "00 01 00 00 00 49 95 be 54 01 2e 4f 70 75 73 54 61 67 73 06 00 00 00 66 66 6d 70 65 67 01 00 00"
    checkGenBytes  = checkGenBytes1 + checkGenBytes2 + checkGenBytes3

    if readGenBytes != checkGenBytes:
        filePathOpen.close
        print("Something went wrong with the generated file's binary")
        print(filePath.name + " is not a true ogg opus file")
        return False

    return True

def deleteFileHeader(filePath):
    filePathOpen = filePath.open("r+b")
    filePathOpen.seek(121)
    save = filePathOpen.read()
    filePathOpen.seek(0)
    filePathOpen.write(save)
    filePathOpen.truncate() # No need to precise the offset, the cursor is automatically set at the good spot after write()
    filePathOpen.close

def calculateFrameChecksum(frame):
    print("")

def deleteOpusPage(filePath):
    filePathOpen = filePath.open("r+b")
    newFilePath = filePath.with_name(filePath.stem + " (test)" + filePath.suffix)
    newFilePathOpen = newFilePath.open("w+b")
    
    pageExist = True
    posCursor = 0
    fileTemp = filePathOpen.read()
    
    endFile = filePathOpen.seek(0, 2) # se positionner à la fin (2 = SEEK_END)
    taille = filePathOpen.tell()
    print(taille)

    while posCursor != taille:
        filePathOpen.seek(posCursor)
        check = filePathOpen.read(1)
        if check != "FC":
            filePathOpen.seek(posCursor + 137)
        frame = filePathOpen.read(480)
        print(posOggS - posCursor)
        posCursor = posOggS
        print(posCursor)

userInput = input("test : ")
userInput = userInput.strip('"')
filePath = Path(userInput)
print(filePath)
checkFile(filePath)
deleteFileHeader(filePath)
deleteOpusPage(filePath)