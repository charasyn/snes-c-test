#!/usr/bin/env python

import glob

from PIL import Image, ImageDraw


def main():
    inputs = glob.glob('*.png')
    try:
        inputs.remove('palette.png')
    except ValueError:
        pass
    inputs = sorted(inputs)
    colours = []
    for inp in inputs:
        with Image.open(inp) as img:
            imgColours = {y: x for x, y in img.palette.colors.items()}
            colours.extend(imgColours.get(x, (0xf8, 0, 0xf8)) for x in range(16))
    assert len(colours) % 16 == 0
    tw, th = 16, len(colours) // 16
    outputImg = Image.new('RGB', (tw*8, th*8))
    draw = ImageDraw.Draw(outputImg)
    for idx, col in enumerate(colours):
        tx, ty = idx % 16, idx // 16
        draw.rectangle((tx*8, ty*8, tx*8+7, ty*8+7), fill=col)
    outputImg.save('palette.png')

if __name__ == '__main__':
    main()
