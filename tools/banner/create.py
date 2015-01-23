from PIL import Image
from sys import exit, argv
from compress import compress_nlz11_to_bytes

BANNER_WIDTH = 256
BANNER_HEIGHT = 128

texHeaderFile = open("header.bin", "rb")
tileMapFile = open("map" + str(BANNER_WIDTH) + "x" + str(BANNER_HEIGHT) + ".bin", "rb")

LENGTH_BYTES = 4
BANNER_TEX_HEADER = texHeaderFile.read()
BANNER_CBMD_HEADER = bytearray([0x43, 0x42, 0x4D, 0x44, 0x00, 0x00, 0x00, 0x00, 0x88]) + bytearray(0x7B)

TILE_MAP = tileMapFile.read()

texHeaderFile.close()
tileMapFile.close()

def convert_banner_image(file):
    image = Image.open(file)
    if image.size[0] != BANNER_WIDTH or image.size[1] != BANNER_HEIGHT:
        print("ERROR: Image must be exactly " + str(BANNER_WIDTH) + " x " + str(BANNER_HEIGHT) + ".")
        exit(1)

    imageData = list(image.getdata())

    converted = bytearray(BANNER_WIDTH * BANNER_HEIGHT * 2)
    for x in range(BANNER_WIDTH * BANNER_HEIGHT):
        pos = TILE_MAP[x * 2] + (TILE_MAP[(x * 2) + 1] << 8)
        converted[pos << 1] = ((imageData[x][2] >> 4) << 4) | (imageData[x][3] >> 4)
        converted[(pos << 1) + 1] = ((imageData[x][0] >> 4) << 4) | (imageData[x][1] >> 4)

    return converted;

def make_banner(file):
    compressed = compress_nlz11_to_bytes(BANNER_TEX_HEADER + convert_banner_image(file))
    pad = bytearray(16 - ((len(BANNER_CBMD_HEADER) + LENGTH_BYTES + len(compressed)) % 16))
    length = (len(BANNER_CBMD_HEADER) + LENGTH_BYTES + len(compressed) + len(pad)).to_bytes(LENGTH_BYTES, byteorder='little')
    return BANNER_CBMD_HEADER + length + compressed + pad
  
def make_audio():
    # TODO: Convert WAV file.
    audioFile = open("audio.bcwav","rb")
    audio = audioFile.read()
    audioFile.close()
    return audio

audio = make_audio()
banner = make_banner(argv[1])

output = open(argv[2], "wb")
output.write(banner + audio)
output.close()