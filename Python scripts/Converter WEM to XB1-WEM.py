import os
from pathlib import Path

dll_dir = os.path.dirname(os.path.abspath(__file__))
os.add_dll_directory(dll_dir) # pour le chargement de la DLL et ses dépendances
os.environ['PATH'] = dll_dir + os.pathsep + os.environ['PATH'] # pour find_library()

import opuslib.api.ctl as ctl
import opuslib.api.decoder as decoder

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

def calculateFrameChecksum(frame):
    varDecoder = decoder.create_state(48000, 2)
    decoder.decode(varDecoder, frame, len(frame), 960, False)
    frameChecksum = decoder.decoder_ctl(varDecoder, ctl.get_final_range)
    frameChecksum = frameChecksum.to_bytes(4, byteorder="big")
    # print(frameChecksum.hex())
    return frameChecksum

def deleteOpusPage(filePath):
    filePathOpen = filePath.open("r+b")
    newFilePath = filePath.with_name(filePath.stem + " (converted)" + filePath.suffix)
    newFilePathOpen = newFilePath.open("w+b")

    endFile = filePathOpen.seek(0, 2) # se positionner à la fin (2 = SEEK_END)
    posCursor = 121
    frameNumberTotal = 0

    while posCursor < endFile:
        posCursor += 26
        filePathOpen.seek(posCursor)
        skipLength = int.from_bytes(filePathOpen.read(1))
        print(skipLength)
        frameNumberTotal += skipLength // 2
        posCursor += skipLength + 1
        filePathOpen.seek(posCursor)

        frameNumberPage = skipLength // 2
        for i in range(frameNumberPage):
            frame = filePathOpen.read(480)
            posCursor += 480
            newFilePathOpen.write(bytes.fromhex('00 00 01 E0'))
            newFilePathOpen.write(calculateFrameChecksum(frame))
            newFilePathOpen.write(frame)
    newFilePathOpen.close
    return frameNumberTotal

userInput = input("test : ")
userInput = userInput.strip('"')
filePath = Path(userInput)
print(filePath)
checkFile(filePath)

frameNumber = deleteOpusPage(filePath) * 488
frameNumber = int.to_bytes(frameNumber, 4, 'little')
newFilePath = filePath.with_name(filePath.stem + " (converted)" + filePath.suffix)
newFilePathOpen = newFilePath.open("r+b")
save = newFilePathOpen.read
newFilePathOpen.seek(0)
newFilePathOpen.truncate()

newFilePathOpen.write(bytes.fromhex('52 49 46 46')) # RIFF
newFilePathOpen.write(bytes.fromhex('00 00 00 00')) # File size but it'll be set at the end
newFilePathOpen.write(bytes.fromhex('57 41 56 45')) # WAVE
newFilePathOpen.write(bytes.fromhex('66 6D 74 20')) # fmt
newFilePathOpen.write(bytes.fromhex('28 00 00 00')) # 'fmt' chunk size
newFilePathOpen.write(bytes.fromhex('39 30 02 00'))
newFilePathOpen.write(bytes.fromhex('80 BB 00 00 00 EE 02 00 04 00 10 00 06 00 C0 03 02 31 00 00')) # File header
newFilePathOpen.write(bytes.fromhex('80 A2 19 00 00 00 00 00 D8 09 0D 00 5C 1B 00 00')) # idk