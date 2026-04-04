#!/usr/bin/env python
'''
Convert a PNG to 15BPP.
'''

import argparse

from PIL import Image

from ConversionLib.Snes import imgToSnesColourDepth

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('inputFile', metavar='<input.png>', type=str, help="Input PNG file")
    parser.add_argument('outputFile', metavar='<output.png>', type=str, help="Output 15BPP PNG file")
    args = parser.parse_args()
    with Image.open(args.inputFile) as tileImg:
        tileImg = imgToSnesColourDepth(tileImg)
    tileImg.save(args.outputFile)

if __name__ == '__main__':
    main()
