#!/bin/python
import sys
import os
import subprocess
import shutil

GRIT = "grit.exe" if sys.platform == "win32" else "grit"
IMAGES_DIR = os.path.join(os.getcwd(), 'images')
PALETTE = os.path.join(IMAGES_DIR, "palette.png")
OUTPUT_DIR = os.path.join(os.getcwd(), 'include', 'images')
TMP_DIR = os.path.join(os.getcwd(), 'tmp')


def clear_dir(tmp_dir):
    if os.path.exists(tmp_dir):
        shutil.rmtree(tmp_dir)
    os.makedirs(tmp_dir, exist_ok=True)


def move_data_to_header(item, tmp_dir, output_dir):
    # grit spits out a C file with the actual data, and a header file
    # so we move the data to the header and delete the C file

    filename = str(item.split('.')[0])
    header = os.path.join(tmp_dir, filename + '.h')
    src = os.path.join(tmp_dir, filename + '.c')

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
        elif "Time-stamp:" in line:
            pass
        else:
            result += line

    output_header = os.path.join(output_dir, filename + '.h')
    with open(output_header, 'w') as f:
        f.write(result)


def grit_images(images_dir, tmp_dir, output_dir):
    for item in os.listdir(images_dir):
        item_path = os.path.join(images_dir, item)

        if os.path.isdir(item_path):
            # recursive image gritting; mirrors dir structure
            tmp_subdir = os.path.join(tmp_dir, item)
            os.mkdir(tmp_subdir)
            output_subdir = os.path.join(output_dir, item)
            os.mkdir(output_subdir)
            grit_images(item_path, tmp_subdir, output_subdir)

        elif os.path.isfile(item_path) and item.endswith(".png"):
            # found an image, grit it
            # yes, the first argument is the palette
            # no, I don't know how it works, but it does, so don't touch it
            subprocess.call([GRIT, PALETTE, item_path, "-ftc", "-gB8", "-pS", "-Opalette"], cwd=tmp_dir)

            move_data_to_header(item, tmp_dir, output_dir)

            clear_dir(tmp_dir)


def main():
    if not os.path.exists(IMAGES_DIR):
        os.mkdir(IMAGES_DIR)

    clear_dir(TMP_DIR)
    clear_dir(OUTPUT_DIR)

    grit_images(IMAGES_DIR, TMP_DIR, OUTPUT_DIR)

    shutil.rmtree(TMP_DIR)


if __name__ == '__main__':
    main()
