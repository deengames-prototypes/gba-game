#!/bin/python
import sys
import os
import subprocess
import shutil

GRIT = "grit.exe" if sys.platform == "win32" else "grit"
IMAGES_DIR = os.path.join(os.getcwd(), 'images')
OUTPUT_DIR = os.path.join(os.getcwd(), 'source', 'images')


def grit_images(images_dir, output_dir):
    for item in os.listdir(images_dir):
        item_path = os.path.join(images_dir, item)

        if os.path.isdir(item_path):
            # recursive image gritting; mirrors dir structure
            output_subdir = os.path.join(output_dir, item)
            os.mkdir(output_subdir)
            grit_images(item_path, output_subdir)

        elif os.path.isfile(item_path) and item.endswith(".png"):
            # found an image, grit it
            subprocess.call([GRIT, item_path, "-ftc", "-gB8"], cwd=output_dir)

            # grit spits out a C file with the actual data, and a header file
            # so we move the data to the header and delete the C file
            filename = str(item.split('.')[0])
            header = os.path.join(output_dir, filename + '.h')
            src = os.path.join(output_dir, filename + '.c')

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


def main():
    # clear existing generated files, unexpected behaviour if files already exist
    shutil.rmtree(OUTPUT_DIR)
    os.mkdir(OUTPUT_DIR)

    grit_images(IMAGES_DIR, OUTPUT_DIR)


if __name__ == '__main__':
    main()
