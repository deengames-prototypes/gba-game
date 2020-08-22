#!/bin/python
import sys
import os
import subprocess
import shutil

GRIT = "grit.exe" if sys.platform == "win32" else "grit"
IMAGES = os.path.join(os.getcwd(), 'images')
OUTPUT_DIR = os.path.join(os.getcwd(), 'source', 'images')


def main():
    # clear existing generated files, unexpected behaviour if files already exist
    shutil.rmtree(OUTPUT_DIR)
    os.mkdir(OUTPUT_DIR)

    for item in os.listdir(IMAGES):
        item_path = os.path.join(IMAGES, item)
        if os.path.isfile(item_path) and item.endswith(".png"):
            # found an image, grit it
            subprocess.call([GRIT, item_path, "-ftc", "-gB8"], cwd=OUTPUT_DIR)

            move_data_to_header(item)


def move_data_to_header(image_name):
    # grit spits out a C file with the actual data, and a header file
    # so we move the data to the header and delete the C file

    filename = str(image_name.split('.')[0])
    header = os.path.join(OUTPUT_DIR, filename + '.h')
    src = os.path.join(OUTPUT_DIR, filename + '.c')

    with open(src, 'r') as f:
        # load the C file, strip comments, only keep definition with data
        data = "".join(x for x in f.readlines() if not x.startswith("//"))

    with open(header, 'r') as f:
        header_lines = f.readlines()

    result = ''
    data_is_added = False
    for line in header_lines:
        # replace definition line with data, keep other lines
        if line.startswith("extern"):
            if not data_is_added:
                result += data
                data_is_added = True
        else:
            result += line

    with open(header, 'w') as f:
        f.write(result)

    # done, delete C file
    os.remove(src)


if __name__ == '__main__':
    main()
