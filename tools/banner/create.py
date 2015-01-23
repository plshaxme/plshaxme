from PIL import Image
from sys import exit, argv
from compress import compress_nlz11_to_bytes

texHeaderFile = open("header.bin", "rb")

TILE_ORDER = bytearray([0, 1, 8, 9, 2, 3, 10, 11, 16, 17, 24, 25, 18, 19, 26, 27, 4, 5, 12, 13, 6, 7, 14, 15, 20, 21, 28, 29, 22, 23, 30, 31, 32, 33, 40, 41, 34, 35, 42, 43, 48, 49, 56, 57, 50, 51, 58, 59, 36, 37, 44, 45, 38, 39, 46, 47, 52, 53, 60, 61, 54, 55, 62, 63])

LENGTH_BYTES = 4
BANNER_TEX_HEADER = texHeaderFile.read()
BANNER_CBMD_HEADER = bytearray([0x43, 0x42, 0x4D, 0x44, 0x00, 0x00, 0x00, 0x00, 0x88]) + bytearray(0x7B)

texHeaderFile.close()

def convert_image(file, width, height):
    image = Image.open(file)
    if image.size[0] != width or image.size[1] != height:
        print("ERROR: Image must be exactly " + str(width) + " x " + str(height) + ".")
        exit(1)

    imageData = list(image.getdata())

    converted = bytearray(width * height * 2)
    n = 0
    for y in range(0, height, 8):
        for x in range(0, width, 8):
            for k in range(0, 8 * 8):
                xx = (TILE_ORDER[k] & 0x7)
                yy = (TILE_ORDER[k] >> 3)

                index = (y + yy) * width + (x + xx);
                converted[n] = ((imageData[index][2] >> 4) << 4) | (imageData[index][3] >> 4)
                converted[n + 1] = ((imageData[index][0] >> 4) << 4) | (imageData[index][1] >> 4)
                n += 2

    return converted;

def make_banner(file):
    compressed = compress_nlz11_to_bytes(BANNER_TEX_HEADER + convert_image(file, 256, 128))
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